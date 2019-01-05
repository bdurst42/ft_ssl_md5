/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 12:19:40 by bdurst2812        #+#    #+#             */
/*   Updated: 2018/12/21 12:52:48 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

static	long	ft_numberlen(long n, char base_nb)
{
	long		i;

	i = 1;
	while (n /= base_nb)
		i++;
	return (i);
}

char			*ft_btoa(long n, char *base)
{
	char	*dst;
	char	base_nb;
	long	i;

	if (n < 0)
		return (NULL);
	base_nb = ft_strlen(base);
	i = ft_numberlen(n, base_nb);
	dst = malloc(sizeof(char) * (i + 1));
	dst[i] = '\0';
	while (--i >= 0)
	{
		dst[i] = base[n % base_nb];
		n /= base_nb;
	}
	return (dst);
}
