/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:07:35 by mochan            #+#    #+#             */
/*   Updated: 2022/09/28 13:08:55 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../minishell.h"
#include "../inc/parser.h"

int	ft_nb_words_ms(char const *s, char c)
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
			result++;
		i++;
	}
	return (result);
}

int	is_pipe(char c)
{
	int	i;

	if (c == '|')
		i = 1;
	else
		i = 0;
	return (i);
}

int	is_doubleQuote(char c)
{
	int	i;

	if (c == '\"')
		i = 1;
	else
		i = 0;
	return (i);
}

char	*find_pipes(char *s)
{
	char	*pipes_loc;
	int		len;
	int		i;
	int		res;
	int		b_openDoubleQuote;

	len = ft_strlen(s) + 1;
	i = 0;
	b_openDoubleQuote = 0;
	pipes_loc = malloc(sizeof(char) * len);
	while (s[i] != '\0')
	{
		res = is_pipe(s[i]);
		if (is_doubleQuote(s[i]))
		{
			if (b_openDoubleQuote == 0)
				b_openDoubleQuote = 1;
			else if (b_openDoubleQuote == 1)
				b_openDoubleQuote = 0;
		}
		if (is_pipe(s[i]) && b_openDoubleQuote == 0)
			pipes_loc[i] = 'P';
		else
			pipes_loc[i] = '.';
		i++;
	}
	pipes_loc[len] = '\0';
	return (pipes_loc);
}

void	ft_fill_splited_array_pipes(char **array_split, char *s, char *pipes_loc, char c)
{
	int	word_start;
	int	i;
	int	length;
	int	word;
	int	len_s;
	
	i = 0;
	word = 0;
	len_s = (int)ft_strlen(s);
	while (i < len_s)
	{
		if (pipes_loc[i] != c)
		{
			word_start = i;
			length = 0;
			while (pipes_loc[i] != 0 && pipes_loc[i] != c)
			{
				length++;
				i++;
			}
			array_split[word] = (char *)ft_substr(s, word_start, length);
			word++;
		}
		else
		{
			i++;
		}
	}
	array_split[word] = NULL;
}

char	**ft_split_pipes(char const *s, char c)
{
	char	**array_result;
	int		nb_words;
	char	*pipes_loc;

	if (!s)
		return (NULL);
	pipes_loc = find_pipes((char *)s);
	nb_words = ft_nb_words_ms(pipes_loc, c);
	array_result = malloc(sizeof(char *) * (nb_words + 1));
	if (!array_result)
		return (NULL);
	ft_fill_splited_array_pipes(array_result, (char *)s, pipes_loc, 'P');
	return (array_result);
}
