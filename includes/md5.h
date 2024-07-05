/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:15:43 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/05 12:06:09 by plouvel          ###   ########.fr       */
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

/**
 * @brief State initialization variables.
 */
#define A 0x67452301u
#define B 0xEFCDAB89u
#define C 0x98BADCFEu
#define D 0x10325476u

/**
 * @brief If X, then Y, else Z.
 */
#define F(X, Y, Z) (((X) & (Y)) | ((~X) & (Z)))
#define G(X, Y, Z) (((X) & (Z)) | ((Y) & (~Z)))
/**
 * @brief  Bit-wise parity operator.
 *
 */
#define H(X, Y, Z) ((X) ^ (Y) ^ (Z))
#define I(X, Y, Z) ((Y) ^ ((X) | (~Z)))

/** Round one
 * a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s) */
#define FF(a, b, c, d, k, s, i)              \
    {                                        \
        (a) += F((b), (c), (d)) + (k) + (i); \
        (a) = L_ROT_32((a), (s));            \
        (a) += (b);                          \
    }

/** a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s). */
#define GG(a, b, c, d, k, s, i)              \
    {                                        \
        (a) += G((b), (c), (d)) + (k) + (i); \
        (a) = L_ROT_32((a), (s));            \
        (a) += (b);                          \
    }

/** a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s). */
#define HH(a, b, c, d, k, s, i)              \
    {                                        \
        (a) += H((b), (c), (d)) + (k) + (i); \
        (a) = L_ROT_32((a), (s));            \
        (a) += (b);                          \
    }

/** a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s). */
#define II(a, b, c, d, k, s, i)              \
    {                                        \
        (a) += I((b), (c), (d)) + (k) + (i); \
        (a) = L_ROT_32((a), (s));            \
        (a) += (b);                          \
    }

#endif
