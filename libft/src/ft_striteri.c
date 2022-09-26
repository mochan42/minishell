/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 22:50:52 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/25 15:36:14 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;
	int	length;

	if (!s)
		return ;
	i = 0;
	length = ft_strlen(s);
	while (i < length)
	{
		(*f)(i, &s[i]);
		i++;
	}
}
