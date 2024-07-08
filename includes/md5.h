/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:15:43 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/08 19:01:39 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
#define MD5_H

/**
 * @file md5.h
 * @note Ressource used :
 *

 */

#include <stddef.h>
#include <stdint.h>

#include "utils.h"

#define MD5_STATE (4)
#define MD5_BUFF_SIZE_BYTE (64)
#define READ_BUFF_SIZE_BYTE (1 << 10)

/**
 * @brief The MD5 digest size in bytes.
 *
 */
#define MD5_DIGEST_SIZE (16)

typedef struct s_md5_ctx {
    uint64_t mlen;                     /* message length*/
    size_t   boff;                     /* buffer offset */
    uint8_t  buff[MD5_BUFF_SIZE_BYTE]; /* buffer (512 bits) */
    uint32_t state[MD5_STATE];         /* state variables */
} t_md5_ctx;

#define F(B, C, D) (((B) & (C)) | (~(B) & (D)))
#define G(B, C, D) (((B) & (D)) | ((C) & ~(D)))
#define H(B, C, D) ((B) ^ (C) ^ (D))
#define I(B, C, D) ((C) ^ ((B) | ~(D)))

#define FIRST_ROUND(I) ((I) <= 15)
#define SECOND_ROUND(I) ((I) >= 16 && (I) <= 31)
#define THIRD_ROUND(I) ((I) >= 32 && (I) <= 47)
#define FOURTH_ROUND(I) ((I) >= 48 && (I) <= 63)

int md5_init(void *ctx);
int md5_update(void *ctx, const uint8_t *buff, size_t bsize);
int md5_finalize(void *ctx, uint8_t *dgst);

#endif
