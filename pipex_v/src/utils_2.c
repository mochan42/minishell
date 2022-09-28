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
//#include "../inc/pipex.h"

 /* must be analysed again*/
void	ft_init_pipe(t_prgm *vars)
{
	vars->p.child = 0;
	//vars->p->env = ft_env_to_local_env(vars->env);
}

void	free_vars(t_prgm *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->p.nb_cmd)
	{
		j = 0;
		while (vars->tokens[i].options[j])
		{
			free(vars->tokens[i].options[j]);
			j++;
		}
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

// must be analysed deeply
void	ft_parse_all(t_prgm *vars, char **pt)
{
	int	i;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		vars->tokens[i].options = ft_split(vars->tokens[i].t_str, ' ');
		ft_parse(vars, pt, i);
		i++;
	}
}
