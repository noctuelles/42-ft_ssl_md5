/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:14:18 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/08 00:25:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file md5.c
 * @brief The MD5 algorithm is implemented in a stream fashion : instead of
 * gathering the whole message, and add the padding bits, we perform a step
 * whenever 512 bits (or 64 bytes) are gathered.
 *
 */

#include "includes/md5.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief The sines values used in the MD5 algorithm. Computed as 2^32 *
 * abs(sin(i)) where i is in radians.
 *
 */
static const uint32_t g_sines[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
    0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
    0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x2441453,  0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
    0xd4ef3085, 0x4881d05,  0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
    0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

/**
 * @brief The shifts values used in the MD5 algorithm.
 *
 */
static const uint8_t g_shifts[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

/**
 * @brief The padding used in the MD5 algorithm. At least 1 byte of padding is
 * used, and at most 64 bytes.
 *
 */
static const uint8_t g_pads[64] = {
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/**
 * @brief Initialize MD5 context.
 *
 * @return t_md5_ctx md5 context.
 */
t_md5_ctx
md5_init(void) {
    t_md5_ctx md5_ctx = {0};

    md5_ctx.state[0] = 0x67452301;
    md5_ctx.state[1] = 0xEFCDAB89;
    md5_ctx.state[2] = 0x98BADCFE;
    md5_ctx.state[3] = 0x10325476;

#ifdef VERBOSE
    fprintf(stderr, "[MD5] Initialization of the MD5 state.\n");
#endif
    return (md5_ctx);
}

/**
 * @brief Apply the 4 rounds (16 operations per round) on a 512-bit block.
 *
 * @param md5_ctx md5 context.
 */
void
md5_step(t_md5_ctx *md5_ctx) {
    uint32_t        a = 0, b = 0, c = 0, d = 0, f = 0, g = 0;
    const uint32_t *input = (const uint32_t *)md5_ctx->buff;

    a = md5_ctx->state[0];
    b = md5_ctx->state[1];
    c = md5_ctx->state[2];
    d = md5_ctx->state[3];
    for (size_t i = 0; i < 64; i++) {
        if (FIRST_ROUND(i)) {
            f = F(b, c, d);
            g = i;
        } else if (SECOND_ROUND(i)) {
            f = G(b, c, d);
            g = (5 * i + 1) % 16;
        } else if (THIRD_ROUND(i)) {
            f = H(b, c, d);
            g = (3 * i + 5) % 16;
        } else if (FOURTH_ROUND(i)) {
            f = I(b, c, d);
            g = (7 * i) % 16;
        }
        f += a + g_sines[i] + input[g];
        a = d;
        d = c;
        c = b;
        b += L_ROT_32(f, g_shifts[i]);
    }
    md5_ctx->state[0] += a;
    md5_ctx->state[1] += b;
    md5_ctx->state[2] += c;
    md5_ctx->state[3] += d;
}

/**
 * @brief Transform a buffer of size n, in distinct 512-bit block that can be
 * process by the MD5 algorithm.
 *
 * @param md5_ctx MD5 context.
 * @param buff Buffer.
 * @param bsize Buffer size.
 */
void
md5_transform(t_md5_ctx *md5_ctx, const uint8_t *buff, size_t bsize) {
    while (bsize) {
        const size_t buntil_full = MD5_BUFF_SIZE_BYTE - md5_ctx->boff;
        const size_t consumed    = MIN(buntil_full, bsize);

        memcpy(&md5_ctx->buff[md5_ctx->boff], buff, consumed);

        bsize -= consumed, buff += consumed, md5_ctx->boff += consumed,
            md5_ctx->mlen += consumed;

        if (md5_ctx->boff == MD5_BUFF_SIZE_BYTE) {
#ifdef VERBOSE
            fputs(stderr, "[MD5] Processing a 512-bit block...");
#endif
            md5_step(md5_ctx);
            md5_ctx->boff = 0;
        }
    }
}

/**
 * @brief Finalize the MD5 digest by appending padding bits and the message
 * length.
 *
 * @param md5_ctx
 */
void
md5_finalize(t_md5_ctx *md5_ctx) {
    const uint64_t len_before_pad = md5_ctx->mlen * 8;
    const size_t   npad =
        md5_ctx->boff < 56 ? 56 - md5_ctx->boff : 120 - md5_ctx->boff;

    md5_transform(md5_ctx, g_pads, npad);
    md5_transform(md5_ctx, (const uint8_t *)&len_before_pad,
                  sizeof(len_before_pad));
#ifdef VERBOSE
    fprintf(stderr, "[MD5] End of message.\n");
    fprintf(stderr, "[MD5] Padding with one 1 and %lu 0.", (npad - 1) * 8);
    fprintf(stderr, "[MD5] Padding with message size of %lu bits.", org_len);
#endif
}

/**
 * @brief
 *
 * @param md5_ctx md5 context.
 * @param digest result-argument, store the memory location of the digest.
 * @param ldigest result-argument, store the size of the digest.
 * @return int 0, or -1 otherwise.
 */
int
md5_digest(const t_md5_ctx *md5_ctx, void **digest, size_t *ldigest) {
    void  *rslt = NULL;
    size_t size = sizeof(md5_ctx->state);

    if ((rslt = malloc(size)) == NULL) {
        return (-1);
    }
    memcpy(rslt, md5_ctx->state, size);
    *digest  = rslt;
    *ldigest = size;
    return (0);
}

int
md5_str(const char *str, void **digest, size_t *ldigest) {
    t_md5_ctx ctx = md5_init();

    md5_transform(&ctx, (const uint8_t *)str, strlen(str));
    md5_finalize(&ctx);
    if (md5_digest(&ctx, digest, ldigest) == -1) {
        return (-1);
    }
    return (0);
}

int
md5_fd(int fd, void **digest, size_t *ldigest) {
    t_md5_ctx ctx                       = md5_init();
    ssize_t   ret                       = 0;
    uint8_t   buff[READ_BUFF_SIZE_BYTE] = {0};

    while ((ret = read(fd, buff, sizeof(buff))) > 0) {
        md5_transform(&ctx, buff, (size_t)ret);
    }
    if (ret == -1) {
        return (-1);
    }
    md5_finalize(&ctx);
    if (md5_digest(&ctx, digest, ldigest) == -1) {
        return (-1);
    }
    return (0);
}
