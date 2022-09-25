/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:13:04 by fakouyat          #+#    #+#             */
/*   Updated: 2022/06/09 14:13:04 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/helpers.h"

static int	ft_size_unsigned(unsigned int n)
{
	int	size;

	size = 1;
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static void	ft_putnbr_fd(unsigned int n, int fd)
{
	char	unit;

	if (n < 10)
	{
		unit = n + '0';
		write(fd, &unit, 1);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

void	ft_print_unsigned(unsigned int nb, int *str_len)
{
	unsigned int	d;

	d = nb;
	ft_putnbr_fd(d, 1);
	*str_len += ft_size_unsigned(d);
}
