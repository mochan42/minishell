/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:54:54 by fakouyat          #+#    #+#             */
/*   Updated: 2022/10/01 13:54:54 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_t_env_to_array(t_env *envp, char ***env_ord)
{
	int	i;

	i = 0;
	while (envp)
	{
		env_ord[i] = malloc(sizeof(char *) * 2);
		env_ord[i][0] = envp->key;
		env_ord[i][1] = envp->value;
		envp = envp->next;
		i++;
	}
}

void	ft_sorting_env(char ***env_ord, int env_size)
{
	int		i;
	int		j;
	char	**tmp_env;

	i = 0;
	while (i < env_size - 1)
	{
		j = i + 1;
		while (j < env_size)
		{
			if (ft_strcmp(env_ord[i][0], env_ord[j][0]) > 0)
			{
				tmp_env = env_ord[i];
				env_ord[i] = env_ord[j];
				env_ord[j] = tmp_env;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_exported_env(char ***env_ord, int env_size)
{
	int	i;

	i = 0;
	while (i < env_size)
	{
		if (env_ord[i][1])
			printf("declare -x %s=\"%s\"\n", env_ord[i][0], env_ord[i][1]);
		else
			printf("declare -x %s\n", env_ord[i][0]);	
		free(env_ord[i]);
		i++;
	}
	free(env_ord);
}

void	ft_export(t_prgm *vars)
{
	t_env	*envp;
	char	***env_ord;	
	int		env_size;	
	
	ft_export_new_key(vars);
	envp = vars->env_head;
	env_size = ft_list_size(envp);
	env_ord = (char ***)malloc(sizeof(char **) * env_size);
	ft_t_env_to_array(envp, env_ord);
	ft_sorting_env(env_ord, env_size);
	if (!vars->tokens[vars->p.child].options[1])
		ft_print_exported_env(env_ord, env_size);
}

// free everything here before existing

void	ft_exit(t_prgm *vars)
{
	static int	i;
	if (i == 0)
		printf("exit !\n");
	kill(0, SIGKILL);
	exit(0);
	i++;
	return ft_exit(vars);
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

	if (var)
	{
		env = vars->env_head;
		while (env)
		{
			if (env->next
				&& ft_strcmp((env->next)->key,
							var) == 0)
			{
				tmp = (env->next)->next;
				free(env->next);
				env->next = tmp;
				break ;
			}
			env = env->next;
		}
		return ;
	}
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
	else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "exit", 4) == 0)
		ft_exit(vars);
	else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "echo", 4) == 0)
		ft_echo(vars);
	exit(0);
}
