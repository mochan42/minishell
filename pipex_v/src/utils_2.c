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

void	ft_init_pipe(t_prgm *vars)
{
	vars->p.child = 0;
}

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

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		vars->tokens[i].options = ft_split(vars->tokens[i].cmd, ' ');
		ft_parse(vars, pt, i);
		i++;
	}
}
