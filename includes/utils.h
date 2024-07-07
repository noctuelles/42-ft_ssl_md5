/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:25:29 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/07 23:40:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Perform a left rotation on a 32-bit value.
 */
#define L_ROT_32(X, N) (((X) << (N)) | ((X) >> (32 - (N))))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#endif
