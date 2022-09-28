/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:03:24 by mochan            #+#    #+#             */
/*   Updated: 2022/09/28 02:25:04 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../minishell.h"
#include "../inc/parser.h"

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

void	parsing_pipes(t_prgm *vars)
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
	if (vars->pipe_ct > 0)
	{
		tab_token = ft_split(vars->cmd_line, '|');
		vars->tokens = malloc(sizeof(t_token) * (vars->pipe_ct + 1));
		
		i = 0;
		while (i < vars->pipe_ct + 1)
		{
			vars->tokens[i].t_str = tab_token[i];
			i++;
		}
	}
	else if (vars->pipe_ct == 0)
	{
		i = 0;
		// one_token = ft_split(vars->cmd_line, ' ');
		vars->tokens = malloc(sizeof(t_token) * 1);
		vars->tokens[i].t_str = vars->cmd_line;
		// free(one_token);
	}
	init_all_tokens(vars);
}

void	parsing_in_redir_heredoc(t_prgm *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		j = 0;
		while(vars->tokens[i].t_str[j] != '\0')
			j++;
		while (j != -1)
		{
			if (j > 0 && vars->tokens[i].t_str[j] == '<' && vars->tokens[i].t_str[j-1] == '<')
			{
				vars->tokens[i].in = "<<";
				break;
			}
			else if (vars->tokens[i].t_str[j] == '<')
			{
				vars->tokens[i].in = "<";
				break;
			}
			j--;
		}
		i++;
	}
}

void	parsing_out_redir_heredoc(t_prgm *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		j = 0;
		while (vars->tokens[i].t_str[j] != '\0')
		{
			if (vars->tokens[i].t_str[j+1] != '\0' && vars->tokens[i].t_str[j] == '>' && vars->tokens[i].t_str[j+1] == '>')
			{
				vars->tokens[i].out = ">>";
				break;
			}
			else if (vars->tokens[i].t_str[j] == '>')
			{
				vars->tokens[i].out = ">";
				break;
			}
			j++;
		}
		i++;
	}
}

void	parsing(t_prgm *vars)
{
	parsing_pipes(vars);
	parsing_in_redir_heredoc(vars);
	parsing_out_redir_heredoc(vars);
}
