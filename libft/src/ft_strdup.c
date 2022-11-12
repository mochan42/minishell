/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:07:50 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/06 22:07:50 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**---------------------------------------------------------------------------*/
/* This functions create a new copy of a given string and return a pointer to 
	the new string
*/
char	*ft_strdup(const char *s)
{
	int		i;
	char	*s_cpy;

	i = 0;
	while (s[i] != 0)
		i++;
	s_cpy = (char *)malloc(sizeof(char) * (i + 1));
	if (!s_cpy)
		return (0);
	s_cpy[i] = '\0';
	while (i > 0)
	{
		s_cpy[i - 1] = s[i - 1];
		i--;
	}
	return (s_cpy);
}
