/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:03:24 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 14:20:19 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	splitting_pipes(t_prgm *vars)
{
	int		i;
	char	**tab_token;

	if (vars->pipe_ct > 0)
	{
		tab_token = ft_split_cmd(vars->cmd_line, '|');
		vars->tokens = malloc(sizeof(t_token) * (vars->pipe_ct));
		i = 0;
		while (i < vars->pipe_ct)
		{
			vars->tokens[i].t_str = ft_strdup(tab_token[i]);
			vars->tokens[i].t_str_og = ft_strdup(tab_token[i]);
			free(tab_token[i]);
			i++;
		}
		free(tab_token);
	}
	else
		vars->tok_error = 1;
	init_all_tokens(vars);
}

void	parsing(t_prgm *vars)
{
	vars->pipe_ct = ft_nb_words_cmd(vars->cmd_line, '|');
	if (vars->pipe_ct == 0)
	{
		vars->tok_error = 1;
		return ;
	}
	splitting_pipes(vars);
	interpret_dollar_sign(vars);
	find_infile(vars);
	if (vars->tok_error != 1)
		find_outfile(vars);
	if (vars->tok_error == 1)
		printf("syntax error near unexpected token\n");
}
