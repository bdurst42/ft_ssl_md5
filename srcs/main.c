/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 21:46:03 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/05 12:57:06 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	check_params(t_env *env, char **params, int nb_params)
{
	if (get_command(env, params[1]))
		return (1);
	if (nb_params > 2 && (get_options_and_args(env, params)) == -1)
		return (1);
	if (!env->command_args)
		ft_node_push_back(&env->command_args, \
			create_arg(STDIN_TEXT, read_file(0)));
	return (0);
}

static void	clear_arg(t_arg *arg)
{
	free(arg);
}

static void	set_algo(t_algo *algo, char *name, char *(*func)(char*))
{
	algo->name = name;
	algo->func = func;
}

int			main(int ac, char **av)
{
	t_env	env;

	ft_bzero(&env, sizeof(env));
	set_algo(&env.algos[0], "md5", md5);
	set_algo(&env.algos[1], "sha256", sha256);
	set_algo(&env.algos[2], "sha224", sha224);
	set_algo(&env.algos[3], "sha512", sha512);
	set_algo(&env.algos[4], "sha384", sha384);
	set_algo(&env.algos[5], "sha512/256", sha512_256);
	set_algo(&env.algos[6], "sha512/224", sha512_224);
	if (ac > 1 && !check_params(&env, av, ac))
	{
		treat_data(&env);
		ft_clear_list(&env.command_args, (void*)&clear_arg);
		return (0);
	}
	ft_clear_list(&env.command_args, (void*)&clear_arg);
	if (ac == 1)
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
	else if (ac < 2)
		ft_putendl("ft_ssl: Error: too few arguments");
	return (1);
}
