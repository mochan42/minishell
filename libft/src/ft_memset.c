/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:27:57 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/25 15:35:52 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
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
