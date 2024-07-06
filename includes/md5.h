/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:15:43 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/06 14:40:40 by plouvel          ###   ########.fr       */
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
#define MD5_BLK_LEN_WORD 16

typedef struct s_md5_ctx {
    size_t   mlen;
    size_t   boff;
    uint32_t buff[MD5_BLK_LEN_WORD];
    uint32_t state[MD5_STATE];
} t_md5_ctx;

/**
 * @brief Perform a left rotation on a 32-bit value.
 */
#define L_ROT_32(X, N) (((X) << (N)) | ((X) >> (32 - (N))))

// t_md5_ctx init_md5_ctx(void);
// void      md5_step(t_md5_ctx* md5_ctx);
// void      md5_transform(t_md5_ctx* md5_ctx, const uint8_t* buff, size_t buff_len);

int md5_str(const char *str, void **digest, size_t *ldigest);
int md5_fd(int fd, void **digest, size_t *ldigest);

#endif
