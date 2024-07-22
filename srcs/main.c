/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:05 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/22 12:25:50 by plouvel          ###   ########.fr       */
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

static const t_command g_available_cmds[] = {
    {
        .name                = "md5",
        .opts_parsing_config = &g_md5_conf,
        .dgst_fnct =
            {
                .dgst_init     = md5_init,
                .dgst_update   = md5_update,
                .dgst_finalize = md5_finalize,
            },
        .dgst_size = MD5_DIGEST_SIZE,
        .ctx_size  = sizeof(t_md5_ctx),
    },
    {
        .name                = "sha256",
        .opts_parsing_config = &g_sha256_conf,
        .dgst_fnct =
            {
                .dgst_init     = sha256_init,
                .dgst_update   = sha256_update,
                .dgst_finalize = sha256_finalize,
            },
        .dgst_size = SHA256_DIGEST_SIZE,
        .ctx_size  = sizeof(t_sha256_ctx),
    }};

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
    printf("\n");
}

static int
digest_msg(const t_command *cmd) {
    uint8_t *dgst = NULL;
    uint8_t  buff[512];
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
        goto free_ctx;
    }
    /* TODO: arbitrary file descriptor. */
    while ((ret = Read(STDIN_FILENO, buff, sizeof(buff))) > 0) {
        if (cmd->dgst_fnct.dgst_update(ctx, buff, ret) != 0) {
            ft_error(0, 0, "failed to update %s", cmd->name);
            goto free_ctx;
        }
    }
    if (ret < 0) {
        goto free_ctx;
    }
    if (cmd->dgst_fnct.dgst_finalize(ctx, dgst) != 0) {
        ft_error(0, 0, "failed to finalize %s", cmd->name);
        goto free_ctx;
    }
    print_digest(dgst, cmd->dgst_size);
    ret = 0;
free_ctx:
    free(ctx);
free_dgst:
    free(dgst);
ret:
    return (ret);
}

int
main(int argc, char **argv) {
    const char      *cmd_str = NULL;
    const t_command *cmd     = NULL;

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
    return (digest_msg(cmd));
}