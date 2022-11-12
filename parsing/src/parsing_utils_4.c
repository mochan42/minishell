/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:06:15 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 22:05:14 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	cnt_dlr(char *s)
{
	int	i;
	int	nb_dlr_sign;

	i = 0;
	nb_dlr_sign = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '$')
			nb_dlr_sign++;
		i++;
	}
	return (nb_dlr_sign);
}

int	check(int ref, int start, int end, int *res)
{
	if (ref > start && ref < end)
	{
		res[0] = start;
		res[1] = end;
		return (0);
	}
	return (1);
}

char	*ft_strnstr_ms(const char *haystack, \
	const char *needle, size_t len, int occ)
{
	size_t	len_needle;
	char	*haystack_char;
	int		occ_copy;

	occ_copy = 0;
	haystack_char = (char *)haystack;
	if (needle[0] == '\0')
		return (haystack_char);
	len_needle = ft_strlen(needle);
	while (*haystack_char && len >= len_needle)
	{
		if (*haystack_char == *needle
			&& !(ft_memcmp(haystack_char, needle, len_needle)))
		{
			if (occ == occ_copy)
				return (haystack_char);
			else
				occ_copy++;
		}
		haystack_char++;
		len--;
	}
	return (NULL);
}

void	ft_str_replace(char **str, char *subs_to_r, char *r_by, int ref)
{
	char	*ptr;
	char	*left;
	char	*right;
	char	*tmp[2];

	ptr = ft_strnstr(*str + ref, subs_to_r, ft_strlen(*str));
	left = ft_substr(*str, 0, ptr - *str);
	right = ft_substr(ptr, ft_strlen(subs_to_r), ft_strlen(ptr));
	tmp[0] = ft_strjoin(left, r_by);
	tmp[1] = ft_strjoin(tmp[0], right);
	if (*str)
		free(*str);
	*str = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(left);
	free(right);
}

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
			if (is_btw_q((char *)s, '"', i) == NULL && \
				is_btw_q((char *)s, '\'', i) == NULL)
			{
				result++;
			}
		}
		i++;
	}
	return (result);
}
