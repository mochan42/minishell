/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:13:20 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/01 16:13:20 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/**---------------------------------------------------------------------------*/
/* This functions is almost same with strchr, the only difference reversing
*/

char	*ft_strrchr(const char *s, int c)
{
	int		size;

	size = ft_strlen(s);
	while (size >= 0)
	{
		if (s[size] == (char)c)
			return ((char *)(s + size));
		size--;
	}
	return (0);
}
