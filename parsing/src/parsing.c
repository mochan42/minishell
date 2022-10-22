/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:03:24 by mochan            #+#    #+#             */
/*   Updated: 2022/10/22 18:23:25 by mochan           ###   ########.fr       */
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
			vars->tokens[i].t_str = tab_token[i];
			i++;
		}
	}
	else if (vars->pipe_ct == 0)
		splitting_pipes_no_pipes(vars);
	init_all_tokens(vars);
}

void	parsing(t_prgm *vars)
{
	splitting_pipes(vars);
	find_infile(vars);
	find_outfile(vars);
	find_cmd_opt_arg(vars);
	interpret_dollar_sign(vars);
}
