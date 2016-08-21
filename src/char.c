/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 18:19:25 by udelorme          #+#    #+#             */
/*   Updated: 2016/08/21 19:28:49 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

size_t		print_char_string(char	*string, t_vars *vars)
{
	char	*str;
	size_t	str_len;

	str_len = 0;
	str = NULL;
	if (!string)
		str = ft_strdup("(null)");
	else
	{
		str = ft_strdup(string);
		if (vars->precision >= 0)
			str[vars->precision] = 0;
	}
	str_len = print_str_padded(str, vars, NULL);
	free(str);
	return (str_len);
}

size_t		print_percent(char	*string, t_vars *vars)
{
	return (print_str_padded(string, vars, NULL));
}

int		print_char_padded(char c, t_vars *vars)
{
	size_t	len;
	int		padding;

	len = 0;
	padding = vars->padding - 1;
	if (padding > 0 && !HAS_FLAG_RIGHT(vars->flags))
		len += print_padding(padding);
	len += write(1, &c, 1);
	if (padding > 0 && HAS_FLAG_RIGHT(vars->flags))
		len += print_padding(padding);
	vars->precision = -1;
	return (len);
}

size_t		print_char(char c, t_vars *vars)
{
	//char	to_str[2];
	int		ret;

	//to_str[0] = c;
	//to_str[1] = 0;
	//ret = print_str_padded(to_str, vars, NULL);
	ret = print_char_padded(c, vars);
	//if (c == 0)
	//	ret += 1;
	return (ret);
}

static void	print_sub_str(const char *str, int begin, size_t len)
{
	write(1, &str[begin], len);
}

size_t		cross_buffer(const char *buf)
{
	size_t	len;
	char	*begin;

	len = 0;
	begin = (char *)buf;
	while (*buf && *buf != '%')
	{
		len++;
		buf++;
	}
	print_sub_str(begin, 0, len);
	return (len);
}

char		*add_padding(char *str, size_t len_padding, t_vars *vars)
{
	char	*tmp;
	size_t	str_len;

	str_len = ft_strlen(str);
	if (HAS_FLAG_ZERO(vars->flags))
		tmp = (char *)ft_memallocset(sizeof(char) * str_len + len_padding + 1, '0');
	else
		tmp = (char *)ft_memallocset(sizeof(char) * str_len + len_padding + 1, ' ');
	tmp[str_len + len_padding] = 0;
	if (HAS_FLAG_RIGHT(vars->flags))
	{
		len_padding = 0;
	}
	else
	{
		tmp += len_padding;
	}
	while (*str)
	{
		*tmp = *str;
		str++;
		tmp++;
	}
	tmp -= (str_len + len_padding);
	return (tmp);
}

int		print_str_padded(char *str, t_vars *vars, char *prefix)
{
	size_t	len_str;
	int		padding;
	char	*string;

	string = ft_strdup(str);

	len_str = ft_strlen(string);
	padding = vars->padding - len_str;
	if (prefix)
		padding -= ft_strlen(prefix);
	if (padding > 0 && HAS_FLAG_ZERO(vars->flags))
		string = add_padding(string, (size_t)padding, vars);
	if (prefix)
		ft_str_renew(&string, ft_strjoin(prefix, string)); // not opti
	if (padding > 0 && !HAS_FLAG_ZERO(vars->flags))
		string = add_padding(string, (size_t)padding, vars);
	len_str = ft_strlen(string);
	ft_putstr(string);
	vars->precision = -1;
	return (len_str);
}
