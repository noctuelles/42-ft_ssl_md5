/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:53 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/06 14:41:23 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
#define FT_SSL_H

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

#endif