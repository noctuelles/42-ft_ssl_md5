/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:25:04 by plouvel           #+#    #+#             */
/*   Updated: 2024/09/24 16:32:27 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <poll.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ft_ssl.h"
#include "md5.h"
#include "opts.h"
#include "sha256.h"
#include "wrapper.h"

/**
 * @brief Print the digest to stdout.
 *
 * @param digest The digest to print.
 * @param ldigest The length of the digest.
 */
static void
print_digest(const uint8_t *digest, size_t ldigest) {
    size_t i = 0;

    while (i < ldigest) {
        printf("%02x", digest[i]);
        i++;
    }
}

/**
 * @brief Print the input from a buffer to stdout in a human readable format.
 *
 * @param buffer The buffer to print.
 * @param buffer_size The size of the buffer.
 */
static void
print_stdin_stdout_echo(const uint8_t buffer[BUFFER_SIZE], size_t buffer_size) {
    for (size_t i = 0; i < buffer_size; i++) {
        if (ft_isprint(buffer[i])) {
            putc(buffer[i], stdout);
        } else {
            fprintf(stdout, "\\x%02x", buffer[i]);
        }
    }
}

/**
 * @brief Process the input from a file descriptor.
 *
 * @param input The input to process, in this case, a file descriptor.
 * @param nbytes_read The number of bytes read.
 * @param fail A boolean to indicate any failure from this routine.
 */
const uint8_t *
proc_input_fd(union u_input input, size_t *nbytes_read, bool *fail) {
    static uint8_t buffer[BUFFER_SIZE] = {0};
    ssize_t        ret                 = 0;

    *fail = false;
    ret   = Read(input.fd, buffer, sizeof(buffer));
    if (ret < 0) {
        *nbytes_read = 0;
        *fail        = true;
    } else {
        *nbytes_read = (size_t)ret;
    }
    return (buffer);
}

/**
 * @brief Process the input from a string.
 *
 * @param input The input to process, in this case, a string.
 * @param nbytes_read The number of bytes read.
 * @param fail A boolean to indicate any failure from this routine. This routine
 * doesn't rely on any external resources, so it never fail.
 */
const uint8_t *
proc_input_str(union u_input input, size_t *nbytes_read, bool *fail) {
    static bool already_proc = false;

    *fail = false;
    if (!already_proc) {
        *nbytes_read = strlen(input.str);
        already_proc = true;
    } else {
        *nbytes_read = 0;
    }
    return ((const uint8_t *)input.str);
}

/**
 * @brief Return the digest of an input by the cryptographic hash function cmd.
 *
 * @param input The input to hash.
 * @param proc_input_fn The function to process the input.
 * @param cmd The command to use.
 * @return uint8_t* The digest of the input.
 */
static uint8_t *
digest_msg(union u_input input, t_proc_input_fn proc_input_fn, const t_command *cmd, bool echo_input) {
    uint8_t       *dgst = NULL;
    void          *ctx = ctx   = NULL;
    const uint8_t *buffer      = NULL;
    size_t         nbytes_read = 0;
    bool           fail        = false;

    if ((dgst = Malloc(cmd->dgst_size)) == NULL) {
        goto ret;
    }
    if ((ctx = Malloc(cmd->ctx_size)) == NULL) {
        goto free_dgst;
    }
    if (cmd->dgst_fnct.dgst_init(ctx) != 0) {
        ft_error(0, 0, "failed to initialize %s", cmd->name);
        goto free_dgst;
    }
    while ((buffer = proc_input_fn(input, &nbytes_read, &fail)) && nbytes_read > 0) {
        if (echo_input == true) {
            print_stdin_stdout_echo(buffer, nbytes_read);
        }
        if (cmd->dgst_fnct.dgst_update(ctx, buffer, nbytes_read) != 0) {
            ft_error(0, 0, "failed to update %s", cmd->name);
            goto free_dgst;
        }
    }
    if (fail) {
        goto free_dgst;
    }
    if (cmd->dgst_fnct.dgst_finalize(ctx, dgst) != 0) {
        ft_error(0, 0, "failed to finalize %s", cmd->name);
        goto free_dgst;
    }
    goto free_ctx;
free_dgst:
    free(dgst);
    dgst = NULL;
free_ctx:
    free(ctx);
    ctx = NULL;
ret:
    return (dgst);
}

