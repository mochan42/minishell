/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:04:39 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/25 15:35:46 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_int;
	char	*src_int;
	int		i;

	dst_int = (char *)dst;
	src_int = (char *)src;
	if (!dst_int && !src_int)
		return (0);
	i = 0;
	while (i < (int)n)
	{
		*(dst_int + i) = *(src_int + i);
		i++;
	}
	return (dst);
}
