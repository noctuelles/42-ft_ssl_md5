/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/07/03 12:42:32 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/03 14:17:36 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file md5.c
 *
 * @note https://www.ietf.org/rfc/rfc1321.txt
 */

#include <stddef.h>
#include <stdint.h>

static const uint32_t g_word_a = 0x01234567u;
static const uint32_t g_word_b = 0x89ABCDEFu;
static const uint32_t g_word_c = 0xFEDCBA98u;
static const uint32_t g_word_d = 0x76543210u;

const char *
md5_hash(const void *buf, size_t buf_size) {}
=======
/*   Created: 2024/07/03 17:14:18 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/05 12:28:16 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/md5.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static const uint32_t g_sin_tab[4][16] = {{0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                                           0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821},
                                          {0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x2441453, 0xd8a1e681, 0xe7d3fbc8,
                                           0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a},
                                          {0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                                           0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665},
                                          {0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                                           0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391}};

static const uint8_t g_shift_tab[4][16] = {{7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22},
                                           {5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20},
                                           {4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23},
                                           {6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21}};

static const uint8_t g_pad_tab[64] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/**
 * @brief
 *
 * @return t_md5_ctx* the md5 context, or NULL if an error occured.
 */
t_md5_ctx *
init_md5_ctx(void) {
    t_md5_ctx *md5_ctx = NULL;

    if ((md5_ctx = calloc(sizeof(*md5_ctx), 1)) == NULL) {
        return (NULL);
    }

    md5_ctx->state[0] = A;
    md5_ctx->state[1] = B;
    md5_ctx->state[2] = C;
    md5_ctx->state[3] = D;

    return (md5_ctx);
}

/**
 * @brief Apply the 4 rounds on a 512-bit block, then mutate the state of the md5 context.
 *
 * @param md5_ctx The MD5 context.
 */
void
md5_step(t_md5_ctx *md5_ctx) {
    uint32_t a = 0;
    uint32_t b = 0;
    uint32_t c = 0;
    uint32_t d = 0;

    a = md5_ctx->state[0];
    b = md5_ctx->state[1];
    c = md5_ctx->state[2];
    d = md5_ctx->state[3];

    /* First Round */

    FF(a, b, c, d, md5_ctx->buffer[0], g_shift_tab[0][0], g_sin_tab[0][0]);
    FF(d, a, b, c, md5_ctx->buffer[1], g_shift_tab[0][1], g_sin_tab[0][1]);
    FF(c, d, a, b, md5_ctx->buffer[2], g_shift_tab[0][2], g_sin_tab[0][2]);
    FF(b, c, d, a, md5_ctx->buffer[3], g_shift_tab[0][3], g_sin_tab[0][3]);
    FF(a, b, c, d, md5_ctx->buffer[4], g_shift_tab[0][4], g_sin_tab[0][4]);
    FF(d, a, b, c, md5_ctx->buffer[5], g_shift_tab[0][5], g_sin_tab[0][5]);
    FF(c, d, a, b, md5_ctx->buffer[6], g_shift_tab[0][6], g_sin_tab[0][6]);
    FF(b, c, d, a, md5_ctx->buffer[7], g_shift_tab[0][7], g_sin_tab[0][7]);
    FF(a, b, c, d, md5_ctx->buffer[8], g_shift_tab[0][8], g_sin_tab[0][8]);
    FF(d, a, b, c, md5_ctx->buffer[9], g_shift_tab[0][9], g_sin_tab[0][9]);
    FF(c, d, a, b, md5_ctx->buffer[10], g_shift_tab[0][10], g_sin_tab[0][10]);
    FF(b, c, d, a, md5_ctx->buffer[11], g_shift_tab[0][11], g_sin_tab[0][11]);
    FF(a, b, c, d, md5_ctx->buffer[12], g_shift_tab[0][12], g_sin_tab[0][12]);
    FF(d, a, b, c, md5_ctx->buffer[13], g_shift_tab[0][13], g_sin_tab[0][13]);
    FF(c, d, a, b, md5_ctx->buffer[14], g_shift_tab[0][14], g_sin_tab[0][14]);
    FF(b, c, d, a, md5_ctx->buffer[15], g_shift_tab[0][15], g_sin_tab[0][15]);

    /* Second Round */

    GG(a, b, c, d, md5_ctx->buffer[1], g_shift_tab[1][0], g_sin_tab[1][0]);
    GG(d, a, b, c, md5_ctx->buffer[6], g_shift_tab[1][1], g_sin_tab[1][1]);
    GG(c, d, a, b, md5_ctx->buffer[11], g_shift_tab[1][2], g_sin_tab[1][2]);
    GG(b, c, d, a, md5_ctx->buffer[0], g_shift_tab[1][3], g_sin_tab[1][3]);
    GG(a, b, c, d, md5_ctx->buffer[5], g_shift_tab[1][4], g_sin_tab[1][4]);
    GG(d, a, b, c, md5_ctx->buffer[10], g_shift_tab[1][5], g_sin_tab[1][5]);
    GG(c, d, a, b, md5_ctx->buffer[15], g_shift_tab[1][6], g_sin_tab[1][6]);
    GG(b, c, d, a, md5_ctx->buffer[4], g_shift_tab[1][7], g_sin_tab[1][7]);
    GG(a, b, c, d, md5_ctx->buffer[9], g_shift_tab[1][8], g_sin_tab[1][8]);
    GG(d, a, b, c, md5_ctx->buffer[14], g_shift_tab[1][9], g_sin_tab[1][9]);
    GG(c, d, a, b, md5_ctx->buffer[3], g_shift_tab[1][10], g_sin_tab[1][10]);
    GG(b, c, d, a, md5_ctx->buffer[8], g_shift_tab[1][11], g_sin_tab[1][11]);
    GG(a, b, c, d, md5_ctx->buffer[13], g_shift_tab[1][12], g_sin_tab[1][12]);
    GG(d, a, b, c, md5_ctx->buffer[2], g_shift_tab[1][13], g_sin_tab[1][13]);
    GG(c, d, a, b, md5_ctx->buffer[7], g_shift_tab[1][14], g_sin_tab[1][14]);
    GG(b, c, d, a, md5_ctx->buffer[12], g_shift_tab[1][15], g_sin_tab[1][15]);

    md5_ctx->state[0] += a;
    md5_ctx->state[1] += b;
    md5_ctx->state[2] += c;
    md5_ctx->state[3] += d;
}
>>>>>>> e7c1b132145dcf98a5eca497fe704b7ee188ec78
