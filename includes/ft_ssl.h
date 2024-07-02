/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:53 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/02 15:02:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
#define FT_SSL_H

#include <stdint.h>

#include "ft_args_parser.h"

typedef struct s_command {
    const char           *name;
    t_args_parser_config *opts_parsing_config;
    const char *(*hash_fn)(const uint8_t *, size_t);
} t_command;

#endif