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

void	ft_exit(t_prgm *vars)
{
	int	i = 1;
	while (vars->tokens[vars->p.child].options[i])
	{
		int	j = 0;
		if (i > 1)
		{
			printf("too many arguments\n");
			ft_exit_code(1, 1);
			return ;
		}
		while (vars->tokens[vars->p.child].options[i][j])
		{
			if (!(vars->tokens[vars->p.child].options[i][j] >= '0'
				&& vars->tokens[vars->p.child].options[i][j] <= '9'))
			{
				printf("numeric argument required : %s\n", vars->tokens[vars->p.child].options[i]);
				ft_exit_code(255, 1);
				return ;
			}
			j++;
		}
		i++;
	}
	vars->exit = 1;
	printf("Exit, BYE!!!!!!\n");
}
