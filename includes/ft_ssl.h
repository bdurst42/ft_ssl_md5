/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 20:02:05 by bdurst2812        #+#    #+#             */
/*   Updated: 2019/01/08 18:30:19 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/libft.h"

# define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
# define RROTATE(x, c) (((x) >> (c % 32)) | ((x) << ((32 - c) % 32)))

# define LEFTROTATE64(x, c) (((x) << (c)) | ((x) >> (64 - (c))))
# define RROTATE64(x, c) (((x) >> (c % 64)) | ((x) << ((64 - c) % 64)))

# define NUMBER_OF_ALGOS 7

enum				e_arg_type
{
	FILE_NAME,
	TEXT,
	STDIN_TEXT,
};

typedef struct		s_algo
{
	char			*(*func32)(char*, uint64_t);
	char			*(*func64)(char*, __uint128_t);
	char			*name;
}					t_algo;

typedef struct		s_options
{
	char			p;
	char			q;
	char			r;
	char			s;
}					t_options;

typedef struct		s_arg
{
	enum e_arg_type	type;
	char			*content;
	t_options		options;
}					t_arg;

typedef struct		s_env
{
	int				command;
	t_options		options;
	t_list			*command_args;
	t_algo			algos[NUMBER_OF_ALGOS];
	__uint128_t		len;
}					t_env;

typedef struct		s_data
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		i;
	uint32_t		ch;
	uint32_t		maj;
	uint32_t		h[8];
	uint32_t		s[2];
	uint32_t		tmp[2];
}					t_data;

typedef struct		s_data_64
{
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
	uint64_t		i;
	uint64_t		ch;
	uint64_t		maj;
	uint64_t		h[8];
	uint64_t		s[2];
	uint64_t		tmp[2];
}					t_data_64;

char				get_command(t_env *env, char *command);
int					get_options_and_args(t_env *env, char **params);
t_arg				*create_arg(enum e_arg_type type, char *content, \
					t_options options);

void				treat_data(t_env *env);

void				get_stdin(t_env *env, __uint128_t *len);
char				*read_file(int fd_file, __uint128_t *len);

void				display_encode_message(t_env *env, t_arg *arg, \
					char *encode_message);

void				fill_output_data(t_data *data);
void				fill_working_variables(t_data *data);
void				set_working_variables(t_data *data);
void				add_msg_len(uint8_t **pad_msg, __uint128_t pad_msg_len, \
					__uint128_t msg_len);

void				fill_output_data_64(t_data_64 *data);
void				fill_working_variables_64(t_data_64 *data);
void				set_working_variables_64(t_data_64 *data);

uint32_t			uswap_32(unsigned int x);
uint8_t				*revert_msg(uint8_t *pad_msg, uint64_t len);
void				last_func(t_env *env, char *param, char	*end_opt);

char				*md5(char *message, uint64_t msg_len);

char				*sha256(char *message, uint64_t msg_len);

char				*sha224(char *message, uint64_t msg_len);

char				*sha512(char *message, __uint128_t msg_len);

char				*sha384(char *message, __uint128_t msg_len);

char				*sha512_256(char *message, __uint128_t msg_len);

char				*sha512_224(char *message, __uint128_t msg_len);

#endif
