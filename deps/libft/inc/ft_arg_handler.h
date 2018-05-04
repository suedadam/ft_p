/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:06:53 by satkins           #+#    #+#             */
/*   Updated: 2018/04/11 17:56:37 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARG_HANDLER_H

# define FT_ARG_HANDLER_H

# include "libft.h"

# include <stdarg.h>

# include <stddef.h>

# include <stdio.h>

# include <unistd.h>

# include <stdlib.h>

# include <wchar.h>

typedef struct		s_flag
{
	int				prefix;
	int				pad_zero;
	int				left_allign;
	int				sign;
	int				blank;
	int				width_set;
	int				precision_set;
	int				width;
	int				precision;
	int				caps;
	enum {
		none,
		hh,
		h,
		l,
		ll,
		j,
		z
	}				e_length;
}					t_flag;

void				ft_putnstr(char *str, int len);

size_t				str_format(char *str, t_flag arg_flag);

size_t				wstr_print(va_list *ap, t_flag arg_flag);

size_t				uchar_print(long long num, t_flag arg_flags);

int					flag_check(t_flag *arg_flags, char **arg);

size_t				signed_print(va_list *ap, t_flag arg_flag, char type);

size_t				unsigned_print(va_list *ap, t_flag arg_flag, char type);

size_t				str_print(va_list *ap, t_flag arg_flag);

size_t				hex_print(unsigned long long int num,
	t_flag arg_flag, char caps);

size_t				ptr_print(va_list *ap, t_flag arg_flag);

size_t				hex_print(unsigned long long int num,
	t_flag arg_flag, char caps);

size_t				uint_print(unsigned long long int num, t_flag arg_flag);

size_t				int_print(long long int num, t_flag arg_flag);

size_t				oct_print(unsigned long long int num, t_flag arg_flag);

size_t				char_print(long long num, t_flag arg_flags);

size_t				formatter(va_list *ap, char *format);

#endif
