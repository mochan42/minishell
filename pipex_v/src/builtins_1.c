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

int	ft_strcmp(const char *s1, const char *s2)
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

void	ft_export_new_key(t_prgm *vars)
{
	int		i;
	t_env	*new_ev;
	char	*delim;

	i = 0;
	while (vars->tokens[vars->p.child].options[1 + i])
	{
		delim = ft_strchr(vars->tokens[vars->p.child].options[1 + i], '=');
		if (delim)
		{
			new_ev = new_node(
					ft_substr(vars->tokens[vars->p.child].options[1 + i],
						0, delim - vars->tokens[vars->p.child].options[1 + i]
						));
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
}
