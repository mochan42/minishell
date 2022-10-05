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
	vars->tokens[0].built_in = 1;
	//vars->tokens[0].infile = "file";
	//vars->tokens[0].outfile= "file2";

	//vars->tokens[0].outfile = "file2";
	if (ft_strncmp(vars->tokens[0].in, "<<", 2) == 0)
		ft_here_doc(vars, 0);
	else if (ft_strncmp(vars->tokens[0].in, "<", 1) == 0)
	{
		if (access(vars->tokens[0].infile, F_OK | R_OK) != 0)
		{
			ft_bzero(vars->p.error[0], 100);
			ft_strcat(vars->p.error[0], strerror(errno));
			ft_strcat(vars->p.error[0], " : ");
			ft_strcat(vars->p.error[0], vars->tokens[0].infile);
			ft_print_err_message(vars);
		}
		else
			vars->tokens[0].fd_args[0] = open(vars->tokens[0].infile, O_RDONLY, 0777);
	}
	if (ft_strncmp(vars->tokens[0].in, "<<", 2) == 0 || ft_strncmp(vars->tokens[0].in, "<", 1) == 0)
		dup2(vars->tokens[0].fd_args[0], 0);
	/**----Out---*/
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
	//vars->tokens[0].out = ">>";
	//vars->tokens[0].infile = "file";
	//vars->tokens[0].outfile= "file2";

	//vars->tokens[0].outfile = "file2";
	if (*vars->tokens[vars->pipe_ct].in == '\0')
		dup2(vars->p.fd[vars->pipe_ct - 1][0], 0);
	else if (ft_strncmp(vars->tokens[vars->pipe_ct].in, "<<", 2) == 0)
		ft_here_doc(vars, vars->pipe_ct);
	else if (ft_strncmp(vars->tokens[vars->pipe_ct].in, "<", 1) == 0)
	{
		if (access(vars->tokens[vars->pipe_ct].infile, F_OK | R_OK) != 0)
		{
			ft_bzero(vars->p.error[vars->pipe_ct], 100);
			ft_strcat(vars->p.error[vars->pipe_ct], strerror(errno));
			ft_strcat(vars->p.error[vars->pipe_ct], " : ");
			ft_strcat(vars->p.error[vars->pipe_ct], vars->tokens[vars->pipe_ct].infile);
			ft_print_err_message(vars);
		}
		else
			vars->tokens[vars->pipe_ct].fd_args[vars->pipe_ct] = open(vars->tokens[vars->pipe_ct].infile, O_RDONLY, 0777);
	}
	if (ft_strncmp(vars->tokens[vars->pipe_ct].in, "<<", 2) == 0 || ft_strncmp(vars->tokens[vars->pipe_ct].in, "<", 1) == 0)
		dup2(vars->tokens[vars->pipe_ct].fd_args[0], 0);
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
