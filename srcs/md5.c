/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:21:38 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/03 18:45:53 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

static uint32_t g_r[64] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 
	17, 22, 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, 4,
	11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, 6, 10, 15, 21,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};
	
static uint32_t g_k[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
		0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
		0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
		0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
		0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
		0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static uint32_t	make_padding_message(uint8_t **padding_message, char *message)
{
	uint32_t	padding_message_len;
	uint64_t	message_len;
	
	message_len = ft_strlen(message);
	padding_message_len = 64 * ((message_len + 1) / 64 + 1);
	if ((message_len + 1) % 64 > 56 )
		padding_message_len += 64;
	if (!(*padding_message = ft_memalloc(padding_message_len)))
		ft_exiterror("Malloc failed", 1);
	ft_memcpy(*padding_message, message, message_len);
	(*padding_message)[message_len] = 128;
	message_len *= 8;
	ft_memcpy(*padding_message + padding_message_len - 8, &message_len, 8);
	return (padding_message_len);
}

static void		compute_data(t_data *data, uint32_t i)
{
	if (i < 16)
	{
		data->f = (data->b & data->c) | ((~data->b) & data->d);
		data->g = i;
	}
	else if (i < 32)
	{
		data->f = (data->d & data->b) | ((~data->d) & data->c);
		data->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		data->f = data->b ^ data->c ^ data->d;
		data->g = (3 * i + 5) % 16;          
	}
	else
	{
		data->f = data->c ^ (data->b | (~data->d));
		data->g = (7 * i) % 16;
	}
}

static void 	modify_data(t_data *data, uint8_t *padding_message)
{
	uint32_t	*w;
	uint32_t	i;
	
	w = (uint32_t*)padding_message;
	data->a = data->h[0];
	data->b = data->h[1];
	data->c = data->h[2];
	data->d = data->h[3];
	for(i = 0; i < 64; i++)
	{
		compute_data(data, i);
		data->tmp[0] = data->d;
		data->d = data->c;
		data->c = data->b;
		data->b = data->b + \
				LEFTROTATE((data->a + data->f + g_k[i] + w[data->g]), g_r[i]);
		data->a = data->tmp[0];
	}		
	data->h[0] += data->a;
	data->h[1] += data->b;
	data->h[2] += data->c;
	data->h[3] += data->d;
}

static void		get_encode_message(char **str, t_data data)
{
	int		i;
	int		j;
	int		k;
	uint8_t	*p;
	char	*base = "0123456789abcdef";
	
	if (!(*str = (char*)malloc(33)))
		ft_exiterror("Malloc failure", 1);
	(*str)[32] = 0;
	i = 31;
	k = 4;
	while (i > -1)
	{
		j = 4;
		p = (uint8_t *)&(data.h[--k]);
		while (--j > -1)
		{
			(*str)[i--] = base[p[j] % 16];
			(*str)[i--] = (p[j] < 16) ? '0' : base[(p[j] / 16) % 16];
		}
	}
}

char			*md5(char *message)
{
	t_data		data;
	uint32_t	padding_message_len;
	uint8_t		*padding_message;	
	uint32_t	offset;
	char 		*encode_message;
	
	data.h[0] = 0x67452301;
	data.h[1] = 0xEFCDAB89;
	data.h[2] = 0x98BADCFE;
	data.h[3] = 0x10325476;
	padding_message_len = make_padding_message(&padding_message, message);
	offset = 0;
	while (offset < padding_message_len)
	{
		modify_data(&data, padding_message + offset);
		offset += 64;
	}
	free(padding_message);
	get_encode_message(&encode_message, data);
	return(encode_message);
}