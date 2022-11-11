/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:01:27 by mochan            #+#    #+#             */
/*   Updated: 2022/11/11 15:56:40 by fakouyat         ###   ########.fr       */
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
		while (i < vars->pipe_ct)
		{
			free(vars->tokens[i].t_str);
			vars->tokens[i].t_str = NULL;
			i++;
		}
	}
	vars->pipe_ct = 0;
	vars->tok_error = 0;
}

void	free_stuff(t_prgm *vars)
{
	free(vars->tokens);
	free(vars);
}
