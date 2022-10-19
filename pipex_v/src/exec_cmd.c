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
	if (ft_strncmp(vars->tokens[0].in, "<<", 2) == 0)
		ft_here_doc(vars, 0);
	else if (ft_strncmp(vars->tokens[0].in, "<", 1) == 0)
		ft_infile_checking(vars);
	if (ft_strncmp(vars->tokens[0].in, "<<", 2) == 0 || ft_strncmp(vars->tokens[0].in, "<", 1) == 0)
	{
		dup2(vars->tokens[0].fd_args[0], 0);
		close(vars->tokens[0].fd_args[0]);
		unlink("tmp.txt");
	}
	if (*vars->tokens[0].out == '\0' && (vars->pipe_ct >= 1))
		dup2(vars->p.fd[0][1], 1);
	else
	{
		if (ft_strncmp(vars->tokens[0].out, ">>", 2) == 0)
			vars->tokens[0].fd_args[1] = open(vars->tokens[0].outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
		else if (ft_strncmp(vars->tokens[0].out, ">", 1) == 0)
			vars->tokens[0].fd_args[1] = open(vars->tokens[0].outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (ft_strncmp(vars->tokens[0].out, ">>", 2) == 0 || ft_strncmp(vars->tokens[0].out, ">", 1) == 0)
			dup2(vars->tokens[0].fd_args[1], 1);
	}
}

void	ft_exec_cmd_last(t_prgm *vars)
{
	if (*vars->tokens[vars->pipe_ct].in == '\0')
		dup2(vars->p.fd[vars->pipe_ct - 1][0], 0);
	else if (ft_strncmp(vars->tokens[vars->pipe_ct].in, "<<", 2) == 0)
		ft_mid_heredoc(vars);
	else if (ft_strncmp(vars->tokens[vars->pipe_ct].in, "<", 1) == 0)
		ft_infile_checking(vars);
	if (ft_strncmp(vars->tokens[vars->pipe_ct].in, "<<", 2) == 0 || ft_strncmp(vars->tokens[vars->pipe_ct].in, "<", 1) == 0)
	{
		dup2(vars->tokens[vars->pipe_ct].fd_args[0], 0);
		close(vars->tokens[vars->pipe_ct].fd_args[0]);
		unlink("tmp.txt");
	}
	/**----Out---*/
	if (ft_strncmp(vars->tokens[vars->pipe_ct].out, ">>", 2) == 0)
		vars->tokens[vars->pipe_ct].fd_args[1] = open(vars->tokens[vars->pipe_ct].outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (ft_strncmp(vars->tokens[vars->pipe_ct].out, ">", 1) == 0)
		vars->tokens[vars->pipe_ct].fd_args[1] = open(vars->tokens[vars->pipe_ct].outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (ft_strncmp(vars->tokens[vars->pipe_ct].out, ">>", 2) == 0 || ft_strncmp(vars->tokens[vars->pipe_ct].out, ">", 1) == 0)
		dup2(vars->tokens[vars->pipe_ct].fd_args[1], 1);
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
