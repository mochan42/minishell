/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:35:36 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/25 15:27:35 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_nb_digits(int n)
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

char	*ft_itoa(int n)
{
	char	*n_in_string;
	int		nb_of_digits;
	int		i;

	i = 0;
	if (n == -2147483648)
		return (ft_substr("-2147483648", 0, 12));
	nb_of_digits = ft_nb_digits(n);
	n_in_string = (char *)malloc(sizeof(char) * (nb_of_digits + 1));
	if (n_in_string == NULL)
		return (0);
	n_in_string[nb_of_digits] = 0;
	if (n < 0)
	{
		n_in_string[0] = '-';
		i = 1;
		n *= -1;
	}
	while (i < nb_of_digits)
	{
		n_in_string[nb_of_digits - 1] = n % 10 + '0';
		n = n / 10;
		nb_of_digits--;
	}
	return (n_in_string);
}