/**
 * @brief Handle the MD5 command.
 *
 * @param cmd The command to handle.
 * @param opts The options associated with the command.
 * @return int
 *
 * @note handle_md5 and handler_sha256 are extremely similar. In fact, they
 * clearly violate the DRY principle. But we have to keep them separate even if
 * they have the same options.
 */
int
handle_md5(const t_command *cmd, void *opts) {
    t_md5_opts   *md5_opts = opts;
    const char   *filename = NULL;
    uint8_t      *dgst     = NULL;
    union u_input input;
    int           fd = -1;

    if (stdin_has_data() || (!md5_opts->files && !md5_opts->str)) {
        bool echo = false;

        input.fd = STDIN_FILENO;
        if (!md5_opts->quiet && !md5_opts->reverse) {
            printf("MD5(");
            if (md5_opts->echo_stdin_to_stdout) {
                echo = true;
                printf("\"");
            } else {
                printf("stdin");
            }
        }
        if ((dgst = digest_msg(input, proc_input_fd, cmd, echo)) == NULL) {
            return (1);
        }
        if (!md5_opts->quiet && !md5_opts->reverse) {
            if (md5_opts->echo_stdin_to_stdout) {
                printf("\"");
            }
            printf(")= ");
        }
        print_digest(dgst, cmd->dgst_size);
        if (!md5_opts->quiet) {
            if (md5_opts->reverse) {
                printf("  stdin");
            }
        }
        printf("\n");
    }

    if (md5_opts->str) {
        input.str = md5_opts->str;
        if (!md5_opts->quiet && !md5_opts->reverse) {
            printf("MD5(\"%s\")= ", md5_opts->str);
        }
        if ((dgst = digest_msg(input, proc_input_str, cmd, false)) == NULL) {
            return (1);
        }
        print_digest(dgst, cmd->dgst_size);
        if (!md5_opts->quiet) {
            if (md5_opts->reverse) {
                printf("  \"%s\"", md5_opts->str);
            }
        }
        printf("\n");
    }

    for (t_list *elem = md5_opts->files; elem != NULL; elem = elem->next) {
        filename = elem->content;

        if ((fd = Open(filename, O_RDONLY)) == -1) {
            return (-1);
        }
        if (!md5_opts->quiet && !md5_opts->reverse) {
            printf("MD5(%s)= ", filename);
        }
        input.fd = fd;
        if ((dgst = digest_msg(input, proc_input_fd, cmd, false)) == NULL) {
            return (-1);
        }
        (void)Close(fd);
        print_digest(dgst, cmd->dgst_size);
        if (!md5_opts->quiet) {
            if (md5_opts->reverse) {
                printf("  %s", filename);
            }
        }
        printf("\n");
    }
    return (0);
}

/**
 * @brief Handle the SHA256 command.
 *
 * @param cmd The command to handle.
 * @param opts The options associated with the command.
 * @return int 0 on success, 1 on failure.
 *
 */
