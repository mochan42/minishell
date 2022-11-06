/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 22:57:39 by mochan            #+#    #+#             */
/*   Updated: 2022/11/06 15:28:50 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*s_cpy;

	i = 0;
	while (s[i] != 0)
		i++;
	s_cpy = (char *)malloc(sizeof(char *) * (i + 1));
	if (!s_cpy)
		return (0);
	s_cpy[i] = '\0';
	while (i > 0)
	{
		s_cpy[i - 1] = s[i - 1];
		i--;
	}
	return (s_cpy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	i = 0;
	if (s_len < len)
		sub_str = (char *)malloc(sizeof(char) * 1);
	else
		sub_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (NULL);
	while (i < len && start < s_len)
	{
		sub_str[i] = s[start];
		i++;
		start++;
	}
	sub_str[i] = 0;
	return (sub_str);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_char;
	unsigned char	*s2_char;
	size_t			i;

	s1_char = (unsigned char *)s1;
	s2_char = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_char[i] != s2_char[i])
			return (s1_char[i] - s2_char[i]);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	char	*haystack_char;

	haystack_char = (char *)haystack;
	if (needle[0] == '\0')
		return (haystack_char);
	len_needle = ft_strlen(needle);
	while (*haystack_char && len >= len_needle)
	{
		if (*haystack_char == *needle
			&& !(ft_memcmp(haystack_char, needle, len_needle)))
			return (haystack_char);
		haystack_char++;
		len--;
	}
	return (NULL);
}

int	cnt_quotes(char *s, char c)
{
	int	nb_quotes;

	nb_quotes = 0;
	while (*s)
	{
		if (*s == c)
			nb_quotes++;
		s++;
	}
	return (nb_quotes);
}


int	**ft_ref_quote(char *s, char c)
{
	int	size_array;
	int	**tab;
	int	i;
	int	j;
	
	i = 0;
	size_array = cnt_quotes(s, c);
	if (size_array % 2 != 0)
		size_array += 1;
	printf("size_array=%d\n", size_array);
	if (size_array > 0)
	{
		tab = malloc(sizeof(int *) * (size_array / 2));
		while (i < size_array / 2)
		{
			tab[i] = malloc(sizeof(int) * 2);
			tab[i][0] = -1;
			tab[i][1] = -1;
			i++;
		}
		i = 0;
		j = 0;
		while (j < ft_strlen(s))
		{
			if (s[j] == c)
			{
				if (tab[i][0] == -1)
					tab[i][0] = j;
				else
				{
					tab[i][1] = j;
					i++;
				}
			}
			j++;
		}
		return (tab);
	}
	return NULL;
}

/* are the number of quotes even?*/
int	is_quote_closed(char *s, char c)
{
	int	**quotes;
	int	size_array;
	int	i;

	size_array = cnt_quotes(s, c);
	if (size_array % 2 != 0)
		size_array += 1;
	quotes = ft_ref_quote(s, c);
	i = 0;
	while (i < size_array / 2)
	{
		if (quotes[i][0] == -1 || quotes[i][1] == -1)
			return (0);
		i++;
	}
	return (1);
}


int	*is_between_quotes(char *s, char *subs, char c)
{
	int		j;
	int		**quotes;
	int		size_array;
	char	*tmp;
	int		*res;
	
	size_array = cnt_quotes(s, c);
	res = malloc(sizeof(int) * 2);
	if (size_array % 2 != 0)
		size_array += 1;
	quotes = ft_ref_quote(s, c);
	j = 0;
	while (j < size_array / 2)
	{
		if (quotes[j][0] != -1 && quotes[j][1] != -1)
		{
			tmp = ft_substr(s, quotes[j][0], quotes[j][1] - quotes[j][0]);
			if (ft_strnstr(tmp, subs, ft_strlen(tmp)))
			{
				res[0] = quotes[j][0];
				res[1] = quotes[j][1];
				return (res);
			}
		}
		j++;
	}
	return (NULL);
}

/*  */
int	are_quotes_closed(char *s)
{
	int	**quotes;
	int	are_closed;
	int	size_array;
	int	i;
	
	are_closed = 0;
	size_array = cnt_quotes(s, '"');
	if (size_array % 2 != 0)
		size_array += 1;
	quotes = ft_ref_quote(s, '"');
	are_closed = is_quote_closed(s, '"');
	if (are_closed == 0)
	{
		i = 0;
		while (i < size_array / 2)
		{
			if (i == 0 && quotes[i][1] == -1)
				return (0);
			else
			{
				if (quotes[i][1] == -1)
				{
					if (is_between_quotes(s, ft_substr(&s[quotes[i][1]], 0, 1), '\'') == NULL &&
						((is_between_quotes(s, ft_substr(&s[quotes[i - 1][1]], 0, 1), '\'') != NULL &&
						 is_between_quotes(s, ft_substr(&s[quotes[i - 1][0]], 0, 1), '\'') != NULL
						) ||
						(is_between_quotes(s, ft_substr(&s[quotes[i - 1][1]], 0, 1), '\'') == NULL &&
						 is_between_quotes(s, ft_substr(&s[quotes[i - 1][0]], 0, 1), '\'') == NULL
						)
						))
						return (0);
				}
			}
			i++;
		}
	}
	// else if (!(is_between_quotes(s, ft_substr(&s[quotes[size_array / 2 - 1][0]], 0, 1), '\'') != NULL && 
	// 			is_between_quotes(s, ft_substr(&s[quotes[size_array / 2 - 1][1]], 0, 1), '\'') != NULL)
	// 		)
	// 	return (0);
	return (1);
}


int	main(void)
{
	int	**quotes;
	char *str;
	int	i;
	int	nb_quotes;
	int	size_array;
	int	*level[3];

	str = "Hello \"\'World toto\"\' !\n";
	size_array = cnt_quotes(str, '"');
	if (size_array % 2 != 0)
		size_array += 1;
	quotes = ft_ref_quote(str, '"');
	i = 0;
	while (i < size_array / 2)
	{
		printf("quotes[%d][0]=%d\n", i, quotes[i][0]);
		printf("quotes[%d][1]=%d\n", i, quotes[i][1]);
		i++;
	}
	if (are_quotes_closed(str) == 0)
	{
		printf("Quotes not closed\n");
		return (0);
	}
	level[0] = is_between_quotes(str, "World", '\'');
	if (level[0] != NULL)
	{
		level[1] = is_between_quotes(str, ft_substr(&str[level[0][0]], 0, 1), '"');
		level[2] = is_between_quotes(str, ft_substr(&str[level[0][1]], 0, 1), '"');
		if (level[1] != NULL || level[2] != NULL)
			printf("EXPAND\n");
		else
			printf("NO EXPAND\n");
	}
	else
		printf("EXPAND\n");
	return (0);
}
