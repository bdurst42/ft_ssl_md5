/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 22:26:39 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/08 18:06:27 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	ft_upper(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		ft_putchar(ft_toupper(str[i]));
}

static void	regular_display(t_arg *arg, char *algo)
{
	ft_upper(algo);
	ft_putchar(' ');
	(arg->type == TEXT) ? ft_putstr("(\"") : ft_putchar('(');
	ft_putstr(arg->content);
	(arg->type == TEXT) ? ft_putstr("\") = ") : ft_putstr(") = ");
}

static void	reverse_display(t_arg *arg)
{
	(arg->type == TEXT) ? ft_putstr(" \"") : ft_putchar(' ');
	ft_putstr(arg->content);
	(arg->type == TEXT) ? ft_putchar('"') : NULL;
}

void		display_encode_message(t_env *env, t_arg *arg, char *encode_message)
{
	if (arg->type == STDIN_TEXT && env->options.p)
		ft_putstr(arg->content);
	else if (arg->type == TEXT && !arg->content)
		ft_exiterror("Option requires an argument -- s", 1);
	if (arg->type != STDIN_TEXT && !arg->options.q && !arg->options.r)
		regular_display(arg, env->algos[env->command].name);
	ft_putstr(encode_message);
	if (arg->type != STDIN_TEXT && !arg->options.q && arg->options.r)
		reverse_display(arg);
	ft_putchar('\n');
}
