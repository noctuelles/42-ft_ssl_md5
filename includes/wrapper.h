/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:52:52 by plouvel           #+#    #+#             */
/*   Updated: 2024/07/08 18:55:44 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
#define WRAPPER_H

#include <stddef.h>
#include <sys/types.h>

void*   Malloc(size_t size);
ssize_t Read(int fd, void* buf, size_t count);

#endif