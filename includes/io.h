/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:07:30 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/04 13:37:06 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
#define IO_H

#include <stddef.h>

#define DFT_BUFF_SIZE (1 << 10)

int get_fd_buff(int fd, void **rslt_buff, size_t *rslt_buff_size);

#endif