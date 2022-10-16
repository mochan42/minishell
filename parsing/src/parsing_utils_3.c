/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:49:17 by mochan            #+#    #+#             */
/*   Updated: 2022/10/15 14:32:01 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	is_pipe(char c)
{
	int	i;

	if (c == '|')
		i = 1;
	else
		i = 0;
	return (i);
}

int	is_double_quote(char c)
{
	int	i;

	if (c == '\"')
		i = 1;
	else
		i = 0;
	return (i);
}

int	is_single_quote(char c)
{
	int	i;

	if (c == '\"')
		i = 1;
	else
		i = 0;
	return (i);
}

int	count_double_quotes(char *s)
{
	int	nb_d_quotes;

	nb_d_quotes = 0;
	while (*s)
	{
		if (*s == '\"')
			nb_d_quotes++;
		s++;
	}
	return (nb_d_quotes);
}

int	count_single_quotes(char *s)
{
	int	nb_s_quotes;

	nb_s_quotes = 0;
	while (*s)
	{
		if (*s == '\'')
			nb_s_quotes++;
		s++;
	}
	return (nb_s_quotes);
}