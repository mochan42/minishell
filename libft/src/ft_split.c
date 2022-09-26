/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:33:34 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/08 17:33:34 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_fill_splited_array(char **array_split, char *s, char c)
{
	int	word_start;
	int	i;
	int	lenght;
	int	word;

	i = 0;
	word = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] != c)
		{
			word_start = i;
			lenght = 0;
			while (s[i] != 0 && s[i] != c)
			{
				lenght++;
				i++;
			}
			array_split[word] = (char *)ft_substr(s, word_start, lenght);
			word++;
		}
		i++;
	}
	array_split[word] = 0;
}

static int	ft_nb_words(char const *s, char c)
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

char	**ft_split(char const *s, char c)
{
	char	**array_result;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = ft_nb_words(s, c);
	array_result = malloc(sizeof(char *) * (nb_words + 1));
	ft_fill_splited_array(array_result, (char *)s, c);
	if (!array_result)
		return (NULL);
	return (array_result);
}
