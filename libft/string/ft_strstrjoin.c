/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 18:34:34 by vdarmaya          #+#    #+#             */
/*   Updated: 2019/01/07 11:00:21 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strstrjoin(char *s1, char *s2, char *s3)
{
	char	*str;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	if (!(str = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	while (*s1)
	{
		str[++i] = *s1;
		s1++;
	}
	while (*s2)
	{
		str[++i] = *s2;
		s2++;
	}
	while (*s3)
	{
		str[++i] = *s3;
		s3++;
	}
	str[++i] = '\0';
	return (str);
}
