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
	if (vars->tok[vars->p.child].options[1]
		&& ft_strcmp(vars->tok[vars->p.child].options[1], "-n") == 0)
	{
		i = 1;
		end = '\0';
	}
	else
		i = 0;
	while (vars->tok[vars->p.child].options[1 + i])
	{
		printf("%s", vars->tok[vars->p.child].options[1 + i]);
		i++;
		if (vars->tok[vars->p.child].options[1 + i])
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
	while (vars->tok[vars->p.child].options[i])
	{
		env = vars->env_head;
		while (env)
		{
			if (env->next
				&& ft_strcmp((env->next)->key,
					vars->tok[vars->p.child].options[i]) == 0)
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

void	ft_only_file_out(t_prgm *vars, int i)
{
	int	ct_red;

	ct_red = 0;
	while (vars->tok[i].outfile[ct_red] != NULL)
	{
		if (vars->tok[i].out[ct_red] == OUT_REDIRECT
			&& access(vars->tok[i].outfile[ct_red], F_OK) == 0)
		{
			unlink(vars->tok[i].outfile[ct_red]);
			open(vars->tok[i].outfile[ct_red], O_RDWR | O_CREAT, 0666);
		}
		ct_red++;
		vars->tok_error += 1;
	}
	g_exit_code = 0;
}
