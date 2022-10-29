/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:25:01 by fakouyat          #+#    #+#             */
/*   Updated: 2022/10/29 13:25:01 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		if (ft_strcmp(vars->tokens[vars->p.child].options[1 + i], "??") == 0)
			ft_exit_code(0, 0);
		else
			printf("%s", vars->tokens[vars->p.child].options[1 + i]);
		i++;
		if (vars->tokens[vars->p.child].options[1 + i])
			printf(" ");
	}
	printf("%c", end);
}

void	ft_unset(t_prgm *vars, char *var)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	if (ft_unset_single_var(vars, var) == 1)
		return ;
	i = 1;
	while (vars->tokens[vars->p.child].options[i])
	{
		env = vars->env_head;
		while (env)
		{
			if (env->next
				&& ft_strcmp((env->next)->key,
					vars->tokens[vars->p.child].options[i]) == 0)
			{
				tmp = (env->next)->next;
				free(env->next);
				env->next = tmp;
				break ;
			}
			env = env->next;
		}
		i++;
	}
}

int	ft_unset_single_var(t_prgm *vars, char *var)
{
	t_env	*env;
	t_env	*tmp;

	if (var)
	{
		env = vars->env_head;
		while (env)
		{
			if (env->next && ft_strcmp((env->next)->key, var) == 0)
			{
				tmp = (env->next)->next;
				free(env->next);
				env->next = tmp;
				break ;
			}
			env = env->next;
		}
		return (1);
	}
	return (0);
}
