/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 19:24:12 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/08 18:06:41 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <fcntl.h>

static char	*open_file(char *file_name, __uint128_t *len)
{
	int		fd_file;
	char	*file_content;

	if ((fd_file = open(file_name, O_RDONLY)) == -1)
	{
		ft_putstr(file_name);
		ft_putendl(": No such file or directory");
		return (NULL);
	}
	file_content = read_file(fd_file, len);
	close(fd_file);
	return (file_content);
}

void		treat_data(t_env *env)
{
	t_list		*tmp;
	t_arg		*arg;
	char		*message;
	char		*encode_message;

	tmp = env->command_args;
	while (tmp)
	{
		arg = (t_arg*)tmp->data;
		if (arg->type == TEXT)
			env->len = ft_strlen(arg->content);
		message = (arg->type != FILE_NAME) ? arg->content \
										: open_file(arg->content, &env->len);
		if (message)
		{
			encode_message = (env->algos[env->command].func32) \
				? env->algos[env->command].func32(message, env->len) \
				: env->algos[env->command].func64(message, env->len);
			display_encode_message(env, arg, \
				encode_message);
			(arg->type != TEXT) ? free(message) : NULL;
			free(encode_message);
		}
		tmp = tmp->next;
	}
}
