/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 00:05:10 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/07 00:05:10 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <string.h>
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	char	*str_trimed;

	end = ft_strlen(s1) - 1;
	begin = 0;
	if (set == NULL)
		return ((char *)s1);
	if (s1 == NULL && set == NULL)
		return (NULL);
	while (ft_strchr(set, s1[begin]) && s1[begin])
		begin++;
	while (ft_strchr(set, s1[end]) && end > begin)
		end--;
	end -= begin;
	str_trimed = ft_substr(s1, begin, end + 1);
	if (!str_trimed)
		return (NULL);
	return (str_trimed);
}
