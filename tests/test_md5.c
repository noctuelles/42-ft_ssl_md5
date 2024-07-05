/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:23:22 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/04 15:54:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "unity.h"

void
setUp(void) {}

void
tearDown(void) {}

void
test_L_ROT_32() {
    TEST_ASSERT_EQUAL_UINT32(0x00000001, L_ROT_32(0x80000000, 1));
}

/**
 * @brief This is the equivalent of the truth table of F.
 *
 */
void
test_F() {
    TEST_ASSERT_EQUAL(0, F(0, 0, 0));
    TEST_ASSERT_EQUAL(0, F(1, 0, 0));
    TEST_ASSERT_EQUAL(0, F(0, 1, 0));
    TEST_ASSERT_EQUAL(1, F(0, 0, 1));
    TEST_ASSERT_EQUAL(1, F(1, 1, 0));
    TEST_ASSERT_EQUAL(1, F(0, 1, 1));
    TEST_ASSERT_EQUAL(0, F(1, 0, 1));
    TEST_ASSERT_EQUAL(1, F(1, 1, 1));
}

void
test_G() {
    /* The only time G is true, is when either X and Z is true, or, Y is true and Z is false. */

    TEST_ASSERT_EQUAL(0, G(0, 0, 0));
    TEST_ASSERT_EQUAL(0, G(1, 0, 0));
    TEST_ASSERT_EQUAL(1, G(0, 1, 0));
    TEST_ASSERT_EQUAL(0, G(0, 0, 1));
    TEST_ASSERT_EQUAL(1, G(1, 1, 0));
    TEST_ASSERT_EQUAL(0, G(0, 1, 1));
    TEST_ASSERT_EQUAL(1, G(1, 0, 1));
    TEST_ASSERT_EQUAL(1, G(1, 1, 1));
}

int
main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_L_ROT_32);
    RUN_TEST(test_F);
    RUN_TEST(test_G);
    return (UNITY_END());
}