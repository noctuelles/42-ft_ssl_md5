/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:20:49 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/08 16:12:28 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_args_parser.h"
#include "ft_ssl.h"
#include "utils.h"

static const t_args_parser_option_entry g_md5_opts_entries[] = {
    {
        .short_key   = "p",
        .long_key    = "echo-stdin",
        .description = "echo STDIN to STDOUT and append the checksum to STDOUT",
        .has_argument                  = false,
        .long_key_argument_description = NULL,
        .parse_fn                      = NULL,
    },
    {
        .short_key                     = "q",
        .long_key                      = "quiet",
        .description                   = "quiet mode",
        .has_argument                  = false,
        .long_key_argument_description = NULL,
        .parse_fn                      = NULL,
    },
    {
        .short_key                     = "r",
        .long_key                      = "reverse",
        .description                   = "reverse the format of the output",
        .has_argument                  = false,
        .long_key_argument_description = NULL,
        .parse_fn                      = NULL,
    },
    {
        .short_key                     = "s",
        .long_key                      = "string",
        .description                   = "print the sum of the given string",
        .has_argument                  = true,
        .long_key_argument_description = "STR",
        .parse_fn                      = NULL,

    }};

static const t_args_parser_option_entry g_sha256_opts_entries[] = {
    {
        .short_key   = "p",
        .long_key    = "echo-stdin",
        .description = "echo STDIN to STDOUT and append the checksum to STDOUT",
        .has_argument                  = false,
        .long_key_argument_description = NULL,
        .parse_fn                      = NULL,
    },
    {
        .short_key                     = "q",
        .long_key                      = "quiet",
        .description                   = "quiet mode",
        .has_argument                  = false,
        .long_key_argument_description = NULL,
        .parse_fn                      = NULL,
    },
    {
        .short_key                     = "r",
        .long_key                      = "reverse",
        .description                   = "reverse the format of the output",
        .has_argument                  = false,
        .long_key_argument_description = NULL,
        .parse_fn                      = NULL,
    },
    {
        .short_key                     = "s",
        .long_key                      = "string",
        .description                   = "print the sum of the given string",
        .has_argument                  = true,
        .long_key_argument_description = "STR",
        .parse_fn                      = NULL,
    }};

t_args_parser_config g_md5_opts_config = {
    .argc                               = 0,
    .argv                               = NULL,
    .entries                            = g_md5_opts_entries,
    .entries_nbr                        = NSIZE(g_md5_opts_entries),
    .stop_opts_parsing_on_first_non_opt = true,
    .default_argument_parse_fn          = NULL,
    .input                              = NULL,
};
