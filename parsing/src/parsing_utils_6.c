/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:59:54 by mochan            #+#    #+#             */
/*   Updated: 2022/11/07 19:09:33 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	ft_nb_words_cmd(char const *s, char c)
{
	int	i;
	int	result;

	if (!s)
		return (0);
	i = 0;
	result = 0;
	while (i <= (int)ft_strlen(s))
	{
		if ((s[i] == c || s[i] == 0) && i != 0 && (s[i - 1] != 0)
			&& s[i - 1] != c)
		{
			if (is_between_quotes((char *)s, '"', i) == NULL && is_between_quotes((char *)s, '\'', i) == NULL)
			{
				result++;
			}
		}
		i++;
	}
	return (result);
}

void	ft_fill_splited_array_cmd(char **array_split, char *s, char c)
{
	int	word_start;
	int	i;
	int	lenght;
	int	word;
	int	flag;

	i = 0;
	word = 0;
	flag = -1;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] != c)
		{
			word_start = i;
			lenght = 0;
			flag = 0;
			while (s[i] != 0 && flag == 0)
			{
				if (s[i] == c && \
					is_between_quotes((char *)s, '"', i) == NULL && \
					is_between_quotes((char *)s, '\'', i) == NULL)
				{
					flag = 1;
					i--;
				}
				else
				{
					flag = 0;
					lenght++;
				}
				i++;
			}
			array_split[word] = (char *)ft_substr(s, word_start, lenght);
			word++;
		}
		i++;
	}
	array_split[word] = 0;
}

char	**ft_split_cmd(char const *s, char c)
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
