/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sha256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:38:29 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/09 13:02:29 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/sha256.h"
#include "unity.h"
#include "utils.h"

void
setUp(void) {}

void
tearDown(void) {}

void
test_SSIG0() {
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00010001000000000010000000000000,
                     SSIG0(0b10000000000000000000000000000000));

    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00010100000001000100101010101000,
                     SSIG0(0b00000000001000000101000000000000));

    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00000110000001000000100110010000,
                     SSIG0(0b00100010000000000000100000000000));

    TEST_ASSERT_BITS(0xFFFFFFFF, 0b10100001111110111000001011000000,
                     SSIG0(0b00000101000010001001010101000010));
}

void
test_SSIG1() {
    TEST_ASSERT_BITS(0xFFFFFFFF, 0b01000100000000000001000000000000,
                     SSIG1(0b00000000010000001010000000000000));

    TEST_ASSERT_BITS(0xFFFFFFFF, 0b00001111000110011011111111000110,
                     SSIG1(0b01100110000000000001100000000000));

    TEST_ASSERT_BITS(0xFFFFFFFF, 0b01010110010001011111100101011100,
                     SSIG1(0b11010110001000100010010110000000));

    TEST_ASSERT_BITS(0xFFFFFFFF, 0b01100000001000000000000000000000,
                     SSIG1(0b00010100001000100101010100001000));

    TEST_ASSERT_BITS(0xFFFFFFFF, 0b000000000001000000101000000000000,
                     SSIG1(0b10000000000000000000000000000000));
}

int
main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_SSIG0);
    RUN_TEST(test_SSIG1);
    return UNITY_END();
}