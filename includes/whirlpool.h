/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whirlpool.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:08:45 by plouvel           #+#    #+#             */
/*   Updated: 2024/09/23 19:32:39 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief WHIRLPOOL uses Merkle-Damgård strengthening and the Miyaguchi-Preneel
 * hashing scheme with a dedicated 512-bit block cipher called W. This consists
 * of the following. The bit string to be hashed is padded with a &lquo;'1'-bit,
 * then with a sequence of '0'-bits, and finally with the original length (in
 * the form of a 256-bit integer value), so that the length after padding is a
 * multiple of 512 bits. The resulting message string is divided into a sequence
 * of 512-bit blocks m1, m2, ... mt which is then used to generate a sequence of
 * intermediate hash values H0, H1, H2, ... Ht. By definition, H0 is a string of
 * 512 '0'-bits. To compute Hi, W encrypts mi using Hi-1 as key, and XORs the
 * resulting ciphertext with both Hi-1 and mi. Finally, the WHIRLPOOL message
 * digest is Ht.
 *
 */

#ifndef WHIRLPOOL_H
#define WHIRLPOOL_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief  Whirlpool cipher block size in bytes.
 *
 */
#define WHIRLPOOL_CIPHER_BLOCK_SIZE (64)
/**
 * @brief Whirlpool digest size in multiple of 64 bit words.
 *
 */
#define WHIRLPOOL_DIGEST_SIZE (8)

typedef struct s_whirlpool_ctx {
    size_t   mlen;
    size_t   boff;
    uint8_t  buff[WHIRLPOOL_CIPHER_BLOCK_SIZE];
    uint64_t hash[WHIRLPOOL_DIGEST_SIZE];
} t_whirlpool_ctx;

#define I64(x) (x##ULL)
#define NBR_ROUNDS (10)

#define WHIRLPOOL_OP(src, shift)                                                                                        \
    (g_whirlpool_sbox[0][(int)(src[shift & 7] >> 56)] ^ g_whirlpool_sbox[1][(int)(src[(shift + 7) & 7] >> 48) & 0xff] ^ \
     g_whirlpool_sbox[2][(int)(src[(shift + 6) & 7] >> 40) & 0xff] ^                                                    \
     g_whirlpool_sbox[3][(int)(src[(shift + 5) & 7] >> 32) & 0xff] ^                                                    \
     g_whirlpool_sbox[4][(int)(src[(shift + 4) & 7] >> 24) & 0xff] ^                                                    \
     g_whirlpool_sbox[5][(int)(src[(shift + 3) & 7] >> 16) & 0xff] ^                                                    \
     g_whirlpool_sbox[6][(int)(src[(shift + 2) & 7] >> 8) & 0xff] ^ g_whirlpool_sbox[7][(int)(src[(shift + 1) & 7]) & 0xff])

int whirlpool_init(void *ctx);
int whirlpool_update(void *ctx, const uint8_t *buff, size_t bsize);
int whirlpool_finalize(void *ctx, uint8_t *dgst);

#endif