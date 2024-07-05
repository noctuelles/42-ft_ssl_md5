/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:14:18 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/05 23:57:07 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/md5.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static const uint32_t g_sines[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1,
    0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x2441453,
    0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942,
    0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d,
    0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static const uint8_t g_shifts[64] = {7,  12, 17, 22, 7,  12, 17, 22, 7,  12, 17, 22, 7,  12, 17, 22, 5,  9,  14, 20, 5,  9,
                                     14, 20, 5,  9,  14, 20, 5,  9,  14, 20, 4,  11, 16, 23, 4,  11, 16, 23, 4,  11, 16, 23,
                                     4,  11, 16, 23, 6,  10, 15, 21, 6,  10, 15, 21, 6,  10, 15, 21, 6,  10, 15, 21};

static const uint8_t g_pads[64] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/**
 * @brief
 *
 * @return t_md5_ctx* the md5 context, or NULL if an error occured.
 */
static t_md5_ctx *
init_md5_ctx(void) {
    t_md5_ctx *md5_ctx = NULL;

    if ((md5_ctx = calloc(sizeof(*md5_ctx), 1)) == NULL) {
        return (NULL);
    }

    md5_ctx->state[0] = 0x67452301;
    md5_ctx->state[1] = 0xEFCDAB89;
    md5_ctx->state[2] = 0x98BADCFE;
    md5_ctx->state[3] = 0x10325476;

    return (md5_ctx);
}

static uint32_t
F(uint32_t b, uint32_t c, uint32_t d, size_t i) {
    uint32_t f = 0;

    if (i >= 0 && i <= 15) {
        f = (b & c) | (~b & d);
    } else if (i >= 16 && i <= 31) {
        f = (d & b) | (c & ~d);
    } else if (i >= 32 && i <= 47) {
        f = b ^ c ^ d;
    } else if (i >= 48 && i <= 63) {
        f = c ^ (b | ~d);
    }

    return (f);
}

static size_t
G(size_t i) {
    size_t i = 0;

    if (i >= 0 && i <= 15) {
        i = i;
    } else if (i >= 16 && i <= 31) {
        i = (5 * i + 1) % 16;
    } else if (i >= 32 && i <= 47) {
        i = (3 * i + 5) % 16;
    } else if (i >= 48 && i <= 63) {
        i = (7 * i) % 16;
    }

    return (i);
}

/**
 * @brief Apply the 4 rounds (16 operations) on a 512-bit block specified in the context.
 *
 * @param md5_ctx The MD5 context.
 */
static void
md5_step(t_md5_ctx *md5_ctx) {
    uint32_t        a = 0, b = 0, c = 0, d = 0;
    const uint32_t *blk = md5_ctx->buffer;

    a = md5_ctx->state[0];
    b = md5_ctx->state[1];
    c = md5_ctx->state[2];
    d = md5_ctx->state[3];

    for (size_t i = 0; i < 64; i++) {
        a = d;
        b = b + L_ROT_32(F(b, c, d, i) + g_sines[i] + blk[G(i)], g_shifts[i]);
        c = b;
        d = c;
    }

    md5_ctx->state[0] += a;
    md5_ctx->state[1] += b;
    md5_ctx->state[2] += c;
    md5_ctx->state[3] += d;
}
