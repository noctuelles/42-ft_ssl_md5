/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:23:39 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/08 18:57:42 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/sha256.h"

#include <string.h>

/**
 * @brief These words represent the first 32 bits of the fractional parts of the
 * cube roots of the first sixty-four prime numbers.
 *
 */
static const uint32_t g_cube_roots[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

void
sha256_step(void *ctx) {
    t_sha256_ctx *sha256_ctx = ctx;
    uint32_t      a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0,
             h = 0; /* Working variables */
    uint32_t w[64]; /* Message schedule */

    /* Prepare message schedule */
    memcpy(w, sha256_ctx->buffer, sizeof(sha256_ctx->buffer));
    for (size_t t = 16; t < 64; t++) {
        w[t] = SSIG1(w[t - 2]) + w[t - 7] + SSIG0(w[t - 15]) + w[t - 16];
    }

    /* Initialize the working variables */
    a = sha256_ctx->state[0];
    b = sha256_ctx->state[1];
    c = sha256_ctx->state[2];
    d = sha256_ctx->state[3];
    e = sha256_ctx->state[4];
    f = sha256_ctx->state[5];
    g = sha256_ctx->state[6];
    h = sha256_ctx->state[7];

    /* Main hash computation */
    for (size_t t = 0; t < 64; t++) {
        const uint32_t T1 = h + BSIG1(e) + CH(e, f, g) + g_cube_roots[t] + w[t];
        const uint32_t T2 = BSIG0(a) + MAJ(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    /* Compute intermediate hash value */
    sha256_ctx->state[0] += a;
    sha256_ctx->state[1] += b;
    sha256_ctx->state[2] += c;
    sha256_ctx->state[3] += d;
    sha256_ctx->state[4] += e;
    sha256_ctx->state[5] += f;
    sha256_ctx->state[6] += g;
    sha256_ctx->state[7] += h;
}

int
sha256_init(void *ctx) {
    t_sha256_ctx *sha256_ctx = ctx;

    sha256_ctx->state[0] = 0x6a09e667;
    sha256_ctx->state[1] = 0xbb67ae85;
    sha256_ctx->state[2] = 0x3c6ef372;
    sha256_ctx->state[3] = 0xa54ff53a;
    sha256_ctx->state[4] = 0x510e527f;
    sha256_ctx->state[5] = 0x9b05688c;
    sha256_ctx->state[6] = 0x1f83d9ab;
    sha256_ctx->state[7] = 0x5be0cd19;

    return (0);
}

int
sha256_update(void *ctx, const uint8_t *buff, size_t bsize) {
    t_sha256_ctx *sha256_ctx = ctx;

    (void)bsize;
    (void)sha256_ctx;
    (void)buff;

    return (0);
}

int
sha256_finalize(void *ctx, uint8_t *dgst) {
    t_sha256_ctx *sha256_ctx = ctx;

    (void)sha256_ctx;
    (void)dgst;

    return (0);
}
