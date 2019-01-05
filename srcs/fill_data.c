/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 20:49:08 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/03 18:45:06 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	fill_output_data(t_data *data)
{
	data->h[0] += data->a;
	data->h[1] += data->b;
	data->h[2] += data->c;
	data->h[3] += data->d;
	data->h[4] += data->e;
	data->h[5] += data->f;
	data->h[6] += data->g;
	data->h[7] += data->i;
}

void	fill_working_variables(t_data *data)
{
	data->i = data->g;
	data->g = data->f;
	data->f = data->e;
	data->e = data->d + data->tmp[0];
	data->d = data->c;
	data->c = data->b;
	data->b = data->a;
	data->a = data->tmp[0] + data->tmp[1];
}

void	set_working_variables(t_data *data)
{
	data->a = data->h[0];
	data->b = data->h[1];
	data->c = data->h[2];
	data->d = data->h[3];
	data->e = data->h[4];
	data->f = data->h[5];
	data->g = data->h[6];
	data->i = data->h[7];
}
