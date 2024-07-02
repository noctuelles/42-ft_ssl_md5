/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:05 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/02 15:06:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

#include "ft_ssl.h"
#include "libft.h"

#define NSIZE(x) (sizeof(x) / sizeof(x[0]))

extern const char *program_invocation_short_name;

static const t_command g_available_cmds[] = {{.name = "md5", .opts_parsing_config = NULL, .hash_fn = NULL},
                                             {.name = "sha256", .opts_parsing_config = NULL, .hash_fn = NULL}};

static void
print_usage() {
    printf("usage: %s [COMMAND] [COMMAND OPTS] \n\n", program_invocation_short_name);
    printf("Available commands :\n");
    for (size_t i = 0; i < NSIZE(g_available_cmds); i++) {
        printf("%s\n", g_available_cmds[i].name);
        if (g_available_cmds[i].opts_parsing_config == NULL) {
            continue;
        }
        printf("Available options :\n");
        ft_args_parser_print_docs(g_available_cmds[i].opts_parsing_config);
    }
}

int
main(int argc, char **argv) {
    const char      *cmd_str = NULL;
    const t_command *cmd     = NULL;

    if (argc < 2) {
        print_usage();
        return (1);
    }
    cmd_str = argv[1];
    for (size_t i = 0; i < NSIZE(g_available_cmds); i++) {
        if (strcmp(cmd_str, g_available_cmds[i].name) == 0) {
            cmd = &g_available_cmds[i];
            break;
        }
    }
    if (cmd == NULL) {
        ft_error(0, 0, "'%s': no such command\n", cmd_str);
        print_usage();
        return (1);
    }
    return (0);
}