/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:27:57 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/13 14:42:01 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**---------------------------------------------------------------------------*/
/* This functions replace the first len content of b by int c and 
	return a pointer to b
*/
void	*ft_memset(void *b, int c, size_t len)
{
	int		i;
	char	*b_int;

	i = 0;
	b_int = (char *)b;
	while (i < (int)len)
	{
		*(b_int + i) = (unsigned char)c;
		i++;
	}
	return (b_int);
}
