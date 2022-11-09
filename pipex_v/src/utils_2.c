/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 04:37:57 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/21 04:37:57 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_vars_p(t_prgm *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		j = 0;
		while (vars->tokens[i].options[j])
		{
			free(vars->tokens[i].options[j]);
			j++;
		}
		if (vars->tokens[i].bin)
			free(vars->tokens[i].bin);
		free(vars->tokens[i].options);
		i++;
	}
}

int	len_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		i++;
	}
	return (i);
}

void	ft_parse_all(t_prgm *vars, char **pt)
{
	int	i;
	int	j;
	int	z;
	char *tmp;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		z = 0;
		vars->tokens[i].options = ft_split_cmd(vars->tokens[i].cmd, ' ');
		if (vars->tokens[i].options[z] == NULL)
		{
			vars->tok_error = 1;
			return ;
		}
		while (vars->tokens[i].options[z])
		{
			tmp = trim_quotes(vars->tokens[i].options[z]);
			free(vars->tokens[i].options[z]);
			vars->tokens[i].options[z] = ft_strdup(tmp);
			free(tmp);
			z++;
		}
		j = 0;
		while (j < 7)
		{
			if (ft_strcmp(vars->tokens[i].options[0], vars->builts[j]) == 0)
			{
				vars->tokens[i].built_in = 1;
				break ;
			}
			j++;
		}
		ft_parse(vars, pt, i);
		i++;
	}
}
