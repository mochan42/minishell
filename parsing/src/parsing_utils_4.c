/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:06:15 by mochan            #+#    #+#             */
/*   Updated: 2022/11/10 19:53:41 by mochan           ###   ########.fr       */
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

void	err_msg_quotes_not_closed(void)
{
	printf("Quotes not closed.\n");
	exit (0);
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
	*str = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
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
			if (is_between_quotes((char *)s, '"', i) == NULL && \
				is_between_quotes((char *)s, '\'', i) == NULL)
			{
				result++;
			}
		}
		i++;
	}
	return (result);
}
