/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:05:08 by plouvel           #+#    #+#             */
/*   Updated: 2024/09/24 16:10:06 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <poll.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * @brief Little trick to check if stdin has data. Note that we could use recvmsg with MSG_PEEK.
 *
 * @return true If stdin has data.
 * @return false Otherwise.
 */
bool
stdin_has_data(void) {
    bool          has_data = false;
    struct pollfd pollfd   = {
          .fd      = STDIN_FILENO,
          .events  = POLLIN,
          .revents = 0,
    };

    if (poll(&pollfd, 1, 0) == -1) {
        return (has_data);
    } else if (pollfd.revents & POLLIN) {
        has_data = true;
    }

    return (has_data);
}