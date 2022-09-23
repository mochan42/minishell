/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:20:58 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/17 04:15:26 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	char	*haystack_char;

	haystack_char = (char *)haystack;
	if (needle[0] == '\0')
		return (haystack_char);
	len_needle = ft_strlen(needle);
	while (*haystack_char && len >= len_needle)
	{
		if (*haystack_char == *needle
			&& !(ft_memcmp(haystack_char, needle, len_needle)))
			return (haystack_char);
		haystack_char++;
		len--;
	}
	return (NULL);
}
