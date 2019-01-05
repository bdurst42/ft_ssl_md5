/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:44:40 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/03 18:55:49 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	fill_output_data_64(t_data_64 *data)
{
	data->h[0] += data->a;
	data->h[1] += data->b;
	data->h[2] += data->c;
	data->h[3] += data->d;
	data->h[4] += data->e;
	data->h[5] += data->f;
	data->h[6] += data->g;
	data->h[7] += data->i;
}

void	fill_working_variables_64(t_data_64 *data)
{
	data->i = data->g;
	data->g = data->f;
	data->f = data->e;
	data->e = data->d + data->tmp[0];
	data->d = data->c;
	data->c = data->b;
	data->b = data->a;
	data->a = data->tmp[0] + data->tmp[1];
}

void	set_working_variables_64(t_data_64 *data)
{
	data->a = data->h[0];
	data->b = data->h[1];
	data->c = data->h[2];
	data->d = data->h[3];
	data->e = data->h[4];
	data->f = data->h[5];
	data->g = data->h[6];
	data->i = data->h[7];
}

void	add_msg_len(uint8_t **pad_msg, uint64_t pad_msg_len, \
					__uint128_t msg_len)
{
	msg_len *= 8;
	(*pad_msg)[pad_msg_len - 1] = (msg_len & 0xFF) >> 56;
	(*pad_msg)[pad_msg_len - 2] = (msg_len & 0x00FF) >> 48;
	(*pad_msg)[pad_msg_len - 3] = (msg_len & 0x0000FF) >> 40;
	(*pad_msg)[pad_msg_len - 4] = (msg_len & 0x000000FF) >> 32;
	(*pad_msg)[pad_msg_len - 5] = (msg_len & 0x00000000FF) >> 24;
	(*pad_msg)[pad_msg_len - 6] = (msg_len & 0x0000000000FF) >> 16;
	(*pad_msg)[pad_msg_len - 7] = (msg_len & 0x000000000000FF) >> 8;
	(*pad_msg)[pad_msg_len - 8] = (msg_len & 0x00000000000000FF);
	(*pad_msg)[pad_msg_len - 9] = (msg_len >> 64 & 0xFF) >> 56;
	(*pad_msg)[pad_msg_len - 10] = (msg_len >> 64 & 0x00FF) >> 48;
	(*pad_msg)[pad_msg_len - 11] = (msg_len >> 64 & 0x0000FF) >> 40;
	(*pad_msg)[pad_msg_len - 12] = (msg_len >> 64 & 0x000000FF) >> 32;
	(*pad_msg)[pad_msg_len - 13] = (msg_len >> 64 & 0x00000000FF) >> 24;
	(*pad_msg)[pad_msg_len - 14] = (msg_len >> 64 & 0x0000000000FF) >> 16;
	(*pad_msg)[pad_msg_len - 15] = (msg_len >> 64 & 0x000000000000FF) >> 8;
	(*pad_msg)[pad_msg_len - 16] = (msg_len >> 64 & 0x00000000000000FF);
}
