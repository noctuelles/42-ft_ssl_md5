/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:25:29 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/09 16:03:32 by plouvel          ###   ########.fr       */
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

#define LE_TO_BE(X) \
    (((X) << 24) | (((X) & 0xff00) << 8) | (((X) >> 8) & 0xff00) | ((X) >> 24))

#endif
