/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:59:54 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 19:16:54 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_fill_splitted_array_cmd(t_fill_splitted_array_cmd *tmp, char c)
{
	tmp->word = 0;
	tmp->flag = -1;
	tmp->i = 0;
	tmp->c = c;
}

void	ft_fill_splited_array_cmd_helper(t_fill_splitted_array_cmd *tmp, \
	char **array_split, char *s)
{
	tmp->word_start = tmp->i;
	tmp->length = 0;
	tmp->flag = 0;
	while (tmp->i < tmp->s_len && tmp->flag == 0)
	{
		if (s[tmp->i] == tmp->c && \
			is_btw_q((char *)s, '"', tmp->i) == NULL && \
			is_btw_q((char *)s, '\'', tmp->i) == NULL)
		{
			tmp->flag = 1;
			tmp->i--;
		}
		else
		{
			tmp->flag = 0;
			tmp->length++;
		}
		tmp->i++;
	}
	array_split[tmp->word] = (char *)ft_substr(s, tmp->word_start, tmp->length);
	tmp->word++;
}

void	ft_fill_splited_array_cmd(char **array_split, char *s, char c)
{
	t_fill_splitted_array_cmd	tmp;

	tmp.s_len = (int)ft_strlen(s);
	init_fill_splitted_array_cmd(&tmp, c);
	while (tmp.i < tmp.s_len)
	{
		if (s[tmp.i] != c)
			ft_fill_splited_array_cmd_helper(&tmp, array_split, s);
		tmp.i++;
	}
	array_split[tmp.word] = 0;
}

char	**ft_split_cmd(char *s, char c)
{
	char	**array_result;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = ft_nb_words_cmd(s, c);
	array_result = malloc(sizeof(char *) * (nb_words + 1));
	ft_fill_splited_array_cmd(array_result, (char *)s, c);
	if (!array_result)
		return (NULL);
	return (array_result);
}
