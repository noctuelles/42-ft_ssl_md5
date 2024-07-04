/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:58:25 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/04 13:37:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * @brief Get a buffer from a file descriptor
 *
 * @param fd file descriptor
 * @param rslt_buff result-argument for the buffer
 * @param rslt_buff_size result-argument for the buffer size
 * @return int 0 on success, -1 on error
 */
int
get_fd_buff(int fd, void **rslt_buff, size_t *rslt_buff_size) {
    uint8_t  tmp_buff[DFT_BUFF_SIZE] = {0};
    uint8_t *buff = NULL, *newbuff = NULL;
    size_t   buff_size = DFT_BUFF_SIZE, curr_buff_size = 0;
    ssize_t  ret = 0;

    if ((buff = malloc(DFT_BUFF_SIZE * sizeof(*buff))) == NULL) {
        return (-1);
    }
    while ((ret = read(fd, tmp_buff, sizeof(tmp_buff))) > 0) {
        if (curr_buff_size + ret >= buff_size) {
            if ((newbuff = realloc(buff, buff_size * 2)) == NULL) {
                free(buff);
                return (-1);
            } else {
                buff_size *= 2;
                buff = newbuff;
            }
        }
        memcpy(buff + curr_buff_size, tmp_buff, (size_t)ret);
        curr_buff_size += (size_t)ret;
    }
    if (ret < 0) {
        free(buff);
        return (-1);
    }
    *rslt_buff      = buff;
    *rslt_buff_size = (size_t)curr_buff_size;
    return (0);
}