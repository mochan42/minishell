/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_opt_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:26:25 by mochan            #+#    #+#             */
/*   Updated: 2022/10/14 10:37:29 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"
void	find_cmd_opt_arg(t_prgm *vars)
{
	int		i;
	int		j;
	int		z; // for interating builtin -checkin
	char*	ptr_coa;
	int		start_coa;
	int		len_coa;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		j = 0;
		ptr_coa = vars->tokens[i].t_str;
		// printf("vars->tokens[%d].t_str :%s\n", i, vars->tokens[0].t_str);
		// printf("ptr_coa :%s\n", ptr_coa);
		// printf("vars->tokens[%d].in: %s\n", i, vars->tokens[i].in);
		// printf("vars->tokens[%d].out: %s\n", i, vars->tokens[i].out);
		// exit (0);
		if (*vars->tokens[i].in != '\0' && *vars->tokens[i].out != '\0')
		{
			while(vars->tokens[i].t_str[j] != '\0') // go to the end of the cmd line string
			{
				j++;
				ptr_coa++; 
			}
			while (j != -1)
			{
				if (j > 0 && vars->tokens[i].t_str[j] == '<' && vars->tokens[i].t_str[j-1] == '<')  // look for infile here doc and jump it
				{
					vars->tokens[i].in = "<<";
					j++;
					ptr_coa++;
					break;
				}
				else if (vars->tokens[i].t_str[j] == '<') // look for infile redirection and jump it
				{
					vars->tokens[i].in = "<";
					j++;
					ptr_coa++;
					break;
				}
				else // continue to go to beginning of cmd line string while input redirection is not found.
				{
					j--;
					ptr_coa--;
				}
			}
			if ((vars->tokens[i].in != NULL && ft_strncmp(vars->tokens[i].in, "<<", 2) == 0) ||\
			(vars->tokens[i].in != NULL && ft_strncmp(vars->tokens[i].in, "<", 1) == 0)) // condition when input redirection is found
			{
				while (vars->tokens[i].t_str[j] == ' ' || vars->tokens[i].t_str[j] == '\t') // jump whitespaces
				{
					j++;
					ptr_coa++;
				}
				// printf("vars->tokens[%d].t_str[%d] :%c\n", i, j, vars->tokens[i].t_str[j]);
				while ((vars->tokens[i].t_str[j] != ' ' && vars->tokens[i].t_str[j] != '\0')) // jump infile
				{
					j++;
					ptr_coa++;
				}
				// printf("vars->tokens[%d].t_str[%d] :%c\n", i, j, vars->tokens[i].t_str[j]);
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
					// printf("case B : cmd opt arg at the start\n");
					ptr_coa = vars->tokens[i].t_str;
					while (ptr_coa[j] == ' ' || ptr_coa[j] == '\t') // jump whitespaces
					{
						j++;
						ptr_coa++;
					}
					start_coa = 0;
					len_coa = 0;
					j = 0;
					// printf("ptr_coa :%s\n", ptr_coa);
					// printf("init start_coa :%d\n", start_coa);
					// printf("init len_coa :%d\n", len_coa);
					while ((ptr_coa[j] != '<' && ptr_coa[j] != '\0')) // jump command arg option
					{
						j++;
						len_coa++;
					}
					// printf("j = %d\n", j);
					// printf("len_coa = %d\n", len_coa);
					// printf("end ptr_coa :%s\n", ptr_coa);
					// printf("end start_coa :%d\n", start_coa);
					// printf("end len_coa :%d\n", len_coa);
					vars->tokens[i].cmd = ft_substr(ptr_coa, start_coa, len_coa);
					printf("vars->tokens[%d].cmd :%s\n", i, vars->tokens[i].cmd);
					
				}
				else
				{
					// printf("case A : cmd opt arg in the middle\n");
					// printf("ptr_coa :%s\n", ptr_coa);
					start_coa = 0;
					len_coa = 0;
					j = 0;
					// printf("init j = %d\n", j);
					// printf("init start_coa :%d\n", start_coa);
					// printf("init len_coa :%d\n", len_coa);
					while ((ptr_coa[j] != '>' && ptr_coa[j] != '\0')) // jump command arg option
					{
						// printf("\tptr_coa[%d](avant incr.) : %c\n", j, ptr_coa[j]);
						j++;
						len_coa++;
					}
					j--;
					len_coa--;
					// printf("end j = %d\n", j);
					// printf("end ptr_coa :%s\n", ptr_coa);
					// printf("end start_coa :%d\n", start_coa);
					// printf("end len_coa :%d\n", len_coa);
					vars->tokens[i].cmd = ft_substr(ptr_coa, start_coa, len_coa + 1);
					printf("vars->tokens[%d].cmd :%s\n", i, vars->tokens[i].cmd);
				}
			}
		}
		else if (*vars->tokens[i].in != '\0' && *vars->tokens[i].out == '\0')
		{
			while(vars->tokens[i].t_str[j] != '\0') // go to the end of the cmd line string
			{
				j++;
				ptr_coa++; 
			}
			while (j != -1)
			{
				if (j > 0 && vars->tokens[i].t_str[j] == '<' && vars->tokens[i].t_str[j-1] == '<')  // look for infile here doc and jump it
				{
					vars->tokens[i].in = "<<";
					j++;
					ptr_coa++;
					break;
				}
				else if (vars->tokens[i].t_str[j] == '<') // look for infile redirection and jump it
				{
					vars->tokens[i].in = "<";
					j++;
					ptr_coa++;
					break;
				}
				else // continue to go to beginning of cmd line string while input redirection is not found.
				{
					j--;
					ptr_coa--;
				}
			}
			if ((vars->tokens[i].in != NULL && ft_strncmp(vars->tokens[i].in, "<<", 2) == 0) ||\
			(vars->tokens[i].in != NULL && ft_strncmp(vars->tokens[i].in, "<", 1) == 0)) // condition when input redirection is found
			{
				while (vars->tokens[i].t_str[j] == ' ' || vars->tokens[i].t_str[j] == '\t') // jump whitespaces
				{
					j++;
					ptr_coa++;
				}
				// printf("vars->tokens[%d].t_str[%d] :%c\n", i, j, vars->tokens[i].t_str[j]);
				while ((vars->tokens[i].t_str[j] != ' ' && vars->tokens[i].t_str[j] != '\0')) // jump infile
				{
					j++;
					ptr_coa++;
				}
				// printf("vars->tokens[%d].t_str[%d] :%c\n", i, j, vars->tokens[i].t_str[j]);
				while (vars->tokens[i].t_str[j] == ' ' || vars->tokens[i].t_str[j] == '\t') // jump whitespaces
				{
					j++;
					ptr_coa++;
				}
				vars->tokens[i].cmd = ft_substr(ptr_coa, 0, ft_strlen(ptr_coa));
				printf("vars->tokens[%d].cmd :%s\n", i, vars->tokens[i].cmd);
			}		
		}
		else if (*vars->tokens[i].in == '\0' && *vars->tokens[i].out != '\0')
		{
			int len_cmd;

			len_cmd = 0;
			while (vars->tokens[i].t_str[j] != '>')
			{
				j++;
				len_cmd++;
			}
			printf("vars->tokens[%d].t_str[%d] :%c\n", i, j, vars->tokens[i].t_str[j]);
			printf("len_cmd = %d\n", len_cmd);
			vars->tokens[i].cmd = ft_substr(ptr_coa, 0, len_cmd);
			printf("vars->tokens[%d].cmd :%s\n", i, vars->tokens[i].cmd);
		}
		else if (*vars->tokens[i].in == '\0' && *vars->tokens[i].out == '\0')
		{
			vars->tokens[i].cmd = ft_substr(ptr_coa, 0, ft_strlen(ptr_coa));
			printf("vars->tokens[%d].cmd :%s\n", i, vars->tokens[i].cmd);
		}
		z = 0;
		while (z < 7)
		{
			if (ft_strncmp(*(ft_split(vars->tokens[i].cmd, ' ')), vars->builts[z], ft_strlen(vars->builts[z])) == 0)
			{
				vars->tokens[i].built_in = 1;
				break;
			}
			z++;
		}
		i++;
	}
}
