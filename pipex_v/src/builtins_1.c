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
}

void	ft_env(t_prgm *vars)
{
	printlist(vars->env_head);
}

void	execbuilt_in(t_prgm *vars)
{
	if (ft_strcmp(vars->tokens[vars->p.child].options[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(vars->tokens[vars->p.child].options[0], "env") == 0)
		ft_env(vars);
	else if (
		ft_strcmp(vars->tokens[vars->p.child].options[0], "export") == 0
	)
		ft_export(vars);
	else if (ft_strcmp(vars->tokens[vars->p.child].options[0], "echo") == 0)
		ft_echo(vars);
	ft_exit_code(0, 1);
	exit(0);
}

void	ft_exit(t_prgm *vars)
{
	// static int	i;

	// if (i == 0)
	(void)vars;
	printf("exit\n");
	// if (vars->p.child == 0)
	// kill(vars->p.child, SIGKILL);
	kill(vars->p.child, SIGTERM);
	exit(0);
	// i++;
	// return (ft_exit(vars));
}
