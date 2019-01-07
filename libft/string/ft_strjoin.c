/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 12:32:58 by bdurst            #+#    #+#             */
/*   Updated: 2019/01/07 10:41:17 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

static char	*ft_concat(char const *s1, char const *s2, char *dst)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	j = 0;
	while (i < s1_len)
	{
		dst[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;

	if (s1 || s2)
	{
		if (!s2)
			return (dst = ft_strdup(s1));
		else if (!s1)
			return (dst = ft_strdup(s2));
		else
			dst = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (dst)
			return (ft_concat(s1, s2, dst));
	}
	return (NULL);
}
