/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:15:43 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/05 23:32:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
#define MD5_H

/**
 * @file md5.h
 * @note Ressource used :
 *
 *      https://en.wikipedia.org/wiki/Padding_(cryptography)
 *      https://en.wikipedia.org/wiki/MD5
 *      https://www.ietf.org/rfc/rfc1321.txt
 */

#include <stddef.h>
#include <stdint.h>

#define MD5_STATE 4
#define MD5_BLK_LEN 16

typedef struct s_md5_ctx {
    size_t   msg_len;
    uint32_t buffer[MD5_BLK_LEN];
    uint32_t state[MD5_STATE];
} t_md5_ctx;

/**
 * @brief Perform a left rotation on a 32-bit value.
 */
#define L_ROT_32(X, N) (((X) << (N)) | ((X) >> (32 - (N))))

#endif
