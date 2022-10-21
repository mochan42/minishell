/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:41:28 by mochan            #+#    #+#             */
/*   Updated: 2022/10/21 23:21:00 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	find_outfile(t_prgm *vars)
{
	int		i;
	int		j;
	char	*ptr_outfile;
	int		start;
	int		len_word;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		j = 0;
		start = 0;
		len_word = 0;
		ptr_outfile = vars->tokens[i].t_str;
		while (vars->tokens[i].t_str[j] != '\0')
		{
			j++;
			ptr_outfile++;
		}
		while (j != -1)
		{
			if (j > 0 && vars->tokens[i].t_str[j] == '>' && vars->tokens[i].t_str[j - 1] == '>')
			{
				vars->tokens[i].out = ">>";
				j++;
				ptr_outfile++;
				break ;
			}
			else if (vars->tokens[i].t_str[j] == '>')
			{
				vars->tokens[i].out = ">";
				j++;
				ptr_outfile++;
				break ;
			}
			else
			{
				j--;
				ptr_outfile--;
			}
		}
		if (vars->tokens[i].out != NULL && ft_strncmp(vars->tokens[i].out, ">>", 2) == 0)
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
			vars->tokens[i].outfile = ft_substr(ptr_outfile, start, len_word);
			printf("output type[%d]= %s\n", i, vars->tokens[i].out);
			printf("outfile[%d]=%s\n", i, vars->tokens[i].outfile);
		}
		else if (vars->tokens[i].out != NULL && ft_strncmp(vars->tokens[i].out, ">", 1) == 0)
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
			vars->tokens[i].outfile = ft_substr(ptr_outfile, start, len_word);
			printf("output type[%d]= %s\n", i, vars->tokens[i].out);
			printf("outfile[%d]=%s\n", i, vars->tokens[i].outfile);
		}
		i++;
	}
}
