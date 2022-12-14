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
void	ft_processing_output_1(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->tok[0].nb_output)
	{
		if (vars->tok[0].out[i] == OUT_APPEND)
			vars->tok[0].fd_args[i][1] = open(vars->tok[0].outfile[i],
					O_RDWR | O_CREAT | O_APPEND, 0777);
		else if (vars->tok[0].out[i] == OUT_REDIRECT)
			vars->tok[0].fd_args[i][1] = open(vars->tok[0].outfile[i],
					O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (vars->tok[0].out[i] == OUT_APPEND
			|| vars->tok[0].out[i] == OUT_REDIRECT)
		{
			dup2(vars->tok[0].fd_args[i][1], 1);
			close(vars->tok[0].fd_args[i][1]);
		}
		i++;
	}
}

void	ft_exec_cmd_1(t_prgm *vars, int *let_error)
{
	int	i;

	i = 0;
	if (vars->tok[0].in == NULL)
	{
	}
	while (i < vars->tok[0].nb_input)
	{
		if (vars->tok[0].in[i] == IN_REDIRECT)
			ft_infile_checking(vars, let_error);
		if (vars->tok[0].in[i] == IN_HEREDOC
			|| vars->tok[0].in[i] == IN_REDIRECT)
		{
			dup2(vars->tok[0].fd_args[i][0], 0);
			close(vars->tok[0].fd_args[i][0]);
		}
		i++;
	}
	ft_print_err_message(vars);
	if (*let_error != 1)
		ft_bzero(vars->p.error[vars->p.child], 100);
	if (vars->tok[0].out == NULL && (vars->pipe_ct > 1))
		dup2(vars->p.fd[0][1], 1);
	ft_processing_output_1(vars);
}

void	ft_processing_output(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->tok[vars->p.child].nb_output)
	{
		if (vars->tok[vars->p.child].out[i] == OUT_APPEND)
			vars->tok[vars->p.child].fd_args[i][1] = open(
					vars->tok[vars->p.child].outfile[i],
					O_RDWR | O_CREAT | O_APPEND, 0777);
		else if (vars->tok[vars->p.child].out[i] == OUT_REDIRECT)
			vars->tok[vars->p.child].fd_args[i][1] = open(
					vars->tok[vars->p.child].outfile[i],
					O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (vars->tok[vars->p.child].out[i] == OUT_APPEND
			|| vars->tok[vars->p.child].out[i] == OUT_REDIRECT)
		{
			dup2(vars->tok[vars->p.child].fd_args[i][1], 1);
			close(vars->tok[vars->p.child].fd_args[i][1]);
		}
		i++;
	}
}

void	ft_exec_cmd_last(t_prgm *vars, int *let_error)
{
	int	i;

	i = 0;
	if (vars->tok[vars->p.child].in == NULL)
		dup2(vars->p.fd[vars->p.child - 1][0], 0);
	while (i < vars->tok[vars->p.child].nb_input)
	{
		if (vars->tok[vars->p.child].in[i] == IN_HEREDOC)
			;
		else if (vars->tok[vars->p.child].in[i] == IN_REDIRECT)
			ft_infile_checking(vars, let_error);
		if (vars->tok[vars->p.child].in[i] == IN_HEREDOC
			|| vars->tok[vars->p.child].in[i] == IN_REDIRECT)
		{
			dup2(vars->tok[vars->p.child].fd_args[i][0], 0);
			close(vars->tok[vars->p.child].fd_args[i][0]);
		}
		i++;
	}
	ft_print_err_message(vars);
	if (*let_error != 1)
		ft_bzero(vars->p.error[vars->p.child], 100);
	ft_processing_output(vars);
}

void	ft_close_fds(t_prgm *vars)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct - 1)
	{
		close(vars->p.fd[i][0]);
		close(vars->p.fd[i][1]);
		i++;
	}
}
