/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:28:20 by plouvel           #+#    #+#             */
/*   Updated: 2024/09/23 17:11:45 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
#define COMMAND_H

#include "ft_ssl.h"

int handle_sha256(const t_command *cmd, void *opts);
int handle_md5(const t_command *cmd, void *opts);
int handle_whirlpool(const t_command *cmd, void *opts);

#endif