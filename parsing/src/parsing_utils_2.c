/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:07:35 by mochan            #+#    #+#             */
/*   Updated: 2022/11/14 17:30:27 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	validate_pipes(char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] == c)
		{
			if (is_btw_q((char *)s, '"', i) == NULL && \
				is_btw_q((char *)s, '\'', i) == NULL)
			{
				if (s[i + 1] != '\0' && s[i + 1] == c)
					if (is_btw_q((char *)s, '"', i + 1) == NULL && \
						is_btw_q((char *)s, '\'', i + 1) == NULL)
						return (1);
			}
		}
		i++;
	}
	return (0);
}
