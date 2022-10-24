/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:06:15 by mochan            #+#    #+#             */
/*   Updated: 2022/10/19 19:06:52 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	cnt_dlr(char *s)
{
	int	nb_dlr_sign;

	nb_dlr_sign = 0;
	if (!s)
		return (0);
	while (*s++)
	{
		if (*s == '$')
			nb_dlr_sign++;
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

	dst_str1 = ft_strlen(str1);
	dst_str2 = ft_strlen(str2);
	dst_ttl = dst_str1 + dst_str2;
	concatenated_str = malloc(sizeof(char) * (dst_ttl + 1));
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
