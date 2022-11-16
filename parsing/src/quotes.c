/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 22:57:39 by mochan            #+#    #+#             */
/*   Updated: 2022/11/16 04:51:21 by fakouyat         ###   ########.fr       */
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
	int		**qts;
	int		*res;

	j[2] = ft_get_ref_qt_size(s, c);
	res = malloc(sizeof(int) * 2);
	qts = ft_ref_quote(s, c);
	j[0] = 0;
	j[1] = 0;
	while (j[0] < j[2] / 2)
	{
		if (qts[j[0]][0] != -1 && qts[j[0]][1] != -1)
		{
			if (check(ref, qts[j[0]][0], qts[j[0]][1], res) == 0 && j[1] == 0)
			{
				free(qts[j[0]]);
				j[1] = 1;
			}
		}
		j[0] += 1;
	}
	free(qts);
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
	level[0] = is_btw_val_sq(s, '\'', ref);
	if (level[0] != NULL)
	{
		level[1] = is_btw_q(s, '"', level[0][0]);
		level[2] = is_btw_q(s, '"', level[0][1]);
		if (level[1] != NULL || level[2] != NULL)
		{
			free(level[0]);
			free(level[1]);
			free(level[2]);
			return (1);
		}
		free(level[0]);
		free(level[1]);
		free(level[2]);
		return (0);
	}
	return (1);
}
