/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:53 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/08 17:06:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
#define FT_SSL_H

/**
 * @file ft_ssl.h
 * @note Ressource used :
 *
 *      https://en.wikipedia.org/wiki/MD5
 *      https://www.ietf.org/rfc/rfc1321.txt
 *      https://en.wikipedia.org/wiki/SHA-2
 *      https://datatracker.ietf.org/doc/html/rfc6234
 *
 *      https://en.wikipedia.org/wiki/Padding_(cryptography)
 *      https://crypto.stackexchange.com/questions/90336/what-is-the-padding-block-actually-in-merkle-damg%C3%A5rd
 *      https://en.wikipedia.org/wiki/Merkle%E2%80%93Damg%C3%A5rd_construction,
 *      especially the "Length padding example".
 */

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