/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:35:07 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/13 14:44:14 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_int;
	char	*src_int;
	size_t	i;

	dst_int = (char *)dst;
	src_int = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (src_int > dst_int)
	{
		i = 0;
		while (i < len)
		{
			dst_int[i] = src_int[i];
			i++;
		}
		return (dst_int);
	}
	while (len > 0)
	{
		dst_int[len - 1] = src_int[len - 1];
		len--;
	}
	return (dst_int);
}
