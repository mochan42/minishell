/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:27:23 by mochan            #+#    #+#             */
/*   Updated: 2022/09/30 17:39:20 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../minishell.h"
#include "../inc/parser.h"

void	find_infile(t_prgm *vars)
{
	int		i;
	int		j;
	char*	ptr_infile;
	int		start;
	int		len_word;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		j = 0;
		start = 0;
		len_word = 0;
		ptr_infile = vars->tokens[i].t_str;
		while(vars->tokens[i].t_str[j] != '\0')
		{
			j++;
			ptr_infile++;
		}
		while (j != -1)
		{
			if (j > 0 && vars->tokens[i].t_str[j] == '<' && vars->tokens[i].t_str[j-1] == '<')
			{
				vars->tokens[i].in = "<<";
				j++;
				ptr_infile++;
				break;
			}
			else if (vars->tokens[i].t_str[j] == '<')
			{
				vars->tokens[i].in = "<";
				j++;
				ptr_infile++;
				break;
			}
			else
			{
				j--;
				ptr_infile--;
			}
		}
		if (ft_strncmp(vars->tokens[i].in, "<<", 2) == 0)
		{
			while (vars->tokens[i].t_str[j] == ' ' || vars->tokens[i].t_str[j] == '\t')
			{
				j++;
				start++;
			}
			while ((vars->tokens[i].t_str[j] != ' ' && vars->tokens[i].t_str[j] != '\0'))
			{
				j++;
				len_word++;
			}
			vars->tokens[i].infile = ft_substr(ptr_infile, start, len_word);
			printf("input type[%d]= %s\n", i, vars->tokens[i].in);
			printf("infile[%d]=%s\n", i, vars->tokens[i].infile);
		}
		else if (ft_strncmp(vars->tokens[i].in, "<", 1) == 0)
		{
			while (vars->tokens[i].t_str[j] == ' ' || vars->tokens[i].t_str[j] == '\t')
			{
				j++;
				start++;
			}
			while ((vars->tokens[i].t_str[j] != ' ' && vars->tokens[i].t_str[j] != '\0'))
			{
				j++;
				len_word++;
			}
			printf("input type[%d]= %s\n", i, vars->tokens[i].in);
			vars->tokens[i].infile = ft_substr(ptr_infile, start, len_word);
			printf("infile[%d]=%s\n", i, vars->tokens[i].infile);
		}
		i++;
	}
}
