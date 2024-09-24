/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:02:45 by plouvel           #+#    #+#             */
/*   Updated: 2024/09/24 09:54:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTS_H
#define OPTS_H

#include "ft_args_parser.h"
#include "libft.h"

typedef struct s_md5_opts {
    bool        reverse;
    bool        quiet;
    bool        echo_stdin_to_stdout;
    const char *str;
    t_list     *files;
} t_md5_opts;

typedef struct s_sha256_opts {
    bool        reverse;
    bool        quiet;
    bool        echo_stdin_to_stdout;
    const char *str;
    t_list     *files;
} t_sha256_opts;

typedef struct s_whirlpool_opts {
    bool        reverse;
    bool        quiet;
    const char *str;
    t_list     *files;
} t_whirlpool_opts;

extern t_args_parser_config g_md5_conf;
extern t_args_parser_config g_sha256_conf;
extern t_args_parser_config g_whirlpool_conf;

#endif