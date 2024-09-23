/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:25:29 by plouvel           #+#    #+#             */
/*   Updated: 2024/09/23 19:36:50 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Perform a left rotation on a 32-bit value.
 */
#define L_ROT_32(X, N) (((X) << (N)) | ((X) >> (32 - (N))))

/**
 * @brief Perform a right rotation on a 32-bit value.
 */
#define R_ROT_32(X, N) (((X) >> (N)) | ((X) << (32 - (N))))

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define LE_TO_BE(X) (((X) << 24) | (((X) & 0xff00) << 8) | (((X) >> 8) & 0xff00) | ((X) >> 24))

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define BSWAP64(X) __builtin_bswap64(X)
#define BSWAP32(X) __builtin_bswap32(X)
#define BSWAP16(X) __builtin_bswap16(X)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define BSWAP64(X) (X)
#define BSWAP32(X) (X)
#define BSWAP16(X) (X)
#else
#error "Huh?"
#endif

#endif
