/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:03:26 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/01 00:03:26 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../inc/pipex.h"

void	ft_execve_cmds(t_prgm *vars)
{
	ft_childs_process(vars);
	if (vars->tokens[vars->p.child].built_in == 1)
		execbuilt_in(vars);
	else if (ft_is_error(vars) == 1)
	{
		if (is_our_env_path(vars) == 1)
		{
			if (execve(vars->tokens[vars->p.child].bin,
					vars->tokens[vars->p.child].options, vars->env) == -1)
				exit(127);
		}
		else
		{
			printf("Environment PATH doesn't exist\n");
			exit(127);
		}
	}
	if (vars->tokens[vars->p.child].built_in != 1)
		exit (1);
	exit(0);
}

int	ft_is_env_buil_ins(t_prgm *vars)
{
	int	i;

	i = 1;
	if (ft_strcmp(vars->tokens[vars->p.child].options[0], "cd") == 0)
		ft_cd(vars);
	else if (ft_strcmp(vars->tokens[vars->p.child].options[0], "export")
		== 0 && vars->tokens[vars->p.child].options[1])
		ft_export(vars);
	else if (ft_strcmp(vars->tokens[vars->p.child].options[0],
			"unset") == 0)
		ft_unset(vars, NULL);
	else if (ft_strcmp(vars->tokens[vars->p.child].options[0], "exit") == 0)
		ft_exit(vars);
	else
		i = 0;
	return (i);
}

int	ms_executor(t_prgm *vars)
{
	ft_valid_args(vars);
	if (vars->tok_error == 1)
	{
		printf("syntax error near unexpected token\n");
		return (0);
	}
	ft_generate_p(vars);
	if (ft_anticipate_heredoc(vars) == 1)
		return (0);
	vars->p.child = 0;
	while (vars->p.child < vars->pipe_ct + 1)
	{
		if (ft_is_env_buil_ins(vars) == 1)
			;
		else
		{
			vars->p.pid[vars->p.child] = fork();
			if (vars->p.pid[vars->p.child] == 0)
				ft_execve_cmds(vars);
		}
		ft_bzero(vars->p.error[vars->p.child], 100);
		vars->p.child += 1;
	}
	ft_parent_process(vars);
	return (0);
}

int	ft_anticipate_heredoc(t_prgm *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		j = 0;
		while (j < vars->tokens[i].nb_input)
		{
			if (vars->tokens[i].in[j] == IN_HEREDOC)
				ft_here_doc(vars, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

// int	ft_only_outfile(t_prgm *vars)
// {
// 	int	i;

// 	i = 0;
// 	while (i < vars->pipe_ct + 1)
// 	{
// 		if (ft_strcmp(vars->tokens[i].cmd, "") == 0)
// 		{
// 			if (ft_strcmp(*vars->tokens[i].outfile, "") != 0)
// 			{
// 				unlink(*vars->tokens[i].outfile);
// 				vars->tokens[i].fd_args[0] = open(*vars->tokens[i].outfile,
// 						O_CREAT | O_TRUNC, 0777);
// 				ft_exit_code(0, 1);
// 				i++;
// 				continue ;
// 			}
// 			printf("syntax error near unexpected token\n");
// 			ft_exit_code(2, 1);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
