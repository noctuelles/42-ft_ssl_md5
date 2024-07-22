/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:56:11 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/22 12:23:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>

#include "ft_args_parser.h"
#include "opts.h"

static int parse_echo_stdin(const char *arg, t_args_parser_state *state,
                            void *input);
static int parse_quiet(const char *arg, t_args_parser_state *state,
                       void *input);
static int parse_reverse(const char *arg, t_args_parser_state *state,
                         void *input);
static int parse_string(const char *arg, t_args_parser_state *state,
                        void *input);
static int parse_filename(const char *arg, t_args_parser_state *state,
                          void *input);

static t_args_parser_option_entry g_sha256_entries[] = {
    {
        .description = "echo STDIN to STDOUT and append the checksum to STDOUT",
        .short_key   = "p",
        .long_key    = "echo-stdin",
        .long_key_argument_description = NULL,
        .parse_fn                      = parse_echo_stdin,
        .has_argument                  = false,
    },
    {
        .description                   = "quiet mode",
        .short_key                     = "q",
        .long_key                      = "quiet",
        .long_key_argument_description = NULL,
        .parse_fn                      = parse_quiet,
        .has_argument                  = false,
    },
    {
        .description                   = "reverse the format of the output",
        .short_key                     = "r",
        .long_key                      = "reverse",
        .long_key_argument_description = NULL,
        .parse_fn                      = parse_reverse,
        .has_argument                  = false,
    },
    {
        .description                   = "print the sum of the given string",
        .short_key                     = "s",
        .long_key                      = "string",
        .long_key_argument_description = "STR",
        .parse_fn                      = parse_string,
        .has_argument                  = true,
    }};

t_args_parser_config g_sha256_conf = {
    .argv                      = NULL,
    .argc                      = 0,
    .input                     = NULL,
    .default_argument_parse_fn = parse_filename,
    .entries                   = g_sha256_entries,
    .entries_nbr = sizeof(g_sha256_entries) / sizeof(g_sha256_entries[0]),
    .stop_opts_parsing_on_first_non_opt = true,
};

static int
parse_echo_stdin(const char *arg, t_args_parser_state *state, void *input) {
    (void)arg;
    (void)state;

    t_sha256_opts *opts = (t_sha256_opts *)input;

    opts->echo_stdin_to_stdout = true;

    return (0);
}

static int
parse_quiet(const char *arg, t_args_parser_state *state, void *input) {
    (void)arg;
    (void)state;

    t_sha256_opts *opts = (t_sha256_opts *)input;

    opts->quiet = true;

    return (0);
}

static int
parse_reverse(const char *arg, t_args_parser_state *state, void *input) {
    (void)arg;
    (void)state;

    t_sha256_opts *opts = (t_sha256_opts *)input;

    opts->reverse = true;

    return (0);
}

static int
parse_string(const char *arg, t_args_parser_state *state, void *input) {
    (void)arg;
    (void)state;

    t_sha256_opts *opts = (t_sha256_opts *)input;

    opts->str = arg;

    return (0);
}

static int
parse_filename(const char *arg, t_args_parser_state *state, void *input) {
    t_sha256_opts *opts = (t_sha256_opts *)input;
    t_list        *elem = NULL;

    if ((elem = ft_lstnew((void *)arg)) == NULL) {
        ft_lstclear(&opts->files, NULL);
        state->error_message = strerror(errno);
        return (-1);
    }
    ft_lstadd_back(&opts->files, elem);
    return (0);
}