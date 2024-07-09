/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:26:53 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/09 11:37:50 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "utils.h"

void
setUp(void) {}

void
tearDown(void) {}

void
test_R_ROT_32() {
    uint32_t x = 0b00000000000000000000000000001111;

    TEST_ASSERT_BITS(0xFFFFFFFF, 0b10000000000000000000000000000111,
                     R_ROT_32(x, 1));
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b11000000000000000000000000000011,
                     R_ROT_32(x, 2));
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b11110000000000000000000000000000,
                     R_ROT_32(x, 4));
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00000111100000000000000000000000,
                     R_ROT_32(x, 9));
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00000000000000000000000000011110,
                     R_ROT_32(x, 31));
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00000000000000000000000000001111,
                     R_ROT_32(x, 32));
}

void
test_L_ROT_32() {
    uint32_t x = 0b00000000000000000000000000001111;

    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00000000000000000000000000011110,
                     L_ROT_32(x, 1));
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00000000000000000000000000111100,
                     L_ROT_32(x, 2));
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00000000000000000000000011110000,
                     L_ROT_32(x, 4));
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00000000000000000001111000000000,
                     L_ROT_32(x, 9));
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b10000000000000000000000000000111,
                     L_ROT_32(x, 31));
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00000000000000000000000000001111,
                     L_ROT_32(x, 32));
}

int
main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_R_ROT_32);
    RUN_TEST(test_L_ROT_32);
    return UNITY_END();
}