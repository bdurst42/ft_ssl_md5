/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stdin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 16:18:28 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/07 18:36:39 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*ft_concat_len(char const *s1, char const *s2, char *dst, \
							__uint128_t *s_len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < s_len[0])
	{
		dst[i] = s1[i];
		i++;
	}
	while (i < s_len[0] + s_len[1])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char		*ft_strjoin_len(char const *s1, char const *s2, __uint128_t s1_len,
						__uint128_t s2_len)
{
	char		*dst;
	__uint128_t	s_len[2];

	if (s1 || s2)
	{
		if (!(dst = malloc(s1_len + s2_len + 1)))
			ft_exiterror("Malloc failure", 1);
		if (!s2)
			return (ft_memcpy(dst, s1, s1_len));
		else if (!s1)
			return (ft_memcpy(dst, s2, s2_len));
		s_len[0] = s1_len;
		s_len[1] = s2_len;
		if (dst)
			return (ft_concat_len(s1, s2, dst, s_len));
	}
	return (NULL);
}

char		*read_file(int fd_file, __uint128_t *len)
{
	char	*to_free;
	int		ret;
	char	*file_content;
	char	buff[100001];

	file_content = NULL;
	*len = 0;
	while ((ret = read(fd_file, buff, 100000)) > 0)
	{
		buff[ret] = 0;
		to_free = file_content;
		file_content = ft_strjoin_len(to_free, buff, *len, ret);
		*len += ret;
		if (to_free)
			ft_strdel(&to_free);
	}
	if (ret == -1)
		ft_exiterror("read failure", 1);
	return (file_content);
}

void		get_stdin(t_env *env, __uint128_t *len)
{
	ft_node_push_front(&env->command_args, \
			create_arg(STDIN_TEXT, read_file(0, len)));
}
