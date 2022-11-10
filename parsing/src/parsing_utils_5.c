/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:38:04 by mochan            #+#    #+#             */
/*   Updated: 2022/11/10 02:59:21 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_true_pipes(t_finding_pipes *vars_tp, char *s)
{
	vars_tp->s = ft_strdup(s);
	vars_tp->pipes_loc = malloc(sizeof(char) * (ft_strlen(s) + 1));
	vars_tp->i = 0;
	vars_tp->b_open_double_quote = 0;
	vars_tp->b_open_single_quote = 0;
}

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

char	*trim_quotes(char *s)
{
	int		i;
	int		quote_opened;
	char	c;
	char	*res;
	int		j;

	i = 0;
	j = 0;
	quote_opened = 0;
	res = malloc(sizeof(char) * ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			c = s[i];
			quote_opened = 1;
			i++;
			while (s[i] != '\0' && s[i] != c)
			{
				res[j] = s[i];
				i++;
				j++;
			}
			if (quote_opened == 1 && s[i] != '\0')
				quote_opened = 0;
		}
		else
		{
			res[j] = s[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}
