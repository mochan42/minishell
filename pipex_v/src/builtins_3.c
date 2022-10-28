/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:27:35 by fakouyat          #+#    #+#             */
/*   Updated: 2022/10/24 13:27:35 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// free everything here before existing

void	ft_exit(t_prgm *vars)
{
	(void)vars;
	printf("exit !\n");
	exit(0);
}

void	ft_echo(t_prgm *vars)
{
	int		i;
	char	end;

	end = '\n';
	if (vars->tokens[vars->p.child].options[1]
		&& ft_strcmp(vars->tokens[vars->p.child].options[1], "-n") == 0)
	{
		i = 1;
		end = '\0';
	}
	else
		i = 0;
	while (vars->tokens[vars->p.child].options[1 + i])
	{
		if (ft_strcmp(vars->tokens[vars->p.child].options[1 + i], "$?") == 0)
			ft_exit_code(0, 0);
		else
			printf("%s", vars->tokens[vars->p.child].options[1 + i]);
		i++;
	}
	printf("%c", end);
}

// void	ft_unset(t_prgm *vars, vars)
// {
// 	t_env	*env;
// 	t_env	*tmp;

// 	env = vars->env_head;
// 	if (vars->tokens[vars->p.child].options[1])
// 	{
// 		while (env)
// 		{
// 			if (env->next
// 				&& ft_strcmp((env->next)->key,
// 					vars->tokens[vars->p.child].options[1]) == 0)
// 			{
// 				tmp = (env->next)->next;
// 				free(env->next);
// 				env->next = tmp;
// 				break ;
// 			}
// 			env = env->next;
// 		}
// 	}
// }

void	execbuilt_in(t_prgm *vars)
{
	if (ft_strncmp(vars->tokens[vars->p.child].options[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "env", 3) == 0)
		ft_env(vars);
	else if (
		ft_strncmp(vars->tokens[vars->p.child].options[0], "export", 6) == 0
	)
		ft_export(vars);
	else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "echo", 4) == 0)
		ft_echo(vars);
	exit(0);
}
