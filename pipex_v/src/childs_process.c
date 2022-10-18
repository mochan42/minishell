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

/* redirecting into fd according to the commands */
void	ft_childs_process(t_prgm *vars)
{
	if (vars->p.child == 0)
		ft_exec_cmd_1(vars);
	else if (vars->p.child > 0 && vars->p.child < vars->pipe_ct)
	{
		waitpid(vars->p.pid[vars->p.child - 1], &vars->p.status, 0);
		if (*vars->tokens[vars->p.child].in == '\0')
			dup2(vars->p.fd[vars->p.child - 1][0], 0);
		else if (ft_strncmp(vars->tokens[vars->p.child].in, "<<", 2) == 0)
		{

			while (!get_next_line(dup(vars->p.fd[vars->p.child - 1][0])))
				;
			ft_here_doc(vars, vars->p.child);
		}
		else if (ft_strncmp(vars->tokens[vars->p.child].in, "<", 1) == 0)
		{
			if (access(vars->tokens[vars->p.child].infile, F_OK | R_OK) != 0)
			{
				ft_bzero(vars->p.error[vars->p.child], 100);
				ft_strcat(vars->p.error[vars->p.child], strerror(errno));
				ft_strcat(vars->p.error[vars->p.child], " : ");
				ft_strcat(vars->p.error[vars->p.child], vars->tokens[vars->p.child].infile);
				ft_print_err_message(vars);
			}
			else
				vars->tokens[vars->p.child].fd_args[vars->p.child] = open(vars->tokens[vars->p.child].infile, O_RDONLY, 0777);
		}
		if (ft_strncmp(vars->tokens[vars->p.child].in, "<<", 2) == 0 || ft_strncmp(vars->tokens[vars->p.child].in, "<", 1) == 0)
		{
			dup2(vars->tokens[vars->p.child].fd_args[0], 0);
			close(vars->tokens[vars->p.child].fd_args[0]);
			unlink("tmp.txt");
		}
		if (*vars->tokens[0].out == '\0')
			dup2(vars->p.fd[vars->p.child][1], 1);
		if (ft_strncmp(vars->tokens[vars->p.child].out, ">>", 2) == 0)
			vars->tokens[vars->p.child].fd_args[1] = open(vars->tokens[vars->pipe_ct].outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
		else if (ft_strncmp(vars->tokens[vars->p.child].out, ">", 1) == 0)
			vars->tokens[vars->pipe_ct].fd_args[1] = open(vars->tokens[vars->pipe_ct].outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (ft_strncmp(vars->tokens[vars->p.child].out, ">>", 2) == 0 || ft_strncmp(vars->tokens[vars->p.child].out, ">", 1) == 0)
			dup2(vars->tokens[vars->p.child].fd_args[1], 1);
	}
	else if (vars->p.child == vars->pipe_ct)
		ft_exec_cmd_last(vars);
	ft_close_fds(vars);
}
