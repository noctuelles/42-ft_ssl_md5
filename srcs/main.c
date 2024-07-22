/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:05 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/22 13:16:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ft_ssl.h"
#include "includes/md5.h"
#include "includes/opts.h"
#include "includes/sha256.h"
#include "libft.h"
#include "wrapper.h"

#define NSIZE(x) (sizeof(x) / sizeof(x[0]))

extern const char *program_invocation_short_name;

static t_command g_available_cmds[] = {
    {
        .name                = "md5",
        .opts_parsing_config = &g_md5_conf,
        .dgst_fnct =
            {
                .dgst_init     = md5_init,
                .dgst_update   = md5_update,
                .dgst_finalize = md5_finalize,
            },
        .dgst_size       = MD5_DIGEST_SIZE,
        .ctx_size        = sizeof(t_md5_ctx),
        .opts_input_size = sizeof(t_md5_opts),
    },
    {.name                = "sha256",
     .opts_parsing_config = &g_sha256_conf,
     .dgst_fnct =
         {
             .dgst_init     = sha256_init,
             .dgst_update   = sha256_update,
             .dgst_finalize = sha256_finalize,
         },
     .dgst_size       = SHA256_DIGEST_SIZE,
     .ctx_size        = sizeof(t_sha256_ctx),
     .opts_input_size = sizeof(t_sha256_opts)}};

static int
print_usage(int ret_code) {
    printf("usage: %s [COMMAND]\n", program_invocation_short_name);
    printf("Available commands :\n");
    for (size_t i = 0; i < NSIZE(g_available_cmds); i++) {
        printf("%s [OPTS] [FILE]\n", g_available_cmds[i].name);
        ft_args_parser_print_docs(g_available_cmds[i].opts_parsing_config);
    }
    return (ret_code);
}

static void
print_digest(const uint8_t *digest, size_t ldigest) {
    size_t i = 0;

    while (i < ldigest) {
        printf("%02x", digest[i]);
        i++;
    }
}

/**
 * @brief Return the digested message of a given cryptographic hash.
 *
 * @param fd The file desciptor to get the data from.
 * @param cmd The command.
 * @return uint8_t* The digest or NULL if an error happened.
 */
static uint8_t *
digest_msg(int fd, const t_command *cmd) {
    uint8_t *dgst = NULL;
    uint8_t  buff[1024];
    void    *ctx = ctx = NULL;
    ssize_t  ret       = -1;

    if ((dgst = Malloc(cmd->dgst_size)) == NULL) {
        goto ret;
    }
    if ((ctx = Malloc(cmd->ctx_size)) == NULL) {
        goto free_dgst;
    }
    if (cmd->dgst_fnct.dgst_init(ctx) != 0) {
        ft_error(0, 0, "failed to initialize %s", cmd->name);
        goto free_dgst;
    }
    while ((ret = Read(fd, buff, sizeof(buff))) > 0) {
        if (cmd->dgst_fnct.dgst_update(ctx, buff, ret) != 0) {
            ft_error(0, 0, "failed to update %s", cmd->name);
            goto free_dgst;
        }
    }
    if (ret < 0) {
        goto free_dgst;
    }
    if (cmd->dgst_fnct.dgst_finalize(ctx, dgst) != 0) {
        ft_error(0, 0, "failed to finalize %s", cmd->name);
        goto free_dgst;
    }
    goto free_ctx;
free_dgst:
    free(dgst);
    dgst = NULL;
free_ctx:
    free(ctx);
    ctx = NULL;
ret:
    return (dgst);
}

// static void
// print_md5(const t_command *cmd, void *opts, const char *source,
//           uint8_t *digest) {
//     t_md5_opts *md5_opts = opts;

//     if (!md5_opts->quiet) {
//         printf("%s (%s) : ", cmd->name, source);
//     }
//     print_digest(digest, cmd->dgst_size);
//     print("\n");
// }

// static int
// handle_md5(const t_command *cmd, void *opts) {
//     t_md5_opts *md5_opts = opts;
//     const char *filename = NULL;
//     uint8_t    *dgst     = NULL;
//     int         fd       = -1;

//     for (t_list *elem = md5_opts->files; elem != NULL; elem = elem->next) {
//         filename = elem->content;

//         if ((fd = Open(filename, O_RDONLY)) == -1) {
//             return (-1);
//         }
//         if ((dgst = digest_msg(fd, cmd)) == -1) {
//             return (-1);
//         }
//         Close(fd);
//     }

//     ft_lstclear(&md5_opts->files, NULL);
// }

int
main(int argc, char **argv) {
    const char *cmd_str  = NULL;
    t_command  *cmd      = NULL;
    void       *cmd_opts = NULL;

    if (argc < 2) {
        return (print_usage(1));
    }
    cmd_str = argv[1];
    for (size_t i = 0; i < NSIZE(g_available_cmds); i++) {
        if (strcmp(cmd_str, g_available_cmds[i].name) == 0) {
            cmd = &g_available_cmds[i];
            break;
        }
    }
    if (cmd == NULL) {
        ft_error(0, 0, "'%s': no such command", cmd_str);
        return (1);
    }
    if ((cmd_opts = Malloc(cmd->opts_input_size)) == NULL) {
        return (1);
    }
    cmd->opts_parsing_config->argc  = argc - 1;
    cmd->opts_parsing_config->argv  = argv + 1;
    cmd->opts_parsing_config->input = cmd_opts;
    if (ft_args_parser(cmd->opts_parsing_config) == -1) {
        return (1);
    }
    return (digest_msg(STDIN_FILENO, cmd));
}