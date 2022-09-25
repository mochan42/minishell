/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:20:27 by fakouyat          #+#    #+#             */
/*   Updated: 2022/06/10 14:20:27 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/helpers.h"

static int	ft_size_ptr(unsigned long int n)
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

static void	ft_putnbr_fd(unsigned long int n, int fd)
{
	char	unit;

	if (n < 16)
	{
		if (n < 10)
			unit = n + '0';
		else
			unit = n - 10 + 'a';
		write(fd, &unit, fd);
	}
	else
	{
		ft_putnbr_fd(n / 16, fd);
		ft_putnbr_fd(n % 16, fd);
	}
}

void	ft_print_ptr(unsigned long long nb, int *str_len)
{
	unsigned long long	d;

	d = nb;
	write (1, "0x", 2);
	if (nb == 0)
	{
		write (1, "0", 1);
		*str_len += 3;
		return ;
	}
	ft_putnbr_fd(d, 1);
	*str_len += ft_size_ptr(d) + 2;
}
