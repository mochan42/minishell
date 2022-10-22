/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:33:54 by mochan            #+#    #+#             */
/*   Updated: 2022/10/22 19:31:36 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_each_token(t_token *token)
{
	token->in = "";
	token->out = "";
	token->infile = "";
	token->outfile = "";
	token->bin = NULL;
	token->built_in = 0;
	token->options = NULL;
	token->t_str_exp = NULL;
	token->cmd = NULL;
}

void	init_all_tokens(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		init_each_token(&vars->tokens[i]);
		i++;
	}
}

// write echox to use echo as execve
void	init(t_prgm *vars)
{
	vars->pipe_ct = 0;
	ft_bzero(vars->curr_dir, MAX_LEN_DIR);
	vars->env_head = NULL;
	vars->env_head = init_env(vars);
	vars->builts[0] = "cd";
	vars->builts[1] = "echox";
	vars->builts[2] = "env";
	vars->builts[3] = "exit";
	vars->builts[4] = "export";
	vars->builts[5] = "pwd";
	vars->builts[6] = "unset";
}
