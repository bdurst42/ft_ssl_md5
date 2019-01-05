/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:47:37 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/03 18:57:30 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	uswap_32(unsigned int x)
{
	return (((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8) | \
			(((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24)));
}

uint8_t		*revert_msg(uint8_t *pad_msg, uint64_t len)
{
	uint64_t	i;
	uint8_t		stock;

	if (!pad_msg || !len)
		return (NULL);
	if (len % 8 != 0)
		len = (len / 8 + 1) * 8;
	i = 0;
	while (i < --len)
	{
		stock = pad_msg[i];
		pad_msg[i++] = pad_msg[len];
		pad_msg[len] = stock; 
	}
	return (pad_msg);
}
