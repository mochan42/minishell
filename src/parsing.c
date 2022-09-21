/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:03:24 by mochan            #+#    #+#             */
/*   Updated: 2022/09/21 21:19:42 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char	**parse_for_pipe(t_prgm *vars)
// {
// 	char	**tab;

// 	tab = ft_split(vars->cmd_line, '|');
// 	return (tab);
// }

// char	**parse_for_space(t_prgm *vars)
// {
// 	char	**tab;

// 	tab = ft_split(vars->cmd_line, ' ');
// 	return (tab);
// }

void	parsing_lvl1(t_prgm *vars)
{
	int		i;
	// char	**one_token;
	char	**tab_token;

	i = 0;
	while (vars->cmd_line[i] != '\0')
	{
		if (vars->cmd_line[i] == '|')
			vars->pipe_ct += 1;
		i++;
	}
	printf("pipe_ct = %d\n", vars->pipe_ct);
	if (vars->pipe_ct > 0)
	{
		tab_token = ft_split(vars->cmd_line, '|');
		vars->array_tokens = malloc(sizeof(t_token) * (vars->pipe_ct + 1));
		
		i = 0;
		while (i < vars->pipe_ct + 1)
		{
			vars->array_tokens[i].token_str = tab_token[i];
			printf("token %d :%s\n", i, vars->array_tokens[i].token_str);
			i++;
		}
	}
	else if (vars->pipe_ct == 0)
	{
		i = 0;
		// one_token = ft_split(vars->cmd_line, ' ');
		vars->array_tokens = malloc(sizeof(t_token) * 1);
		vars->array_tokens[i].token_str = vars->cmd_line;
		printf("token %d :%s\n", i, vars->array_tokens[i].token_str);
		// free(one_token);
	}
}

void	parsing(t_prgm *vars)
{
	parsing_lvl1(vars);
}
