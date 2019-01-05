/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 13:21:27 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/05 12:56:41 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_arg			*create_arg(enum e_arg_type type, char *content)
{
	t_arg	*new_arg;

	if (!(new_arg = (t_arg*)malloc(sizeof(t_arg))))
		ft_exiterror("Malloc failed", 1);
	new_arg->type = type;
	new_arg->content = content;
	return (new_arg);
}

static char		manage_s_op(t_env *env, char *string_arg)
{
	env->options.s = 1;
	ft_node_push_back(&env->command_args, create_arg(TEXT, string_arg));
	return (1);
}

static char		get_options(t_env *env, char c, char *string_arg, \
							char *jump_next)
{
	if (c == 'p')
	{
		if (env->options.p)
			ft_node_push_back(&env->command_args, \
				create_arg(STDIN_TEXT, ft_strdup("")));
		else
			ft_node_push_back(&env->command_args, \
				create_arg(STDIN_TEXT, read_file(0)));
		env->options.p = 1;
	}
	else if (c == 'q')
		env->options.q = 1;
	else if (c == 'r')
		env->options.r = 1;
	else if (c == 's' && !*jump_next)
		*jump_next = manage_s_op(env, string_arg);
	else
	{
		ft_putstr("ft_ssl: Error: '");
		ft_putchar(c);
		ft_putendl("' is an invalid option.");
		return (-1);
	}
	return (0);
}

int				get_options_and_args(t_env *env, char **p)
{
	int		i;
	int		j;
	char	jump_next;
	char	end_opt;

	i = 1;
	end_opt = 0;
	while (p[i] && p[++i])
	{
		if (!end_opt && p[i][0] == '-' && p[i][1])
		{
			jump_next = 0;
			j = 0;
			while (p[i] && p[i][++j])
				if ((get_options(env, p[i][j], p[i + 1], &jump_next)) == -1)
					return (-1);
			i += jump_next;
		}
		else
		{
			end_opt = 1;
			ft_node_push_back(&env->command_args, create_arg(FILE_NAME, p[i]));
		}
	}
	return (i);
}

char			get_command(t_env *env, char *command)
{
	int		i;

	i = -1;
	while (++i < NUMBER_OF_ALGOS)
		if (!ft_strcmp(command, env->algos[i].name))
		{
			env->command = i;
			break;
		}
	if (i == NUMBER_OF_ALGOS)
	{
		ft_putstr("ft_ssl: Error: '");
		ft_putstr(command);
		ft_putendl("' is an invalid command.");
		return (1);
	}
	return (0);
}
