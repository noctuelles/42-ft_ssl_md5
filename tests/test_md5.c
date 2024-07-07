/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:23:22 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/08 00:05:26 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/md5.h"
#include "unity.h"

#define STATIC_STRLEN(str) (sizeof((str)) - 1)

static t_md5_ctx g_md5_ctx = {0};

t_md5_ctx md5_init(void);
void      md5_transform(t_md5_ctx *md5_ctx, const uint8_t *buff, size_t blen);
void      md5_finalize(t_md5_ctx *md5_ctx);

void
setUp(void) {
    g_md5_ctx = md5_init();
}

void
tearDown(void) {}

void
test_L_ROT_32() {
    TEST_ASSERT_EQUAL_UINT32(0x00000001, L_ROT_32(0x80000000, 1));
}

void
test_md5_transform_EXACT() {
    const char buff[] =
        "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";

    md5_transform(&g_md5_ctx, buff, sizeof(buff) - 1);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(buff, g_md5_ctx.buff, sizeof(buff) - 1);
}

void
test_md5_transform_NOT_EXACT() {
    const char buff[]  = "abcdabcdabcdabcdabcdabcdabcdabcd";
    const char buff2[] = "abcda";

    md5_transform(&g_md5_ctx, buff, STATIC_STRLEN(buff));
    md5_transform(&g_md5_ctx, buff, STATIC_STRLEN(buff2));
    md5_transform(&g_md5_ctx, buff, STATIC_STRLEN(buff));

    TEST_ASSERT_EQUAL(STATIC_STRLEN(buff) - STATIC_STRLEN(buff2),
                      g_md5_ctx.boff);
}

void
test_md5_finalize_LOW() {
    const char buff[] = "abcdabcdabcdabcdabcdabcdabccdabcdabcdabcdabcdabcdabc";

    md5_transform(&g_md5_ctx, buff, STATIC_STRLEN(buff));
    md5_finalize(&g_md5_ctx);
}

void
test_md5_finalize_HIGH() {
    const char buff[] =
        "1abcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcdabcd";

    md5_transform(&g_md5_ctx, buff, STATIC_STRLEN(buff));
    md5_finalize(&g_md5_ctx);
}

int
main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_L_ROT_32);
    RUN_TEST(test_md5_transform_EXACT);
    RUN_TEST(test_md5_transform_NOT_EXACT);
    RUN_TEST(test_md5_finalize_LOW);
    RUN_TEST(test_md5_finalize_HIGH);
    return (UNITY_END());
}