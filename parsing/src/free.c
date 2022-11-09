/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:01:27 by mochan            #+#    #+#             */
/*   Updated: 2022/11/09 23:44:47 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		exit (1);
	while (table[i] != NULL)
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void	re_init_tokens(t_prgm *vars)
{
	int	i;

	i = 0;
	if (vars->pipe_ct > 0)
	{
		while (i < vars->pipe_ct + 1)
		{
			free(vars->tokens[i].t_str);
			vars->tokens[i].t_str = NULL;
			i++;
		}
	}
	else
	{
		free(vars->tokens[i].t_str);
		vars->tokens[i].t_str = NULL;
	}
	vars->pipe_ct = 0;
}

void	free_stuff(t_prgm *vars)
{
	free(vars->tokens);
	free(vars);
}
