/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:27:39 by mochan            #+#    #+#             */
/*   Updated: 2022/10/21 23:23:10 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

/* helper function to fill array of strings for ft_split_2 (split by string delimiter)*/
void	ft_fill_splited_array_2(char **array_split, char *s, char *needle)
{
	int		word_start;
	int		i;
	int		length;
	int		word;
	int		len_needle;
	int		j;
	char	*ptr;
	int		len_s;

	len_needle = ft_strlen(needle);
	len_s = ft_strlen(s);
	i = 0;
	word = 0;
	while (i < len_s && s[i] != '\0')
	{
		i = 0;
		ptr = ft_substr(s, i, len_needle);
		if (ft_strncmp(ptr, needle, len_needle) != 0)
		{
			word_start = i;
			length = 0;
			while (ft_strncmp(ptr, needle, len_needle) != 0 && *ptr != 0 && s[i] != '\0')
			{
				i++;
				length++;
				ptr = ft_substr(s, i, len_needle);
			}
			array_split[word] = (char *)ft_substr(s, word_start, length);
			while (length > 0)
			{
				s++;
				length--;
			}
			word++;
		}
		j = 0;
		while (j < len_needle && *s)
		{
			ptr++;
			s++;
			j++;
			i++;
		}
		i = 0;
	}
	array_split[word] = 0;
}

/* helper function to count words for ft_split_2 (split by string delimiter)*/
int	ft_nb_words_2(char const *s, char *needle)
{
	int			i;
	int			result;
	int			len_needle;
	const char	*ptr;
	int			j;

	if (!s)
		return (0);
	len_needle = ft_strlen(needle);
	ptr = s;
	i = 0;
	j = 0;
	result = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (((ft_strnstr(ptr, needle, len_needle) != NULL && needle != NULL) || s[i] == 0) && i != 0)
		{
			result++;
			i = i + len_needle + 1;
			j = 0;
			while (j <= len_needle)
			{
				ptr++;
				j++;
			}
		}
		else
		{
			i++;
			ptr++;
		}
	}
	return (result);
}

/*function to split a string "s" by string delimiter "needle"*/
char	**ft_split_2(char const *s, char *needle)
{
	char	**array_result;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = ft_nb_words_2(s, needle);
	array_result = malloc(sizeof(char *) * (nb_words + 1));
	ft_fill_splited_array_2(array_result, (char *)s, needle);
	if (!array_result)
		return (NULL);
	return (array_result);
}
