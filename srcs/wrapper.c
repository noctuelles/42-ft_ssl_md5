/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:52:04 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/22 13:03:17 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

void *
Malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        ft_error(0, errno, "malloc");
    }
    return ptr;
}

ssize_t
Read(int fd, void *buf, size_t count) {
    ssize_t ret = read(fd, buf, count);
    if (ret == -1) {
        ft_error(0, errno, "read");
    }
    return ret;
}

int
Open(const char *pathname, int flags) {
    int fd = open(pathname, flags);
    if (fd == -1) {
        ft_error(0, errno, "open");
    }
    return fd;
}

int
Close(int fd) {
    int ret = close(fd);
    if (ret == -1) {
        ft_error(0, errno, "close");
    }
    return ret;
}