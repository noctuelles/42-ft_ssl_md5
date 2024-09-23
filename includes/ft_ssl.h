/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:52:53 by plouvel           #+#    #+#             */
/*   Updated: 2024/09/23 19:34:35 by plouvel          ###   ########.fr       */
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

#ifndef __BYTE_ORDER__
#error "Byte order not defined. Please use GCC at a recent version or define __BYTE_ORDER__ manually."
#endif

#define BUFFER_SIZE 1 << 10

typedef struct s_command t_command;

union u_input {
    int         fd;
    const char *str;
};

typedef const uint8_t *(*t_proc_input_fn)(union u_input, size_t *, bool *);
typedef int (*t_handle_fn)(const t_command *, void *);
typedef int (*t_dgst_init_fn)(void *);
typedef int (*t_dgst_update_fn)(void *, const uint8_t *, size_t);
typedef int (*t_dgst_finalize_fn)(void *, uint8_t *);

typedef struct s_dgst_fncts {
    t_dgst_init_fn     dgst_init;
    t_dgst_update_fn   dgst_update;
    t_dgst_finalize_fn dgst_finalize;
} t_dgst_fncts;

struct s_command {
    const char           *name;                /* The name of the command */
    t_args_parser_config *opts_parsing_config; /* The options parsing configuration */
    size_t                opts_input_size;     /* The size of the latter */
    size_t                ctx_size;            /* The size of the latter */
    size_t                dgst_size;           /* The size of the digest in bytes */
    t_dgst_fncts          dgst_fnct;           /* The digest function */
    t_handle_fn           handle_fn;
};

#endif