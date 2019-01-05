/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stdin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 16:18:28 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/05 12:56:47 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char		*read_file(int fd_file)
{
	char	*line;
	char	*to_free;
	int		ret;
	char	*file_content;

	line = NULL;
	file_content = ft_strdup("");
	while ((ret = gnl(fd_file, &line)) > 0)
	{
		to_free = file_content;
		file_content = (ret == 2) ? ft_strstrjoin(to_free, line, "\n") : \
									ft_strjoin(to_free, line);
		if (to_free)
			ft_strdel(&to_free);
		ft_strdel(&line);
	}
	free(line);
	if (ret == -1)
		ft_exiterror("read failure", 1);
	return (file_content);
}

void		get_stdin(t_env *env)
{
	ft_node_push_front(&env->command_args, \
			create_arg(STDIN_TEXT, read_file(0)));
}
