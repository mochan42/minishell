/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:27:23 by mochan            #+#    #+#             */
/*   Updated: 2022/11/05 21:46:08 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// void	find_infile_identify_input_redirection_type(t_prgm *vars)
// {
// 	while (vars->j1 != -1)
// 	{
// 		if (vars->j1 > 0 && vars->tokens[vars->i1].t_str[vars->j1] == '<' && \
// 			vars->tokens[vars->i1].t_str[vars->j1 - 1] == '<')
// 		{
// 			vars->tokens[vars->i1].in = IN_HEREDOC;
// 			vars->j1++;
// 			vars->ptr_infile++;
// 			break ;
// 		}
// 		else if (vars->tokens[vars->i1].t_str[vars->j1] == '<')
// 		{
// 			vars->tokens[vars->i1].in = IN_REDIRECT;
// 			vars->j1++;
// 			vars->ptr_infile++;
// 			break ;
// 		}
// 		else
// 		{
// 			vars->j1--;
// 			vars->ptr_infile--;
// 		}
// 	}
// }

// void	find_infile_extract_heredoc_infile(t_prgm *vars)
// {
// 	while (vars->tokens[vars->i1].t_str[vars->j1] == ' ' || \
// 		vars->tokens[vars->i1].t_str[vars->j1] == '\t')
// 	{
// 		vars->j1++;
// 		vars->start_infile++;
// 	}
// 	while ((vars->tokens[vars->i1].t_str[vars->j1] != ' ' && \
// 		vars->tokens[vars->i1].t_str[vars->j1] != '\0'))
// 	{
// 		vars->j1++;
// 		vars->len_infile++;
// 	}
// 	vars->tokens[vars->i1].infile = ft_substr(vars->ptr_infile, \
// 		vars->start_infile, vars->len_infile);
// 	printf("input type[%d]= %d\n", vars->i1, vars->tokens[vars->j1].in);
// 	printf("infile[%d]=%s\n", vars->j1, vars->tokens[vars->j1].infile);
// }

// void	find_infile_extract_redirection_infile(t_prgm *vars)
// {
// 	while (vars->tokens[vars->i1].t_str[vars->j1] == ' ' || \
// 		vars->tokens[vars->i1].t_str[vars->j1] == '\t')
// 	{
// 		vars->j1++;
// 		vars->start_infile++;
// 	}
// 	while ((vars->tokens[vars->i1].t_str[vars->j1] != ' ' && \
// 		vars->tokens[vars->i1].t_str[vars->j1] != '\0'))
// 	{
// 		vars->j1++;
// 		vars->len_infile++;
// 	}
// 	printf("input type[%d]= %d\n", vars->i1, vars->tokens[vars->i1].in);
// 	vars->tokens[vars->i1].infile = ft_substr(vars->ptr_infile, \
// 		vars->start_infile, vars->len_infile);
// 	printf("infile[%d]=%s\n", vars->i1, vars->tokens[vars->i1].infile);
// }

// void	find_infile_extract_infile(t_prgm *vars)
// {
// 	if (vars->tokens[vars->i1].in != IN_STD && \
// 		vars->tokens[vars->i1].in == IN_HEREDOC)
// 		find_infile_extract_heredoc_infile(vars);
// 	else if (vars->tokens[vars->i1].in != IN_STD && \
// 		vars->tokens[vars->i1].in == IN_REDIRECT)
// 		find_infile_extract_redirection_infile(vars);
// }

int	count_input(t_prgm *vars)
{
	int	j;
	int	nb_input;

	j = 0;
	nb_input = 0;
	while(vars->tokens[vars->i1].t_str[j] != '\0')
	{
		if (vars->tokens[vars->i1].t_str[j] == '<')
			nb_input++;
		if (j > 0)
		{
			if (vars->tokens[vars->i1].t_str[j-1] == '<' && vars->tokens[vars->i1].t_str[j] == '<')
				nb_input--;
		}
		j++;
	}
	return(nb_input);
}

void	skip_white_spaces(t_prgm *vars, int *start, int cnt)
{
	while (vars->tokens[cnt].t_str[*start] != '\0' && (vars->tokens[cnt].t_str[*start] == ' ' || vars->tokens[cnt].t_str[*start] == '\t'))
	{
		*start += 1;
	}
}

void	subs_infile(t_prgm *vars, int *start, int index)
{
	int len_infile;
	int	j;
	
	len_infile = 0;
	j = *start;
	skip_white_spaces(vars, start, vars->i1);
	while (vars->tokens[vars->i1].t_str[j] != '\0' && (vars->tokens[vars->i1].t_str[j] != ' ' && vars->tokens[vars->i1].t_str[j] != '\t'))
	{
		len_infile++;
		j++;
	}
	vars->tokens[vars->i1].infile[index] = ft_substr(vars->tokens[vars->i1].t_str, *start, len_infile++);
	*start += len_infile - 1;
}

void	extract_infiles(t_prgm *vars)
{
	int	start;
	int	j;
	int	index;
	int	k;

	j = 0;
	index = 0;
	k = 0;
	vars->tokens[vars->i1].nb_input = count_input(vars);
	printf("nb of input =%d\n", vars->tokens[vars->i1].nb_input);
	if (vars->tokens[vars->i1].nb_input > 0)
	{
		vars->tokens[vars->i1].in = malloc(sizeof(int) * (vars->tokens[vars->i1].nb_input + 1));
		vars->tokens[vars->i1].infile = malloc(sizeof(char *) * (vars->tokens[vars->i1].nb_input + 1));
		vars->tokens[vars->i1].infile[vars->tokens[vars->i1].nb_input] = NULL;
	}
	while (vars->tokens[vars->i1].t_str[j] != '\0')
	{
		if (j > 0)
		{
			if (vars->tokens[vars->i1].t_str[j] == '<' && vars->tokens[vars->i1].t_str[j - 1] == '<')
			{
				start = j+1;
				vars->tokens[vars->i1].in[index] = IN_HEREDOC;
				printf("\tvars->tokens[%d].in[%d] =%d\n", vars->i1, index, vars->tokens[vars->i1].in[index]);
				skip_white_spaces(vars, &start, vars->i1);
				subs_infile(vars, &start, index);
				printf("\tvars->tokens[%d].infile[%d] :%s\n", vars->i1, index, vars->tokens[vars->i1].infile[index]);
				index++;
				j = start;
				vars->tokens[vars->i1].cmd[k++] = ' ';
				// printf("\t<< vars->tokens[%d].cmd :%s\n", vars->i1, vars->tokens[vars->i1].cmd);

			}
			else if (vars->tokens[vars->i1].t_str[j - 1] == '<')
			{
				start = j;
				vars->tokens[vars->i1].in[index] = IN_REDIRECT;
				printf("\tvars->tokens[%d].in[%d] =%d\n", vars->i1, index, vars->tokens[vars->i1].in[index]);
				skip_white_spaces(vars, &start, vars->i1);
				subs_infile(vars, &start, index);
				printf("\tvars->tokens[%d].infile[%d] :%s\n", vars->i1, index, vars->tokens[vars->i1].infile[index]);
				index++;
				j = start;
				vars->tokens[vars->i1].cmd[k++] = ' ';
				// printf("\t< vars->tokens[%d].cmd :%s\n", vars->i1, vars->tokens[vars->i1].cmd);
			}
			else
			{
				if (vars->tokens[vars->i1].t_str[j] != '<')
					vars->tokens[vars->i1].cmd[k++] = vars->tokens[vars->i1].t_str[j];
				// printf("\t 1 else vars->tokens[%d].t_str[%d]	:%c\n", vars->i1, j, vars->tokens[vars->i1].t_str[j]);
				j++;
			}
		}
		else
		{
			if (vars->tokens[vars->i1].t_str[j] != '<')
				vars->tokens[vars->i1].cmd[k++] = vars->tokens[vars->i1].t_str[j];
			// printf("2 else vars->tokens[%d].t_str[%d]	:%c\n", vars->i1, j, vars->tokens[vars->i1].t_str[j]);
			j++;
		}
		// printf("j = %d\n", j);
	}
	vars->tokens[vars->i1].cmd[k] = '\0';
	printf("vars->tokens[%d].cmd :%s\n", vars->i1, vars->tokens[vars->i1].cmd);
}

void	find_infile(t_prgm *vars)
{
	vars->i1 = 0;
	while (vars->i1 < vars->pipe_ct + 1)
	{
		vars->tokens[vars->i1].cmd = malloc(sizeof(char) * (ft_strlen(vars->tokens[vars->i1].t_str) + 1));
		find_infile_init(vars);
		// find_infile_go_to_string_end(vars);
		extract_infiles(vars);
		// find_infile_identify_input_redirection_type(vars);
		// find_infile_extract_infile(vars);
		// printf("vars->tokens[%d].infile :%s\n", vars->i1, \
		// 	vars->tokens[vars->i1].infile);
		vars->i1++;
	}
}
