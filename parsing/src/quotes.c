/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 22:57:39 by mochan            #+#    #+#             */
/*   Updated: 2022/11/09 23:46:10 by mochan           ###   ########.fr       */
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

int	**ft_ref_quote(char *s, char c)
{
	int		size_array;
	int		**tab;
	int		i;
	size_t	j;

	i = 0;
	size_array = cnt_quotes(s, c);
	if (size_array % 2 != 0)
		size_array += 1;
	if (size_array > 0)
	{
		tab = malloc(sizeof(int *) * (size_array / 2));
		while (i < size_array / 2)
		{
			tab[i] = malloc(sizeof(int) * 2);
			tab[i][0] = -1;
			tab[i][1] = -1;
			i++;
		}
		i = 0;
		j = 0;
		while (j < ft_strlen(s))
		{
			if (s[j] == c)
			{
				if (tab[i][0] == -1)
					tab[i][0] = j;
				else
				{
					tab[i][1] = j;
					i++;
				}
			}
			j++;
		}
		return (tab);
	}
	return (NULL);
}

int	*is_between_quotes(char *s, char c, int ref)
{
	int		j;
	int		**quotes;
	int		size_array;
	int		*res;

	size_array = cnt_quotes(s, c);
	res = malloc(sizeof(int) * 2);
	if (size_array % 2 != 0)
		size_array += 1;
	quotes = ft_ref_quote(s, c);
	j = 0;
	while (j < size_array / 2)
	{
		if (quotes[j][0] != -1 && quotes[j][1] != -1)
		{
			if (ref > quotes[j][0] && ref < quotes[j][1])
			{
				res[0] = quotes[j][0];
				res[1] = quotes[j][1];
				return (res);
			}
		}
		j++;
	}
	quotes = NULL;
	return (NULL);
}

int	are_quotes_closed_v3(char *s)
{
	int		i;
	int		quote_opened;
	char	c;
	char	*tmp;

	i = 0;
	quote_opened = 0;
	tmp = ft_strdup(s);
	while (tmp[i] != '\0')
	{
		if (tmp[i] == (char) '"' || tmp[i] == (char) '\'')
		{
			c = tmp[i];
			quote_opened = 1;
			i++;
			while (tmp[i] != '\0' && tmp[i] != c)
				i++;
			if (quote_opened == 1 && tmp[i] != '\0')
				quote_opened = 0;
		}
		i++;
	}
	free(tmp);
	return (quote_opened);
}

int	expand_ds(char *s, int ref)
{
	int	size_array;
	int	*level[3];

	size_array = cnt_quotes(s, '"');
	if (size_array % 2 != 0)
		size_array += 1;
	level[0] = is_between_quotes(s, '\'', ref);
	if (level[0] != NULL)
	{
		level[1] = is_between_quotes(s, '"', level[0][0]);
		level[2] = is_between_quotes(s, '"', level[0][1]);
		if (level[1] != NULL || level[2] != NULL)
			return (1);
		else
			return (0);
	}
	else
		return (1);
}
