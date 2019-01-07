/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data_64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:44:40 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/07 14:51:41 by bdurst2812       ###   ########.fr       */
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

void	add_msg_len(uint8_t **pad_msg, __uint128_t pad_msg_len, \
					__uint128_t len)
{
	len *= 8;
	(*pad_msg)[pad_msg_len - 1] = (len & 0xFF00000000000000) >> 56;
	(*pad_msg)[pad_msg_len - 2] = (len & 0xFF000000000000) >> 48;
	(*pad_msg)[pad_msg_len - 3] = (len & 0xFF0000000000) >> 40;
	(*pad_msg)[pad_msg_len - 4] = (len & 0xFF00000000) >> 32;
	(*pad_msg)[pad_msg_len - 5] = (len & 0xFF000000) >> 24;
	(*pad_msg)[pad_msg_len - 6] = (len & 0xFF0000) >> 16;
	(*pad_msg)[pad_msg_len - 7] = (len & 0xFF00) >> 8;
	(*pad_msg)[pad_msg_len - 8] = (len & 0xFF);
	(*pad_msg)[pad_msg_len - 9] = (len >> 64 & 0xFF00000000000000) >> 56;
	(*pad_msg)[pad_msg_len - 10] = (len >> 64 & 0xFF000000000000) >> 48;
	(*pad_msg)[pad_msg_len - 11] = (len >> 64 & 0xFF0000000000) >> 40;
	(*pad_msg)[pad_msg_len - 12] = (len >> 64 & 0xFF00000000) >> 32;
	(*pad_msg)[pad_msg_len - 13] = (len >> 64 & 0xFF000000) >> 24;
	(*pad_msg)[pad_msg_len - 14] = (len >> 64 & 0xFF0000) >> 16;
	(*pad_msg)[pad_msg_len - 15] = (len >> 64 & 0xFF00) >> 8;
	(*pad_msg)[pad_msg_len - 16] = (len >> 64 & 0xFF);
}
