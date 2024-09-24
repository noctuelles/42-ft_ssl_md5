/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:05 by plouvel           #+#    #+#             */
/*   Updated: 2024/09/24 16:39:55 by plouvel          ###   ########.fr       */
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
#include "includes/command.h"
#include "includes/md5.h"
#include "includes/opts.h"
#include "includes/sha256.h"
#include "includes/whirlpool.h"
#include "libft.h"
#include "wrapper.h"

#define NSIZE(x) (sizeof(x) / sizeof(x[0]))

extern const char *program_invocation_short_name;

static t_command g_available_cmds[] = {{
                                           .name                = "md5",
                                           .opts_parsing_config = &g_md5_conf,
                                           .dgst_fnct =
                                               {
                                                   .dgst_init     = md5_init,
                                                   .dgst_update   = md5_update,
                                                   .dgst_finalize = md5_finalize,
                                               },
                                           .dgst_size       = MD5_DIGEST_SIZE,
                                           .handle_fn       = handle_md5,
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
                                        .handle_fn       = handle_sha256,
                                        .ctx_size        = sizeof(t_sha256_ctx),
                                        .opts_input_size = sizeof(t_sha256_opts)},
                                       {.name                = "whirlpool",
                                        .opts_parsing_config = &g_whirlpool_conf,
                                        .dgst_fnct =
                                            {
                                                .dgst_init     = whirlpool_init,
                                                .dgst_update   = whirlpool_update,
                                                .dgst_finalize = whirlpool_finalize,
                                            },
                                        .dgst_size       = WHIRLPOOL_DIGEST_SIZE * 8,
                                        .handle_fn       = handle_whirlpool,
                                        .ctx_size        = sizeof(t_whirlpool_ctx),
                                        .opts_input_size = sizeof(t_whirlpool_opts)}};

static int
print_usage(int ret_code) {
    printf("usage: %s [COMMAND]\n", program_invocation_short_name);
    printf("Available commands :\n");
    for (size_t i = 0; i < NSIZE(g_available_cmds); i++) {
        if (!g_available_cmds[i].opts_parsing_config) {
            printf("%s - no options available.\n", g_available_cmds[i].name);
            continue;
        }

        printf("%s [OPTS] [FILE]\n", g_available_cmds[i].name);
        ft_args_parser_print_docs(g_available_cmds[i].opts_parsing_config);
    }
    return (ret_code);
}

int
main(int argc, char **argv) {
    const char *cmd_str  = NULL;
    t_command  *cmd      = NULL;
    void       *cmd_opts = NULL;
    int         ret      = 1;

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
    if (cmd->opts_parsing_config) {
        if ((cmd_opts = Malloc(cmd->opts_input_size)) == NULL) {
            return (1);
        }
        bzero(cmd_opts, cmd->opts_input_size);
        cmd->opts_parsing_config->argc  = argc - 1;
        cmd->opts_parsing_config->argv  = argv + 1;
        cmd->opts_parsing_config->input = cmd_opts;

        if (ft_args_parser(cmd->opts_parsing_config) == -1) {
            return (1);
        }
    }
    ret = cmd->handle_fn(cmd, cmd_opts);
    if (cmd_opts) {
        free(cmd_opts);
    }
    return (ret);
}