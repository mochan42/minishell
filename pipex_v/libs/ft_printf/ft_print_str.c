/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 03:49:45 by fakouyat          #+#    #+#             */
/*   Updated: 2022/06/09 03:49:45 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

void	ft_print_str(char *str, int *str_len)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		*str_len += 6;
		return ;
	}
	while (str[i])
		i++;
	write(1, str, i);
	*str_len += i;
}
