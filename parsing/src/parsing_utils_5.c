/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:38:04 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 14:06:00 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_trim_quotes(t_trim_quotes *tmp, char *s)
{
	tmp->i = 0;
	tmp->j = 0;
	tmp->quote_opened = 0;
	tmp->res = malloc(sizeof(char) * ft_strlen(s) + 1);
}

void	trim_quotes_helper(t_trim_quotes *tmp, char *s)
{
	while (s[tmp->i] != '\0')
	{
		if (s[tmp->i] == '"' || s[tmp->i] == '\'')
		{
			tmp->c = s[tmp->i];
			tmp->quote_opened = 1;
			tmp->i++;
			while (s[tmp->i] != '\0' && s[tmp->i] != tmp->c)
			{
				tmp->res[tmp->j] = s[tmp->i];
				tmp->i++;
				tmp->j++;
			}
			if (tmp->quote_opened == 1 && s[tmp->i] != '\0')
				tmp->quote_opened = 0;
		}
		else
		{
			tmp->res[tmp->j] = s[tmp->i];
			tmp->j++;
		}
		tmp->i++;
	}
	tmp->res[tmp->j] = '\0';
}

char	*trim_quotes(char *s)
{
	t_trim_quotes	tmp;
	char			*res;
	init_trim_quotes(&tmp, s);
	trim_quotes_helper(&tmp, s);
	res = ft_strdup(tmp.res);
	free(tmp.res);
	return (res);
}