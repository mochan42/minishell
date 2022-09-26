/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:27:39 by mochan            #+#    #+#             */
/*   Updated: 2022/09/26 22:22:15 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../minishell.h"
#include "../inc/parser.h"

// size_t	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// int	ft_memcmp(const void *s1, const void *s2, size_t n)
// {
// 	unsigned char	*s1_char;
// 	unsigned char	*s2_char;
// 	size_t			i;

// 	s1_char = (unsigned char *)s1;
// 	s2_char = (unsigned char *)s2;
// 	i = 0;
// 	while (i < n)
// 	{
// 		if (s1_char[i] != s2_char[i])
// 			return (s1_char[i] - s2_char[i]);
// 		i++;
// 	}
// 	return (0);
// }

// char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
// {
// 	size_t	len_needle;
// 	char	*haystack_char;

// 	haystack_char = (char *)haystack;
// 	if (needle[0] == '\0')
// 		return (haystack_char);
// 	len_needle = ft_strlen(needle);
// 	while (*haystack_char && len >= len_needle)
// 	{
// 		if (*haystack_char == *needle
// 			&& !(ft_memcmp(haystack_char, needle, len_needle)))
// 			return (haystack_char);
// 		haystack_char++;
// 		len--;
// 	}
// 	return (NULL);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	if (n == 0)
// 		return (0);
// 	i = 0;
// 	while (i + 1 < n && s1[i] != 0)
// 	{
// 		if (s1[i] != s2[i])
// 			break ;
// 		i++;
// 	}
// 	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*sub_str;
// 	size_t	i;
// 	size_t	s_len;

// 	s_len = ft_strlen(s);
// 	i = 0;
// 	if (s_len < len)
// 		sub_str = (char *)malloc(sizeof(char) * 1);
// 	else
// 		sub_str = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!sub_str)
// 		return (NULL);
// 	while (i < len && start < s_len)
// 	{
// 		sub_str[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	sub_str[i] = 0;
// 	return (sub_str);
// }

void	ft_fill_splited_array_2(char **array_split, char *s, char *needle)
{
	int		word_start;
	int		i;
	int		length;
	int		word;
	int		len_needle;
	int		j;
	char	*ptr;

	len_needle = ft_strlen(needle);
	i = 0;
	word = 0;
	while (i < (int)ft_strlen(s))
	{
		i = 0;
		ptr = ft_substr(s, i, len_needle);
		if (ft_strncmp(ptr, needle, len_needle) != 0)
		{
			word_start = i;
			length = 0;
			while (ft_strncmp(ptr, needle, len_needle) != 0 && *ptr != 0)
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
		while (j < len_needle)
		{
			ptr++;
			s++;
			j++;
		}
	}
	array_split[word] = 0;
}

int	ft_nb_words_2(char const *s, char *needle)
{
	int	i;
	int	result;
	int	len_needle;
	const char *ptr;
	int j;

	if (!s)
		return (0);
	len_needle = ft_strlen(needle);
	ptr = s;
	i = 0;
	j = 0;
	result = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (((ft_strnstr(ptr, needle, len_needle) != NULL && needle != NULL) || s[i] == 0) && i!= 0)
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
