/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst2812 <bdurst2812@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/13 19:47:25 by bdurst            #+#    #+#             */
/*   Updated: 2018/12/21 12:36:07 by bdurst2812       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

size_t				ft_strlen(const char *str);
size_t				ft_nbrlen(long nb);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
long				ft_atoi(const char *str);
char				*ft_itoa(long n);
char				*ft_btoa(long n, char *base);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strdelpp(char ***str);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_sorttab(char ***tabu);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strstrjoin(char *s1, char *s2, char *s3);
char				*ft_strjoinchar(char *s1, char s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_strsplitmulticharacters(char const *s, char *cs);
char				**ft_strseparate(char const *s, char c);
void				ft_perror(const char *str, int status);
void				ft_exiterror(const char *str, int status);
int					ft_strfind_by_end(const char *s, int c);
int					ft_strfind(const char *s, int start, int c);
char				ft_strcont(char *s1, char *s2);
size_t				ft_counttab(char **tabu);
char				**ft_strrealsplit(char const *s, char c);

#endif
