/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:03:23 by fakouyat          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/22 23:12:03 by fakouyat         ###   ########.fr       */
=======
/*   Updated: 2022/09/21 00:25:55 by fakouyat         ###   ########.fr       */
>>>>>>> facinet
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenght_str(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write (fd, s, ft_lenght_str(s));
}
