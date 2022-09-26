/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:02:55 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/25 15:36:22 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_len_str(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	int		size_src;

	size_src = 0;
	size_src = ft_len_str(src);
	i = 0;
	while (i + 1 < dstsize && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = 0;
	return (size_src);
}

static int	ft_len_str(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
