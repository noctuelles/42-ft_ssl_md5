/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:23:46 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/09 11:55:59 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
#define SHA256_H

#include <stddef.h>
#include <stdint.h>

#include "utils.h"

/**
 * @brief The SHA-256 digest size in bytes.
 *
 */
#define SHA256_DIGEST_SIZE (32)
#define SHA256_BUFF_SIZE_BYTE (64)

typedef struct s_sha256_ctx {
    size_t   mlen;
    size_t   boff;
    uint8_t  buff[64];
    uint32_t state[8];
} t_sha256_ctx;

/**
 * @brief  SHA-224 and SHA-256 logicial functions. Each function operate on
 * 32-bit words.
 */

#define CH(X, Y, Z) (((X) & (Y)) ^ (~(X) & (Z)))
#define MAJ(X, Y, Z) (((X) & (Y)) ^ ((X) & (Z)) ^ ((Y) & (Z)))

#define SSIG0(X) (R_ROT_32(X, 7) ^ R_ROT_32(X, 18) ^ ((X) >> 3))
#define SSIG1(X) (R_ROT_32(X, 17) ^ R_ROT_32(X, 19) ^ ((X) >> 10))

#define W(w, T) \
    ((w)[(T) - 16] + SSIG0((w)[(T) - 15]) + (w)[(T) - 7] + SSIG1((w)[(T) - 2]))

#define BSIG0(X) (R_ROT_32(X, 2) ^ R_ROT_32(X, 13) ^ R_ROT_32(X, 22))
#define BSIG1(X) (R_ROT_32(X, 6) ^ R_ROT_32(X, 11) ^ R_ROT_32(X, 25))

int sha256_init(void *ctx);
int sha256_update(void *ctx, const uint8_t *buff, size_t bsize);
int sha256_finalize(void *ctx, uint8_t *dgst);

#endif