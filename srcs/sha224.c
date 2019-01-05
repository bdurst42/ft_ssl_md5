/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 12:11:55 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/05 13:09:42 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t g_k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 
		0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
		0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
		0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
		0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
		0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static uint32_t	make_padding_message(uint8_t **padding_message, char *message)
{
	uint32_t	padding_message_len;
	uint64_t	message_len;

	message_len = ft_strlen(message);
	padding_message_len = 64 * ((message_len + 1) / 64 + 1);
	if ((message_len + 1) % 64 > 56)
		padding_message_len += 64; 
	if (!(*padding_message = ft_memalloc(padding_message_len)))
		ft_exiterror("Malloc failed", 1);
	ft_memcpy(*padding_message, message, message_len);
	(*padding_message)[message_len] = 128;
	message_len *= 8;
	(*padding_message)[padding_message_len - 8] = message_len >> 56;
	(*padding_message)[padding_message_len - 7] = message_len >> 48;
	(*padding_message)[padding_message_len - 6] = message_len >> 40;
	(*padding_message)[padding_message_len - 5] = message_len >> 32;
	(*padding_message)[padding_message_len - 4] = message_len >> 24;
	(*padding_message)[padding_message_len - 3] = message_len >> 16;
	(*padding_message)[padding_message_len - 2] = message_len >> 8;
	(*padding_message)[padding_message_len - 1] = message_len;
	return (padding_message_len);
}

static void		compute_data(t_data *data, uint32_t i, uint32_t	*w)
{
	data->s[1] = RROTATE(data->e, 6) ^ RROTATE(data->e, 11) \
	^ RROTATE(data->e, 25);
	data->ch = (data->e & data->f) ^ ((~data->e) & data->g);
	data->tmp[0] = data->i + data->s[1] + data->ch + g_k[i] + w[i];
	data->s[0] = RROTATE(data->a, 2) ^ RROTATE(data->a, 13) \
	^ RROTATE(data->a, 22);
	data->maj = (data->a & data->b) ^ (data->a & data->c) ^ (data->b & data->c);
	data->tmp[1] = data->s[0] + data->maj;
	fill_working_variables(data);
}

static void		modify_data(t_data *data, uint8_t *padding_message)
{
	uint32_t	w[64];
	uint32_t	i;

	i = -1;
	while (++i < 16)
		w[i] = (padding_message[i * 4] << 24) + (padding_message[i * 4 + 1] \
		<< 16) + (padding_message[i * 4 + 2] << 8) + padding_message[i * 4 + 3];
	i = 15;
	while (++i < 64)
	{
		data->s[0] = RROTATE(w[i - 15], 7) \
		^ RROTATE(w[i - 15], 18) ^ w[i - 15] >> 3;
		data->s[1] = RROTATE(w[i - 2], 17) \
		^ RROTATE(w[i - 2], 19) ^ w[i - 2] >> 10;
		w[i] = w[i - 16] + data->s[0] + w[i - 7] + data->s[1];
	}
	set_working_variables(data);
	i = -1;
	while (++i < 64)
		compute_data(data, i, w);
	fill_output_data(data);
}

static void		get_encode_message(char **str, t_data data)
{
	int		i;
	int		j;
	int		k;
	uint8_t	*p;
	char	*base;

	base = "0123456789abcdef";
	if (!(*str = (char*)malloc(57)))
		ft_exiterror("Malloc failure", 1);
	(*str)[56] = 0;
	i = 55;
	k = 7;
	while (i > -1)
	{
		j = 0;
		p = (uint8_t *)&(data.h[--k]);
		while (j < 4)
		{
			(*str)[i--] = base[p[j] % 16];
			(*str)[i--] = (p[j] < 16) ? '0' : base[(p[j] / 16) % 16];
			++j;
		}
	}
}

char			*sha224(char *message)
{
	t_data		data;
	uint32_t	padding_message_len;
	uint8_t		*padding_message;
	uint32_t	offset;
	char 		*encode_message;

	data.h[0] = 0xc1059ed8;
	data.h[1] = 0x367cd507;
	data.h[2] = 0x3070dd17;
	data.h[3] = 0xf70e5939;
	data.h[4] = 0xffc00b31;
	data.h[5] = 0x68581511;
	data.h[6] = 0x64f98fa7;
	data.h[7] = 0xbefa4fa4;
	padding_message_len = make_padding_message(&padding_message, message);
	offset = 0;
	while (offset < padding_message_len)
	{
		modify_data(&data, padding_message + offset);
		offset += 64;
	}
	free(padding_message);
	get_encode_message(&encode_message, data);
	return (encode_message);
}
