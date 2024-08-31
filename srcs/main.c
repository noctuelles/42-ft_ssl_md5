/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:05 by plouvel           #+#    #+#             */
/*   Updated: 2024/08/31 18:30:43 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <fcntl.h>
#include <limits.h>
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
 * @brief Process the input from a file descriptor.
 */
const uint8_t *
proc_input_fd(union u_input input, size_t *nbytes_read, bool *fail) {
    static uint8_t buffer[1 << 10] = {0};
    ssize_t        ret             = 0;

    *fail = false;
    ret   = Read(input.fd, buffer, sizeof(buffer));
    if (ret < 0) {
        *nbytes_read = 0;
        *fail        = true;
    } else {
        *nbytes_read = (size_t)ret;
    }
    return (buffer);
}

/**
 * @brief Process the input from a string.
 */
const uint8_t *
proc_input_str(union u_input input, size_t *nbytes_read, bool *fail) {
    static bool already_proc = false;

    *fail = false;
    if (!already_proc) {
        *nbytes_read = strlen(input.str);
        already_proc = true;
    } else {
        *nbytes_read = 0;
    }
    return ((const uint8_t *)input.str);
}

/**
 * @brief Return the digest of an input by the cryptographic hash function cmd.
 *
 * @param input The input to hash.
 * @param proc_input_fn The function to process the input.
 * @param cmd The command to use.
 * @return uint8_t* The digest of the input.
 */
static uint8_t *
digest_msg(union u_input input, t_proc_input_fn proc_input_fn,
           const t_command *cmd, bool echo_input) {
    uint8_t       *dgst = NULL;
    void          *ctx = ctx   = NULL;
    const uint8_t *buffer      = NULL;
    size_t         nbytes_read = 0;
    bool           fail        = false;

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
    while ((buffer = proc_input_fn(input, &nbytes_read, &fail)) &&
           nbytes_read > 0) {
        if (echo_input == true) {
            (void)write(STDOUT_FILENO, buffer, nbytes_read);
        }
        if (cmd->dgst_fnct.dgst_update(ctx, buffer, nbytes_read) != 0) {
            ft_error(0, 0, "failed to update %s", cmd->name);
            goto free_dgst;
        }
    }
    if (fail) {
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

static int
handle_md5(const t_command *cmd, void *opts) {
    t_md5_opts   *md5_opts = opts;
    const char   *filename = NULL;
    uint8_t      *dgst     = NULL;
    union u_input input;
    int           fd = -1;

    if (isatty(STDIN_FILENO) == 0 || (!md5_opts->files && !md5_opts->str)) {
        bool echo = false;

        input.fd = STDIN_FILENO;
        if (!md5_opts->quiet) {
            printf("MD5(");
            if (md5_opts->echo_stdin_to_stdout) {
                echo = true;
                printf("\"");
            } else {
                printf("stdin");
            }
        }
        if ((dgst = digest_msg(input, proc_input_fd, cmd, echo)) == NULL) {
            return (1);
        }
        if (!md5_opts->quiet && md5_opts->echo_stdin_to_stdout) {
            printf("\"");
        }
        printf(")= ");
        print_digest(dgst, cmd->dgst_size);
        printf("\n");
    }
    if (md5_opts->str) {
        input.str = md5_opts->str;
        if (!md5_opts->quiet && !md5_opts->reverse) {
            printf("MD5(\"%s\")= ", md5_opts->str);
        }
        if ((dgst = digest_msg(input, proc_input_str, cmd, false)) == NULL) {
            return (1);
        }
        print_digest(dgst, cmd->dgst_size);
        if (!md5_opts->quiet) {
            if (md5_opts->reverse) {
                printf(" \"%s\"", md5_opts->str);
            }
        }
        printf("\n");
    }
    for (t_list *elem = md5_opts->files; elem != NULL; elem = elem->next) {
        filename = elem->content;

        if ((fd = Open(filename, O_RDONLY)) == -1) {
            return (-1);
        }
        if (!md5_opts->quiet && !md5_opts->reverse) {
            printf("MD5(%s)= ", filename);
        }
        input.fd = fd;
        if ((dgst = digest_msg(input, proc_input_fd, cmd, false)) == NULL) {
            return (-1);
        }
        print_digest(dgst, cmd->dgst_size);
        if (!md5_opts->quiet) {
            if (md5_opts->reverse) {
                printf(" %s", filename);
            }
        }
        printf("\n");
        Close(fd);
    }
    return (0);
}

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
    return (handle_md5(cmd, cmd_opts));
}