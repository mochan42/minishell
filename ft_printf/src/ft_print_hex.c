/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:21:19 by fakouyat          #+#    #+#             */
/*   Updated: 2022/06/10 14:21:19 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/helpers.h"

static int	ft_size_hex(unsigned int n)
{
	int	size;

	size = 1;
	while (n >= 16)
	{
		n /= 16;
		size++;
	}
	return (size);
}

static void	ft_putnbr_fd(unsigned int n, char c, int fd)
{
	char	unit;

	if (n < 16)
	{
		if (n < 10)
			unit = n + '0';
		else
		{
			if (c == 'x')
				unit = n - 10 + 'a';
			else if (c == 'X')
				unit = n - 10 + 'A';
		}
		write(fd, &unit, 1);
	}
	else
	{
		ft_putnbr_fd(n / 16, c, fd);
		ft_putnbr_fd(n % 16, c, fd);
	}
}

void	ft_print_hex(unsigned int nb, int *str_len, char c)
{
	unsigned int	d;

	d = nb;
	if (d == 0)
	{
		write (1, "0", 1);
		*str_len += 1;
		return ;
	}
	ft_putnbr_fd(d, c, 1);
	*str_len += ft_size_hex(d);
}