int
handle_sha256(const t_command *cmd, void *opts) {
    t_sha256_opts *sha256_opts = opts;
    const char    *filename    = NULL;
    uint8_t       *dgst        = NULL;
    union u_input  input;
    int            fd = -1;

    if (stdin_has_data() || (!sha256_opts->files && !sha256_opts->str)) {
        bool echo = false;

        input.fd = STDIN_FILENO;
        if (!sha256_opts->quiet && !sha256_opts->reverse) {
            printf("SHA256(");
            if (sha256_opts->echo_stdin_to_stdout) {
                echo = true;
                printf("\"");
            } else {
                printf("stdin");
            }
        }
        if ((dgst = digest_msg(input, proc_input_fd, cmd, echo)) == NULL) {
            return (1);
        }
        if (!sha256_opts->quiet && !sha256_opts->reverse) {
            if (sha256_opts->echo_stdin_to_stdout) {
                printf("\"");
            }
            printf(")= ");
        }
        print_digest(dgst, cmd->dgst_size);
        if (!sha256_opts->quiet) {
            if (sha256_opts->reverse) {
                printf("  stdin");
            }
        }
        printf("\n");
    }

    if (sha256_opts->str) {
        input.str = sha256_opts->str;
        if (!sha256_opts->quiet && !sha256_opts->reverse) {
            printf("SHA256(\"%s\")= ", sha256_opts->str);
        }
        if ((dgst = digest_msg(input, proc_input_str, cmd, false)) == NULL) {
            return (1);
        }
        print_digest(dgst, cmd->dgst_size);
        if (!sha256_opts->quiet) {
            if (sha256_opts->reverse) {
                printf("  \"%s\"", sha256_opts->str);
            }
        }
        printf("\n");
    }

    for (t_list *elem = sha256_opts->files; elem != NULL; elem = elem->next) {
        filename = elem->content;

        if ((fd = Open(filename, O_RDONLY)) == -1) {
            return (-1);
        }
        if (!sha256_opts->quiet && !sha256_opts->reverse) {
            printf("SHA256(%s)= ", filename);
        }
        input.fd = fd;
        if ((dgst = digest_msg(input, proc_input_fd, cmd, false)) == NULL) {
            return (-1);
        }
        (void)Close(fd);
        print_digest(dgst, cmd->dgst_size);
        if (!sha256_opts->quiet) {
            if (sha256_opts->reverse) {
                printf("  %s", filename);
            }
        }
        printf("\n");
    }
    return (0);
}

int
handle_whirlpool(const t_command *cmd, void *opts) {
    t_whirlpool_opts *whirlpool_opts = opts;
    uint8_t          *dgst           = NULL;
    const char       *filename;
    int               fd;
    union u_input     input;

    if (stdin_has_data() || (!whirlpool_opts->files && !whirlpool_opts->str)) {
        input.fd = STDIN_FILENO;
        if (!whirlpool_opts->quiet && !whirlpool_opts->reverse) {
            printf("WHIRLPOOL(stdin)= ");
        }
        if ((dgst = digest_msg(input, proc_input_fd, cmd, false)) == NULL) {
            return (1);
        }
        print_digest(dgst, cmd->dgst_size);
        if (!whirlpool_opts->quiet) {
            if (whirlpool_opts->reverse) {
                printf("  stdin");
            }
        }
        printf("\n");
    }

    if (whirlpool_opts->str) {
        input.str = whirlpool_opts->str;
        if (!whirlpool_opts->quiet && !whirlpool_opts->reverse) {
            printf("WHIRLPOOL(\"%s\")= ", whirlpool_opts->str);
        }
        if ((dgst = digest_msg(input, proc_input_str, cmd, false)) == NULL) {
            return (1);
        }
        print_digest(dgst, cmd->dgst_size);
        if (!whirlpool_opts->quiet) {
            if (whirlpool_opts->reverse) {
                printf("  \"%s\"", whirlpool_opts->str);
            }
        }
        printf("\n");
    }

    for (t_list *elem = whirlpool_opts->files; elem != NULL; elem = elem->next) {
        filename = elem->content;

        if ((fd = Open(filename, O_RDONLY)) == -1) {
            return (-1);
        }
        if (!whirlpool_opts->quiet && !whirlpool_opts->reverse) {
            printf("WHIRLPOOL(%s)= ", filename);
        }
        input.fd = fd;
        if ((dgst = digest_msg(input, proc_input_fd, cmd, false)) == NULL) {
            return (-1);
        }
        (void)Close(fd);
        print_digest(dgst, cmd->dgst_size);
        if (!whirlpool_opts->quiet) {
            if (whirlpool_opts->reverse) {
                printf("  %s", filename);
            }
        }
        printf("\n");
    }

    return (0);
}