/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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
