/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:53 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/08 19:01:06 by plouvel          ###   ########.fr       */
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

typedef struct s_dgst_fnct {
    int (*dgst_init)(void *); /* */
    int (*dgst_update)(void *, const uint8_t *, size_t);
    int (*dgst_finalize)(void *, uint8_t *);
} t_dgst_fnct;

typedef struct s_command {
    const char *name; /* The name of the command */
    t_args_parser_config
               *opts_parsing_config; /* The options parsing configuration */
    void       *ctx;                 /* The context of the digest function */
    t_dgst_fnct dgst_fnct;           /* The digest function */
    size_t      dgst_size;           /* The size of the digest in bytes */
    size_t      ctx_size;            /* The size of the context */
} t_command;

#endif