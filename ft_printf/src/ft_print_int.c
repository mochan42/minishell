/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 02:01:40 by fakouyat          #+#    #+#             */
/*   Updated: 2022/06/09 02:01:40 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/helpers.h"

static int	ft_size_int(int n)
{
	int	size;
	int	n_original;

	n_original = n;
	size = 1;
	if (n < 0)
		n = n * -1;
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	if (n_original < 0)
		size += 1;
	return (size);
}

static void	ft_putnbr_fd(int n, int fd)
{
	char	unit;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
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

void	ft_print_int(int nb, int *str_len)
{
	int	d;

	d = nb;
	ft_putnbr_fd(d, 1);
	if (d != -2147483648)
		*str_len += ft_size_int(d);
	else
		*str_len += 11;
}
