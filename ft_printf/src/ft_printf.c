/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:00:05 by fakouyat          #+#    #+#             */
/*   Updated: 2022/06/08 20:00:05 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_format_arg(va_list args, char c, int *str_len)
{
	if (c == 'd' || c == 'i')
		ft_print_int(va_arg(args, int), str_len);
	else if (c == 'c')
		ft_print_char(va_arg(args, int), str_len);
	else if (c == 's')
		ft_print_str(va_arg(args, char *), str_len);
	else if (c == 'u')
		ft_print_unsigned(va_arg(args, unsigned int), str_len);
	else if (c == '%')
		ft_print_char(c, str_len);
	else if (c == 'p')
		ft_print_ptr(va_arg(args, unsigned long long), str_len);
	else if (c == 'x' || c == 'X')
		ft_print_hex(va_arg(args, unsigned int), str_len, c);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		str_len;

	str_len = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_format_arg(args, str[(i + 1)], &str_len);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			str_len++;
		}
		i++;
	}
	va_end(args);
	return (str_len);
}
