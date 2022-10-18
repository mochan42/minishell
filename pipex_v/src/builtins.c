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

/* find the appropriate command, then execut it
* cd, echo, export, unset, pwd, env, exit
*/
static char	*get_our_env(t_prgm *vars)
{
	t_env	*envp;

	envp = vars->env_head;
	while (envp)
	{
		 if (ft_strncmp(envp->key, "PWD",3) == 0)
		 	return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

int	is_our_env_path(t_prgm *vars)
{
	t_env	*envp;

	envp = vars->env_head;
	while (envp)
	{
		 if (ft_strncmp(envp->key, "PATH", 4) == 0)
		 	return (1);
		envp = envp->next;
	}
	return (0);
}

void	ft_cd(t_prgm *vars)
{
	char *oldpwd;
	t_env *envp;
	char repo[MAX_LEN_DIR];
	int flag;

	flag = 0;
	envp = vars->env_head;
	oldpwd = get_our_env(vars);
	if (!vars->tokens[vars->p.child].options[1] || *vars->tokens[vars->p.child].options[1] == '~')
		chdir(getenv("HOME"));
	else
		chdir(vars->tokens[vars->p.child].options[1]);
	while (envp)
	{
		if (ft_strncmp(envp->key, "OLDPWD", 6) == 0)
		{
			envp->value = ft_strdup(oldpwd);
			flag += 1;
		}
		else if (ft_strncmp(envp->key, "PWD",3) == 0)
		{
			ft_bzero(repo, MAX_LEN_DIR);
			envp->value = ft_strdup(getcwd(repo, MAX_LEN_DIR));
			flag += 1;
		}
		if (flag == 2)
			return ;
		envp = envp->next;
	}

}

void	ft_pwd()
{
	char repo[MAX_LEN_DIR];
	
    printf("\033[0;34m%s:\n", getcwd(repo, MAX_LEN_DIR));
    printf("\033[0;37m");
}

void	ft_env(t_prgm *vars)
{
	printlist(vars->env_head);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != 0 && s2[i] != 0)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

void	ft_export(t_prgm *vars)
{
	t_env	*envp;
	t_env	*new_ev;
	char	***env_ord;	
	char	**tmp_env;
	int		env_size;	
	int		i;
	int		j;
	char	*delim;

	i = 0;
	while (vars->tokens[vars->p.child].options[1 + i])
	{
		delim = ft_strchr(vars->tokens[vars->p.child].options[1 + i], '=');
		if (delim)
		{
			new_ev = new_node(ft_substr(vars->tokens[vars->p.child].options[1 + i], 0, delim - vars->tokens[vars->p.child].options[1 + i]));
			if (delim + 1)
				new_ev->value = ft_strdup(delim + 1);
			else
				new_ev->value = "";
		}
		else
			new_ev = new_node(vars->tokens[vars->p.child].options[1 + i]);
		node_add_back(&vars->env_head, new_ev);
		i++;
	}
	envp = vars->env_head;
	env_size = ft_list_size(envp);
	env_ord = (char ***)malloc(sizeof(char **) * env_size);
	i = 0;
	// transform to array
	while (envp)
	{
		env_ord[i] = malloc(sizeof(char *) * 2);
		env_ord[i][0] = envp->key;
		env_ord[i][1] = envp->value;
		envp = envp->next;
		i++;
	}
	i = 0;
	//sorting
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
	i = 0;
	// print
	if (!vars->tokens[vars->p.child].options[1])
	{
		while (i < env_size)
		{
			if(env_ord[i][1])
				printf("declare -x %s=\"%s\"\n",env_ord[i][0], env_ord[i][1]);
			else
				printf("declare -x %s\n",env_ord[i][0]);	
			i++;
		}
	}
}

void	ft_exit(t_prgm *vars)
{
	(void)vars;
	printf("exit !\n");
	exit(0);
}

void	ft_echo(t_prgm *vars)
{
	int i;
	char end;

	end = '\n';
	if (vars->tokens[vars->p.child].options[1] && ft_strcmp(vars->tokens[vars->p.child].options[1], "-n") == 0)
	{
		i = 1;
		end = '\0';
	}
	else
		i = 0;
	while (vars->tokens[vars->p.child].options[1 + i])
	{
		printf("%s", vars->tokens[vars->p.child].options[1 + i]);
		i++;
	}
	printf("%c", end);
}

void	ft_unset(t_prgm *vars)
{
	t_env *env;
	t_env *tmp;
	env = vars->env_head;
	if (vars->tokens[vars->p.child].options[1])
	{
		while (env)
		{
			if (env->next && ft_strcmp((env->next)->key, vars->tokens[vars->p.child].options[1]) == 0)
			{
				tmp = (env->next)->next;
				free(env->next);
				env->next = tmp;
				break;
			}
			env = env->next;
		}
	}
}

void	execbuilt_in(t_prgm *vars)
{
    if (ft_strncmp(vars->tokens[vars->p.child].options[0], "pwd", 3) == 0)
        ft_pwd();
	else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "env", 3) == 0)
		ft_env(vars);
	else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "export", 6) == 0)
		ft_export(vars);
	else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "exit", 4) == 0)
		ft_exit(vars);
	else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "echo", 4) == 0)
		ft_echo(vars);
	exit(0);
}

