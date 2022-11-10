/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:11:39 by mochan            #+#    #+#             */
/*   Updated: 2022/11/10 20:11:59 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	cnt_quotes(char *s, char c)
{
	int	nb_quotes;

	nb_quotes = 0;
	while (*s)
	{
		if (*s == c)
			nb_quotes++;
		s++;
	}
	return (nb_quotes);
}
