/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:38:04 by mochan            #+#    #+#             */
/*   Updated: 2022/11/10 20:20:35 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	check_if_double_quote_open_or_closed(t_finding_pipes *vars_tp)
{
	if (is_double_quote(vars_tp->s[vars_tp->i]))
	{
		if (vars_tp->b_open_double_quote == 0)
			vars_tp->b_open_double_quote = 1;
		else if (vars_tp->b_open_double_quote == 1)
			vars_tp->b_open_double_quote = 0;
	}	
}

void	check_if_single_quote_open_or_closed(t_finding_pipes *vars_tp)
{
	if (is_single_quote(vars_tp->s[vars_tp->i]))
	{
		if (vars_tp->b_open_single_quote == 0)
			vars_tp->b_open_single_quote = 1;
		else if (vars_tp->b_open_single_quote == 1)
			vars_tp->b_open_single_quote = 0;
	}
}

void	init_trim_quotes(t_trim_quotes *tmp, char *s)
{
	tmp->i = 0;
	tmp->j = 0;
	tmp->quote_opened = 0;
	tmp->res = malloc(sizeof(char) * ft_strlen(s));
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

	init_trim_quotes(&tmp, s);
	trim_quotes_helper(&tmp, s);
	return (tmp.res);
}
