/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 02:26:56 by fakouyat          #+#    #+#             */
/*   Updated: 2022/10/29 02:26:56 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (s1 - s2);
	while (s1[i] != 0 && s2[i] != 0)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

t_env	*ft_creat_var_node(char *delim, t_prgm *vars, int i, int curr)
{
	t_env	*node;

	node = new_node(ft_substr(vars->tok[curr].opts[i],
				0, delim - vars->tok[curr].opts[i]));
	if (delim + 1)
		node->value = ft_strdup(delim + 1);
	else
		node->value = ft_strdup("");
	return (node);
}

void	ft_export_new_key(t_prgm *vars)
{
	int		i;
	t_env	*new_ev;
	char	*delim;
	char	*value;
	int		curr;

	i = 1;
	curr = vars->p.child;
	while (vars->tok[curr].opts[i])
	{
		delim = ft_strchr(vars->tok[curr].opts[i], '=');
		if (delim)
			new_ev = ft_creat_var_node(delim, vars, i, curr);
		else
			new_ev = new_node(ft_strdup(vars->tok[curr].opts[i]));
		value = get_our_env(vars, new_ev->key);
		if (value && !new_ev->value)
			new_ev->value = ft_strdup(value);
		if (value != NULL)
			free(value);
		ft_unset(vars, new_ev->key);
		node_add_back(&vars->env_head, new_ev);
		i++;
	}
}
