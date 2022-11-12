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
	if (!vars->tok[vars->p.child].options[1])
		ft_print_exported_env(env_ord, env_size);
}
