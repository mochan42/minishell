/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_last_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 02:27:18 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/18 02:27:18 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include "../inc/pipex.h"

void	ft_mid_heredoc(t_prgm *vars)
{
	while (!get_next_line(dup(vars->p.fd[vars->p.child - 1][0])))
		;
	ft_here_doc(vars, vars->p.child);
}

void	ft_infile_checking(t_prgm *vars, int *let_error)
{
	if (access(vars->tokens[vars->p.child].infile, F_OK | R_OK) != 0)
	{
		ft_bzero(vars->p.error[vars->p.child], 100);
		ft_strcat(vars->p.error[vars->p.child], strerror(errno));
		ft_strcat(vars->p.error[vars->p.child], " : ");
		ft_strcat(vars->p.error[vars->p.child], vars->tokens[vars->p.child].infile);
		*let_error = 1;
	}
	else
		vars->tokens[vars->p.child].fd_args[0] = open(vars->tokens[vars->p.child].infile, O_RDONLY, 0777);
}

void	ft_in_redirect(t_prgm *vars, int *let_error)
{
	if (*vars->tokens[vars->p.child].in == '\0')
		dup2(vars->p.fd[vars->p.child - 1][0], 0);
	else if (ft_strncmp(vars->tokens[vars->p.child].in, "<<", 2) == 0)
		;
	else if (ft_strncmp(vars->tokens[vars->p.child].in, "<", 1) == 0)
		ft_infile_checking(vars, let_error);
	if (ft_strncmp(vars->tokens[vars->p.child].in, "<<", 2) == 0 || ft_strncmp(vars->tokens[vars->p.child].in, "<", 1) == 0)
	{
		dup2(vars->tokens[vars->p.child].fd_args[0], 0);
		close(vars->tokens[vars->p.child].fd_args[0]);
	}
}
void	ft_redirect_out(t_prgm	*vars)
{
	if (*vars->tokens[0].out == '\0')
		dup2(vars->p.fd[vars->p.child][1], 1);
	if (ft_strncmp(vars->tokens[vars->p.child].out, ">>", 2) == 0)
		vars->tokens[vars->p.child].fd_args[1] = open(vars->tokens[vars->pipe_ct].outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (ft_strncmp(vars->tokens[vars->p.child].out, ">", 1) == 0)
		vars->tokens[vars->pipe_ct].fd_args[1] = open(vars->tokens[vars->pipe_ct].outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (ft_strncmp(vars->tokens[vars->p.child].out, ">>", 2) == 0 || ft_strncmp(vars->tokens[vars->p.child].out, ">", 1) == 0)
	{
		dup2(vars->tokens[vars->p.child].fd_args[1], 1);
		if (vars->pipe_ct > vars->p.child && ft_strncmp(vars->tokens[vars->p.child + 1].in, "<<", 2) == 0)
			dup2(vars->p.fd[vars->p.child][1], 1);
	}
}

/* redirecting into fd according to the commands */
void	ft_childs_process(t_prgm *vars)
{
	int	let_error;

	let_error = 0;
	if (vars->p.child == 0)
		ft_exec_cmd_1(vars, &let_error);
	else if (vars->p.child > 0 && vars->p.child < vars->pipe_ct)
	{
		//waitpid(vars->p.pid[vars->p.child - 1], &vars->p.status, 0);
		ft_in_redirect(vars, &let_error);
		if (let_error != 1)
			ft_bzero(vars->p.error[vars->p.child], 100);
		ft_redirect_out(vars);
	}
	else if (vars->p.child == vars->pipe_ct)
		ft_exec_cmd_last(vars, &let_error);
	let_error = 0;
	ft_close_fds(vars);
}
