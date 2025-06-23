//
// Created by plouvel on 6/23/25.
//

#include "ft_args_parser.h"
#include "opts.h"

static int parse_decode(const char *arg, t_args_parser_state *state,
                            void *input);
static int parse_encode(const char *arg, t_args_parser_state *state,
                       void *input);
static int parse_input_file(const char *arg, t_args_parser_state *state,
                         void *input);
static int parse_output_file(const char *arg, t_args_parser_state *state,
                        void *input);

static t_args_parser_option_entry g_base64_entries[] = {
    {
        .description = "decode mode",
        .short_key   = "d",
        .long_key    = "decode",
        .long_key_argument_description = NULL,
        .parse_fn                      = parse_decode,
        .has_argument                  = false,
    },
    {
        .description                   = "encode mode",
        .short_key                     = "e",
        .long_key                      = "encode",
        .long_key_argument_description = NULL,
        .parse_fn                      = parse_encode,
        .has_argument                  = false,
    },
    {
        .description                   = "input file",
        .short_key                     = "i",
        .long_key                      = "input-file",
        .long_key_argument_description = "FILE",
        .parse_fn                      = parse_input_file,
        .has_argument                  = false,
    },
    {
        .description                   = "output file",
        .short_key                     = "o",
        .long_key                      = "output-file",
        .long_key_argument_description = "FILE",
        .parse_fn                      = parse_output_file,
        .has_argument                  = true,
    }};

t_args_parser_config g_base64_conf = {
    .argv                      = NULL,
    .argc                      = 0,
    .input                     = NULL,
    .default_argument_parse_fn = NULL,
    .entries                   = g_base64_entries,
    .entries_nbr = sizeof(g_base64_entries) / sizeof(g_base64_entries[0]),
    .stop_opts_parsing_on_first_non_opt = true,
};

static int parse_decode(const char *arg, t_args_parser_state *state,
                            void *input) {
    (void)arg;
    (void)state;

    t_base64_opts *opts = input;

    opts->decode = true;

    return 0;
}

static int parse_encode(const char *arg, t_args_parser_state *state,
                       void *input) {
    (void)arg;
    (void)state;

    t_base64_opts *opts = input;

    opts->encode = true;

    return 0;
}

static int parse_input_file(const char *arg, t_args_parser_state *state,
                         void *input) {
    (void)state;

    t_base64_opts *opts = input;

    opts->input_file = arg;

    return 0;
}

static int parse_output_file(const char *arg, t_args_parser_state *state,
                        void *input) {
    (void)state;

    t_base64_opts *opts = input;

    opts->output_file = arg;

    return 0;
}
