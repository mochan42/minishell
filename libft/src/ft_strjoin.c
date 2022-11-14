/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:48:50 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/06 22:48:50 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	ft_jonction(char const *s1, char const *s2,
				char *str_joined, int length);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_joined;
	int		i;
	int		j;
	int		length;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	length = i + j;
	str_joined = (char *)malloc(sizeof(char) * length + 1);
	if (!str_joined)
		return (0);
	ft_jonction(s1, s2, str_joined, length);
	str_joined[length] = '\0';
	return (str_joined);
}

static void	ft_jonction(char const *s1, char const *s2,
char *str_joined, int length)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i + j < length)
	{
		if (s1[i] != 0)
		{
			str_joined[i + j] = s1[i];
			i++;
		}
		else if (s2[j] != 0)
		{
			str_joined[i + j] = s2[j];
			j++;
		}
	}
}
