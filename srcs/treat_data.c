/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 19:24:12 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/05 12:58:33 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <fcntl.h>

static char	*open_file(char	*file_name)
{
	int		fd_file;
	char	*file_content;
	
	if ((fd_file = open(file_name, O_RDONLY)) == -1)
	{
		ft_putstr(file_name);
		ft_putendl(": No such file or directory");
		return (NULL);
	}
	file_content = read_file(fd_file);
	close(fd_file);
	return (file_content);
}

void		treat_data(t_env *env)
{
	t_list	*tmp;
	t_arg	*arg;
	char	*message;
	
	tmp = env->command_args;
	while (tmp)
	{
		arg = (t_arg*)tmp->data;
		message = (arg->type != FILE_NAME)	? arg->content \
											: open_file(arg->content);
		if (message)
		{
			display_encode_message(env, arg, \
				env->algos[env->command].func(message));
			free(message);
		}
		tmp = tmp->next;
	}
}
