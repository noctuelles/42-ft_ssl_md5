/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:53 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/08 12:23:57 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
#define FT_SSL_H

#include <stdbool.h>
#include <stdint.h>

#include "ft_args_parser.h"

typedef int (*t_hash_str_fptr)(const char *, void **, size_t *);
typedef int (*t_hash_fd_fptr)(int, void **, size_t *);

typedef struct s_command {
    const char           *name;
    t_args_parser_config *opts_parsing_config;
    t_hash_str_fptr       hash_str;
    t_hash_fd_fptr        hash_fd;
} t_command;

typedef struct s_md5_opts {
    const char *str;
    bool        echo_stdin : 1;
    bool        quiet : 1;
    bool        reverse : 1;
} t_md5_opts;

typedef struct s_sha256_opts {
    const char *str;
    bool        echo_stdin : 1;
    bool        quiet : 1;
    bool        reverse : 1;
} t_sha256_opts;

#endif