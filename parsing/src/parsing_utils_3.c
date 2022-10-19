/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:49:17 by mochan            #+#    #+#             */
/*   Updated: 2022/10/19 13:44:06 by mochan           ###   ########.fr       */
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

int	cnt_dquotes(char *s)
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

int	cnt_squotes(char *s)
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