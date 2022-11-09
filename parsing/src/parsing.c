/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:03:24 by mochan            #+#    #+#             */
/*   Updated: 2022/11/09 21:01:00 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	splitting_pipes_no_pipes(t_prgm *vars)
{
	int	i;

	i = 0;
	vars->tokens = malloc(sizeof(t_token) * 1);
	vars->tokens[i].t_str = vars->cmd_line;
}

void	splitting_pipes(t_prgm *vars)
{
	int		i;
	char	**tab_token;
	char	*pipes_loc;

	i = 0;
	pipes_loc = find_pipes(vars->cmd_line);
	while (pipes_loc[i++] != '\0')
	{
		if (pipes_loc[i] == 'P')
			vars->pipe_ct++;
	}
	if (vars->pipe_ct > 0)
	{
		tab_token = ft_split_pipes(vars->cmd_line, 'P');
		vars->tokens = malloc(sizeof(t_token) * (vars->pipe_ct + 1));
		i = 0;
		while (i < vars->pipe_ct + 1)
		{
			vars->tokens[i].t_str = ft_strdup(tab_token[i]);
			vars->tokens[i].t_str_og = ft_strdup(tab_token[i]);
			// printf("PARSING v->tokens[%d].t_str_og :%s\n", i, vars->tokens[i].t_str_og);
			i++;
		}
	}
	else if (vars->pipe_ct == 0)
	{
		splitting_pipes_no_pipes(vars);
		vars->tokens[0].t_str_og = ft_strdup(vars->cmd_line);
	}
	init_all_tokens(vars);
}

void	parsing(t_prgm *vars)
{
	splitting_pipes(vars);
	interpret_dollar_sign(vars);
	find_infile(vars);
	if (vars->tok_error != 1)
		find_outfile(vars);
	if (vars->tok_error == 1)
		printf("syntax error near unexpected token\n");
}
