/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:03:24 by mochan            #+#    #+#             */
/*   Updated: 2022/10/01 17:52:39 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	splitting_pipes(t_prgm *vars)
{
	int		i;
	// char	**one_token;
	char	**tab_token;
	char	*pipes_loc;

	i = 0;
	pipes_loc = find_pipes(vars->cmd_line);
	while (pipes_loc[i] != '\0')
	{
		if (pipes_loc[i] == 'P')
			vars->pipe_ct++;
		i++;
	}
	printf("vars->pipe_ct = %d\n", vars->pipe_ct);
	if (vars->pipe_ct > 0)
	{
		tab_token = ft_split_pipes(vars->cmd_line, 'P');
		vars->tokens = malloc(sizeof(t_token) * (vars->pipe_ct + 1));
		
		i = 0;
		while (i < vars->pipe_ct + 1)
		{
			vars->tokens[i].t_str = tab_token[i];
			printf("token %d :%s\n", i, vars->tokens[i].t_str);
			i++;
		}
	}
	else if (vars->pipe_ct == 0)
	{
		i = 0;
		// one_token = ft_split(vars->cmd_line, ' ');
		vars->tokens = malloc(sizeof(t_token) * 1);
		vars->tokens[i].t_str = vars->cmd_line;
		printf("token %d :%s\n", i, vars->tokens[i].t_str);
		// free(one_token);
	}
	init_all_tokens(vars);
}

// void	split_in_redir_heredoc(t_prgm *vars)
// {
// 	int		i;
// 	int		j;
// 	char	***in_redir_heredoc_tab;
	
// 	in_redir_heredoc_tab = malloc(sizeof(char *) * (vars->pipe_ct + 1));
// 	i = 0;
// 	while (i < vars->pipe_ct + 1)
// 	{
// 		printf("i = %d \n", i);
// 		if (vars->tokens[i].in != NULL && ft_strlen(vars->tokens[i].in) == 1)
// 		{
// 			in_redir_heredoc_tab[i] = ft_split(vars->tokens[i].t_str, '<');
// 			printf("\t< found\n");
// 		}

// 		else if (vars->tokens[i].in != NULL && ft_strlen(vars->tokens[i].in) == 2)
// 		{
// 			in_redir_heredoc_tab[i] = ft_split_2(vars->tokens[i].t_str, "<<");
// 			printf("\t<< found\n");
// 		}
// 		else
// 			in_redir_heredoc_tab[i] = &vars->tokens[i].t_str;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < vars->pipe_ct + 1)
// 	{
// 		j = 0;
// 		while (in_redir_heredoc_tab[i][j] != NULL)
// 		{
// 			printf("%s\n", in_redir_heredoc_tab[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	parsing(t_prgm *vars)
{
	splitting_pipes(vars);
	// split_in_redir_heredoc(vars); // we will not split by redirection, heredoc
	// printlist(vars->env_head); // just for debugging purposes
	find_infile(vars);
	find_outfile(vars);
	find_cmd_opt_arg(vars);
}
