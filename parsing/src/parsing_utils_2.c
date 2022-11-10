/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:07:35 by mochan            #+#    #+#             */
/*   Updated: 2022/11/10 20:20:52 by mochan           ###   ########.fr       */
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
	t_finding_pipes	true_pipes;

	init_true_pipes(&true_pipes, s);
	while (true_pipes.s[true_pipes.i] != '\0')
	{
		if (is_pipe(true_pipes.s[true_pipes.i]) && \
			is_between_quotes(true_pipes.s, '"', true_pipes.i) == NULL && \
			is_between_quotes(true_pipes.s, '\'', true_pipes.i) == NULL)
			true_pipes.pipes_loc[true_pipes.i] = 'P';
		else
			true_pipes.pipes_loc[true_pipes.i] = '.';
		true_pipes.i++;
	}
	free(true_pipes.s);
	true_pipes.pipes_loc[true_pipes.i] = '\0';
	return (true_pipes.pipes_loc);
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
	pipes_loc = NULL;
	pipes_loc = find_pipes((char *)s);
	nb_words = ft_nb_words_ms(pipes_loc, c);
	array_result = malloc(sizeof(char *) * (nb_words + 1));
	if (!array_result)
	{
		free(pipes_loc);
		free(array_result);
		return (NULL);
	}
	ft_fill_splited_array_pipes(array_result, (char *)s, pipes_loc, 'P');
	free(pipes_loc);
	return (array_result);
}
