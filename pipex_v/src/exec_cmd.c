/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_first_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 01:54:56 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/18 01:54:56 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
* Executing the first command :
* check in : "", "<<", "<"
* check infile
* redirect | stop
* check out "", ">>", "<"
* check outfile
* redirect | stop
* let execute
*/
void	ft_exec_cmd_1(t_prgm *vars)
{
	vars->tokens[0].in = "<<";
	if (vars->tokens[0].in == NULL)
		;
	else if (ft_strncmp(vars->tokens[0].in, "<<", 2) == 0)
	{
		ft_here_doc(vars, 0);
		dup2(vars->tokens[0].fd_args[0], 0);
	}
	/**----Out---*/
	if (vars->tokens[0].out == NULL)
	{
		if (vars->pipe_ct >= 1)
			dup2(vars->p.fd[0][1], 1);
	}
	else
	{
		vars->tokens[0].outfile = *(ft_split(ft_strnstr(vars->tokens[0].t_str, ">>", ft_strlen(vars->tokens[0].t_str)) + 2, ' '));
		if (ft_strncmp(vars->tokens[0].out, ">>", 2) == 0)
			vars->tokens[0].fd_args[1] = open(vars->tokens[0].outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
		else if (ft_strncmp(vars->tokens[0].out, ">", 1) == 0)
			vars->tokens[0].fd_args[1] = open(vars->tokens[0].outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
		dup2(vars->tokens[0].fd_args[1], 1);
	}
}

void	ft_exec_cmd_last(t_prgm *vars)
{
	// if (p->fd_hd < 0)
	// 	p->fd_args[1] = open(p->av[p->ac - 1],
	// 			O_CREAT | O_RDWR | O_TRUNC, 0777);
	// else
	// 	p->fd_args[1] = open(p->av[p->ac - 1],
	// 			O_CREAT | O_RDWR | O_APPEND, 0777);
	// dup2(p->fd[p->child - 1][0], 0);
	// dup2(p->fd_args[1], 1);
	// close(p->fd_args[1]);

	//vars->tokens[vars->p.child].in = "<<";
	if (vars->tokens[vars->p.child].in == NULL)
		dup2(vars->p.fd[vars->p.child - 1][0], 0);
	else if (ft_strncmp(vars->tokens[vars->p.child].in, "<<", 2) == 0)
	{
		ft_here_doc(vars, vars->p.child);
		dup2(vars->tokens[vars->p.child].fd_args[0], 0);
	}
	/**----Out---*/
	if (vars->tokens[vars->p.child].out == NULL)
		;
	else
	{
		vars->tokens[vars->p.child].outfile = *(ft_split(ft_strnstr(vars->tokens[vars->p.child].t_str, ">>", ft_strlen(vars->tokens[vars->p.child].t_str)) + 2, ' '));
		if (ft_strncmp(vars->tokens[0].out, ">>", 2) == 0)
			vars->tokens[vars->p.child].fd_args[1] = open(vars->tokens[vars->p.child].outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
		else if (ft_strncmp(vars->tokens[vars->p.child].out, ">", 1) == 0)
			vars->tokens[vars->p.child].fd_args[1] = open(vars->tokens[vars->p.child].outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
		dup2(vars->tokens[vars->p.child].fd_args[1], 1);
	}
}

void	ft_close_fds(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct)
	{
		close(vars->p.fd[i][0]);
		close(vars->p.fd[i][1]);
		i++;
	}
}
