/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 22:57:39 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 20:39:40 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	ft_ref_quote_helper(int **tab, char *s, char c)
{
	int		i;
	size_t	j;

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
}

int	**ft_ref_quote(char *s, char c)
{
	int		size_array;
	int		**tab;
	int		i;

	i = 0;
	size_array = ft_get_ref_qt_size(s, c);
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
		ft_ref_quote_helper(tab, s, c);
		return (tab);
	}
	return (NULL);
}

int	*is_btw_q(char *s, char c, int ref)
{
	int		j[3];
	int		**quotes;
	int		*res;

	j[2] = ft_get_ref_qt_size(s, c);
	res = malloc(sizeof(int) * 2);
	quotes = ft_ref_quote(s, c);
	j[0] = 0;
	j[1] = 0;
	while (j[0] < j[2] / 2)
	{
		if (quotes[j[0]][0] != -1 && quotes[j[0]][1] != -1)
		{
			if (ref > quotes[j[0]][0] && ref < quotes[j[0]][1] && j[1] == 0)
			{
				res[0] = quotes[j[0]][0];
				res[1] = quotes[j[0]][1];
				free(quotes[j[0]]);
				j[1] = 1;
			}
		}
		j[0] += 1;
	}
	free(quotes);
	if (j[1] == 1)
		return (res);
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
		if (tmp[i] == '"' || tmp[i] == '\'')
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
	level[0] = is_btw_q(s, '\'', ref);
	if (level[0] != NULL)
	{
		level[1] = is_btw_q(s, '"', level[0][0]);
		level[2] = is_btw_q(s, '"', level[0][1]);
		if (level[1] != NULL || level[2] != NULL)
			return (1);
		return (0);
	}
	return (1);
}
