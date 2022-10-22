/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:07:35 by mochan            #+#    #+#             */
/*   Updated: 2022/10/22 17:57:31 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*find_pipes(char *s)
{
	char	*pipes_loc;
	int		i;
	int		b_open_double_quote;

	i = 0;
	b_open_double_quote = 0;
	pipes_loc = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[i] != '\0')
	{
		if (is_double_quote(s[i]))
		{
			if (b_open_double_quote == 0)
				b_open_double_quote = 1;
			else if (b_open_double_quote == 1)
				b_open_double_quote = 0;
		}
		if (is_pipe(s[i]) && b_open_double_quote == 0)
			pipes_loc[i] = 'P';
		else
			pipes_loc[i] = '.';
		i++;
	}
	pipes_loc[i + 1] = '\0';
	return (pipes_loc);
}

void	ft_fill_splited_array_pipes(char **array_split, char *s, \
		char *pipes_loc, char c)
{
	int	counter[2];
	int	word_start;
	int	length;

	counter[0] = 0;
	counter[1] = 0;
	while (counter[0] < (int)ft_strlen(s))
	{
		if (pipes_loc[counter[0]] != c)
		{
			word_start = counter[0];
			length = 0;
			while (pipes_loc[counter[0]] != 0 && pipes_loc[counter[0]] != c)
			{
				length++;
				counter[0]++;
			}
			array_split[counter[1]] = (char *)ft_substr(s, word_start, length);
			counter[1]++;
		}
		else
			counter[0]++;
	}
	array_split[counter[1]] = NULL;
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
