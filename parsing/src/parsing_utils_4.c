/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:06:15 by mochan            #+#    #+#             */
/*   Updated: 2022/11/05 21:19:17 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// int	cnt_dlr(char *s)
// {
// 	int	nb_dlr_sign;

// 	nb_dlr_sign = 0;
// 	if (!s)
// 		return (0);
// 	while (*s++)
// 	{
// 		if (*s == '$')
// 			nb_dlr_sign++;
// 	}
// 	return (nb_dlr_sign);
// }

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

char	*ft_concat(char *str1, const char *str2)
{
	size_t	i;
	size_t	dst_str1;
	size_t	dst_str2;
	size_t	dst_ttl;
	char	*concatenated_str;

	if (!str1 && str2 != NULL)
		return(ft_strdup(str2));
	if (!str2 && str1 != NULL)
		return(ft_strdup(str1));
	dst_str1 = ft_strlen(str1);
	dst_str2 = ft_strlen(str2);
	dst_ttl = dst_str1 + dst_str2;
	concatenated_str = malloc(sizeof(char) * (dst_ttl + 1));
	if (!concatenated_str)
		return NULL;
	ft_bzero(concatenated_str, dst_ttl);
	concatenated_str[dst_ttl] = '\0';
	i = 0;
	while (str1[i] != '\0' && i < dst_str1)
	{
		concatenated_str[i] = str1[i];
		i++;
	}
	i = 0;
	while (str2[i] != '\0' && i < dst_str2)
	{
		concatenated_str[dst_str1 + i] = str2[i];
		i++;
	}
	return (concatenated_str);
}

void	ft_str_replace(char **str, char *subs_to_r, char *r_by)
{
	char	*ptr;
	char	*left;
	char	*right;
	char	*tmp[2];

	ptr = ft_strnstr(*str, subs_to_r, ft_strlen(*str));
	// printf("ptr	:%s\n", ptr);
	left = ft_substr(*str, 0, ptr - *str);
	// printf("left	:%s\n", left);
	right = ft_substr(ptr, ft_strlen(subs_to_r), ft_strlen(ptr));
	// printf("right	:%s\n", right);;
	tmp[0] = ft_strjoin(left, r_by);
	// printf("tmp 1	:%s\n", tmp[0]);
	tmp[1] = ft_strjoin(tmp[0], right);
	// printf("tmp 2	:%s\n", tmp[1]);
	*str = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
}
