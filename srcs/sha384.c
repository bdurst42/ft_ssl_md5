/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 00:29:51 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/07 18:35:09 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint64_t g_k[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c,
	0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694, 0xe49b69c19ef14ad2,
	0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4,
	0x76f988da831153b5, 0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2,
	0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
	0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b, 0xa2bfe8a14cf10364,
	0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a,
	0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63,
	0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72,
	0x8cc702081a6439ec, 0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae,
	0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c, 0x4cc5d4becb3e42b6,
	0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

static uint64_t	make_padding_message(uint8_t **pad_msg, char *message, \
		__uint128_t msg_len)
{
	uint64_t	pad_msg_len;

	pad_msg_len = 128 * ((msg_len + 1) / 128 + 1);
	if ((msg_len + 1) % 128 > 112)
		pad_msg_len += 128;
	if (!(*pad_msg = ft_memalloc(pad_msg_len)))
		ft_exiterror("Malloc failed", 1);
	ft_memcpy(*pad_msg, message, msg_len);
	(*pad_msg)[msg_len] = 128;
	add_msg_len(pad_msg, pad_msg_len, msg_len);
	*pad_msg = revert_msg(*pad_msg, msg_len + 1);
	return (pad_msg_len);
}

static void		compute_data(t_data_64 *data, uint64_t i, uint64_t *w)
{
	data->s[1] = RROTATE64(data->e, 14) ^ RROTATE64(data->e, 18) \
	^ RROTATE64(data->e, 41);
	data->ch = (data->e & data->f) ^ ((~data->e) & data->g);
	data->tmp[0] = data->i + data->s[1] + data->ch + g_k[i] + w[i];
	data->s[0] = RROTATE64(data->a, 28) ^ RROTATE64(data->a, 34) \
	^ RROTATE64(data->a, 39);
	data->maj = (data->a & data->b) ^ (data->a & data->c) ^ (data->b & data->c);
	data->tmp[1] = data->s[0] + data->maj;
	fill_working_variables_64(data);
}

static void		modify_data(t_data_64 *data, uint8_t *pad_msg)
{
	uint64_t	w[80];
	uint64_t	i;
	uint64_t	*m;

	i = -1;
	m = (uint64_t*)pad_msg;
	while (++i < 16)
		w[i] = m[i];
	--i;
	while (++i < 80)
	{
		data->s[0] = RROTATE64(w[i - 15], 1) \
		^ RROTATE64(w[i - 15], 8) ^ w[i - 15] >> 7;
		data->s[1] = RROTATE64(w[i - 2], 19) \
		^ RROTATE64(w[i - 2], 61) ^ w[i - 2] >> 6;
		w[i] = w[i - 16] + data->s[0] + w[i - 7] + data->s[1];
	}
	set_working_variables_64(data);
	i = -1;
	while (++i < 80)
		compute_data(data, i, w);
	fill_output_data_64(data);
}

static void		get_encode_message(char **str, t_data_64 data)
{
	int		i;
	int		j;
	int		k;
	uint8_t	*p;
	char	*base;

	base = "0123456789abcdef";
	if (!(*str = (char*)malloc(97)))
		ft_exiterror("Malloc failure", 1);
	(*str)[96] = 0;
	i = 95;
	k = 6;
	while (i > -1)
	{
		j = 0;
		p = (uint8_t *)&(data.h[--k]);
		while (j < 8)
		{
			(*str)[i--] = base[p[j] % 16];
			(*str)[i--] = (p[j] < 16) ? '0' : base[(p[j] / 16) % 16];
			++j;
		}
	}
}

char			*sha384(char *message, __uint128_t msg_len)
{
	t_data_64	data;
	uint64_t	pad_msg_len;
	uint8_t		*pad_msg;
	uint64_t	offset;
	char		*encode_message;

	data.h[0] = 0xcbbb9d5dc1059ed8;
	data.h[1] = 0x629a292a367cd507;
	data.h[2] = 0x9159015a3070dd17;
	data.h[3] = 0x152fecd8f70e5939;
	data.h[4] = 0x67332667ffc00b31;
	data.h[5] = 0x8eb44a8768581511;
	data.h[6] = 0xdb0c2e0d64f98fa7;
	data.h[7] = 0x47b5481dbefa4fa4;
	pad_msg_len = make_padding_message(&pad_msg, message, msg_len);
	offset = 0;
	while (offset < pad_msg_len)
	{
		modify_data(&data, pad_msg + offset);
		offset += 128;
	}
	free(pad_msg);
	get_encode_message(&encode_message, data);
	return (encode_message);
}
