/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:03:24 by mochan            #+#    #+#             */
/*   Updated: 2022/09/18 16:25:29 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**parse_space(t_prgm *vars)
{
	char **tab;

	tab = ft_split(vars->cmd_line, ' ');
	return (tab);
}

void	parsing(t_prgm *vars)
{
	int	i;

	i = 0;
	while (vars->cmd_line[i] != '\0')
	{
		if (vars->cmd_line[i] == '|')
		{
			vars->pipe_ct += 1;
		}
		i++;
	}
	if (vars->pipe_ct == 0)
	{
		char	**one_token;
		int	i;
		
		i = 0;
		one_token = parse_space(vars);
		while (one_token[i] != NULL)
		{
			printf("%s\n", one_token[i]);
			i++;
		}
		free(one_token);
	}
}
