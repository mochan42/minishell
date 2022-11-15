/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:22:13 by fakouyat          #+#    #+#             */
/*   Updated: 2022/10/24 13:22:13 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(void)
{
	char	repo[MAX_LEN_DIR];

	printf("\033[0;34m%s:\n", getcwd(repo, MAX_LEN_DIR));
	printf("\033[0;37m");
	ft_exit_code(0, 1);
}

void	ft_env(t_prgm *vars)
{
	printenv(vars->env_head);
	ft_exit_code(0, 1);
}

void	execbuilt_in(t_prgm *vars)
{
	if (ft_strcmp(vars->tok[vars->p.child].opts[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(vars->tok[vars->p.child].opts[0], "env") == 0)
		ft_env(vars);
	else if (
		ft_strcmp(vars->tok[vars->p.child].opts[0], "export") == 0
	)
		ft_export(vars);
	else if (ft_strcmp(vars->tok[vars->p.child].opts[0], "echo") == 0)
		ft_echo(vars);
	exit(0);
}

void	ft_exit(t_prgm *vars)
{
	int	i;

	i = 1;
	if (vars->pipe_ct > 1)
		return ;
	if (ft_check_ex_opts(vars) == 1)
		return ;
	if (vars->tok[vars->p.child].opts[i])
		ft_exit_code(ft_atoi(vars->tok[vars->p.child].opts[i]), 1);
	vars->exit = 1;
	printf("Exit, BYE!!!!!!\n");
}

void	ft_exit_shell(t_prgm *vars)
{
	vars->exit = 1;
	printf("Exit, BYE!!!!!!\n");
}
