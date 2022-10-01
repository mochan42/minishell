/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_opt_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:26:25 by mochan            #+#    #+#             */
/*   Updated: 2022/10/01 18:49:09 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
void	find_cmd_opt_arg(t_prgm *vars)
{
	int		i;
	int		j;
	char*	ptr_coa;
	int		start_coa;
	int		len_coa;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		j = 0;
		ptr_coa = vars->tokens[i].t_str;
		while(vars->tokens[i].t_str[j] != '\0')
		{
			j++;
			ptr_coa++;
		}
		while (j != -1)
		{
			if (j > 0 && vars->tokens[i].t_str[j] == '<' && vars->tokens[i].t_str[j-1] == '<')
			{
				vars->tokens[i].in = "<<";
				j++;
				ptr_coa++;
				break;
			}
			else if (vars->tokens[i].t_str[j] == '<')
			{
				vars->tokens[i].in = "<";
				j++;
				ptr_coa++;
				break;
			}
			else
			{
				j--;
				ptr_coa--;
			}
		}
		if ((vars->tokens[i].in != NULL && ft_strncmp(vars->tokens[i].in, "<<", 2) == 0) ||\
		(vars->tokens[i].in != NULL && ft_strncmp(vars->tokens[i].in, "<", 1) == 0))
		{
			while (vars->tokens[i].t_str[j] == ' ' || vars->tokens[i].t_str[j] == '\t') // jump whitespaces
			{
				j++;
				ptr_coa++;
			}
			printf("vars->tokens[%d].t_str[%d] :%c\n", i, j, vars->tokens[i].t_str[j]);
			while ((vars->tokens[i].t_str[j] != ' ' && vars->tokens[i].t_str[j] != '\0')) // jump infile
			{
				j++;
				ptr_coa++;
			}
			printf("vars->tokens[%d].t_str[%d] :%c\n", i, j, vars->tokens[i].t_str[j]);
			while (vars->tokens[i].t_str[j] == ' ' || vars->tokens[i].t_str[j] == '\t') // jump whitespaces
			{
				j++;
				ptr_coa++;
			}
			// printf("vars->tokens[%d].t_str[%d] :%c\n", i, j, vars->tokens[i].t_str[j]); // just for debug purposes
			// printf("vars->tokens[%d].t_str[%d] :%c\n", i, j+1, vars->tokens[i].t_str[j+1]); // just for debug purposes
			if ((j > 0 && vars->tokens[i].t_str[j] == '>' && vars->tokens[i].t_str[j-1] == '>') || \
				(vars->tokens[i].t_str[j] == '>'))
			{
				printf("case B : cmd opt arg at the start\n");
				ptr_coa = vars->tokens[i].t_str;
				while (ptr_coa[j] == ' ' || ptr_coa[j] == '\t') // jump whitespaces
				{
					j++;
					ptr_coa++;
				}
				start_coa = 0;
				len_coa = 0;
				printf("ptr_coa :%s\n", ptr_coa);
				printf("init start_coa :%d\n", start_coa);
				printf("init len_coa :%d\n", len_coa);
				while ((ptr_coa[j] != '<' && ptr_coa[j] != '\0')) // jump command arg option
				{
					j++;
					len_coa++;
				}
				j -= 2;
				len_coa -= 2;
				printf("end ptr_coa :%s\n", ptr_coa);
				printf("end start_coa :%d\n", start_coa);
				printf("end len_coa :%d\n", len_coa);
				vars->tokens[i].cmd = ft_substr(ptr_coa, start_coa, len_coa);
				printf("vars->tokens[%d].cmd :%s\n", i, vars->tokens[i].cmd);
			}
			else
			{
				printf("case A : cmd opt arg in the middle\n");
				printf("ptr_coa :%s\n", ptr_coa);
			}
		}
		i++;
	}
}
