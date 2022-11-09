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
}

int	is_numeric(char c)
{
	if (!(c >= '0' && c <= '9') && c != '-')
		return (1);
	return (0);
}

int	ft_assert_numeric(t_prgm *vars, int indice)
{
	int	j;

	j = 0;
	while (vars->tokens[vars->p.child].options[indice][j])
	{
		if (is_numeric(
				vars->tokens[vars->p.child].options[indice][j]) == 1)
		{
			printf("numeric argument required : %s\n",
				vars->tokens[vars->p.child].options[indice]);
			ft_exit_code(255, 1);
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_check_ex_options(t_prgm *vars)
{
	int	i;

	i = 1;
	while (vars->tokens[vars->p.child].options[i])
	{
		if (i > 1)
		{
			printf("too many arguments\n");
			ft_exit_code(1, 1);
			return (1);
		}
		if (ft_assert_numeric(vars, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_prgm *vars)
{
	int	i;

	i = 1;
	if (vars->pipe_ct > 0)
		return ;
	if (ft_check_ex_options(vars) == 1)
		return ;
	if (vars->tokens[vars->p.child].options[i])
		ft_exit_code(ft_atoi(vars->tokens[vars->p.child].options[i]), 1);
	vars->exit = 1;
	printf("Exit, BYE!!!!!!\n");
}

void	ft_exit_shell(t_prgm *vars)
{
	vars->exit = 1;
	printf("Exit, BYE!!!!!!\n");
}
