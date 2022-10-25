/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:27:23 by mochan            #+#    #+#             */
/*   Updated: 2022/10/25 19:42:11 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	count_input_redirections(t_prgm *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (vars->pipe_ct + 1))
	{
		while (vars->tokens[i].t_str[j] != '\0')
		{
			if (vars->tokens[i].t_str[j+1] != '\0' && vars->tokens[i].t_str[j+1] == '<' \
				&& vars->tokens[i].t_str[j] == '<')
			{
				vars->tokens[i].nb_in++;
				j++;
			}
			else if (vars->tokens[i].t_str[j] == '<')
				vars->tokens[i].nb_in++;
			j++;
		}
		printf("token[%d] nb_in =%d\n", i, vars->tokens[i].nb_in);
		i++;
	}
}

void	init_array_input_redirection_types(t_prgm *vars)
{
	int	i;
	i = 0;

	while (i < (vars->pipe_ct + 1))
	{
		vars->tokens[i].array_in = malloc(sizeof(char *) * \
			(vars->tokens[i].nb_in + 1));
		if (!vars->tokens[i].array_in)
			return ;
		vars->tokens[i].array_in[vars->tokens[i].nb_in] = NULL;
		i++;
	}
}

void	fill_in_array_input_redirection_types(t_prgm *vars)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	j = 0;
	index = 0;
	while (i < (vars->pipe_ct + 1))
	{
		while (vars->tokens[i].t_str[j] != '\0')
		{
			if (vars->tokens[i].t_str[j+1] != '\0' && vars->tokens[i].t_str[j+1] == '<' \
				&& vars->tokens[i].t_str[j] == '<')
			{
				vars->tokens[i].array_in[index] = ft_strdup("<<");
				index++;
				j++;
			}
			else if (vars->tokens[i].t_str[j] == '<')
			{
				vars->tokens[i].array_in[index] = ft_strdup("<");
				index++;
			}
			j++;
		}
		i++;
	}
}

void	print_input_redirection_types(t_prgm *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (vars->pipe_ct + 1))
	{
		while (j < vars->tokens[i].nb_in)
		{
			printf("vars->tokens[%d].array_in[%d] :%s\n", i, j, \
				vars->tokens[i].array_in[j]);
			j++;
		}
		i++;
	}
}

void	init_array_infiles(t_prgm *vars)
{
	int	i;
	i = 0;

	while (i < (vars->pipe_ct + 1))
	{
		vars->tokens[i].array_infiles = malloc(sizeof(char *) * \
			(vars->tokens[i].nb_in + 1));
		if (!vars->tokens[i].array_infiles)
			return ;
		vars->tokens[i].array_infiles[vars->tokens[i].nb_in] = NULL;
		i++;
	}
}

void	fill_in_array_infiles(t_prgm *vars)
{
	int	index;
	int	len_infile_arr;

	index = 0;
	vars->i1 = 0;
	while (vars->i1 < (vars->pipe_ct + 1))
	{
		vars->j1 = 0;
		vars->ptr_array_infiles = ft_strdup(vars->tokens[vars->i1].t_str);
		while (vars->tokens[vars->i1].t_str[vars->j1] != '\0')
		{
			printf("\tstart of j1 while loop: vars->j1 =%d\n", vars->j1);
			if (vars->tokens[vars->i1].t_str[vars->j1 + 1] != '\0' && \
				vars->tokens[vars->i1].t_str[vars->j1 + 1] == '<' && \
				vars->tokens[vars->i1].t_str[vars->j1] == '<')
			{
				vars->j1++;
				vars->j1++;
				vars->ptr_array_infiles++;
				vars->ptr_array_infiles++;
				jump_white_spaces(vars, "ptr_array_infiles");
				len_infile_arr = 0;
				while (vars->tokens[vars->i1].t_str[vars->j1] != ' ' && \
					vars->tokens[vars->i1].t_str[vars->j1] != '\0')
				{
					vars->j1++;
					len_infile_arr++;
				}
				vars->tokens[vars->i1].array_infiles[index] = ft_substr(vars->ptr_array_infiles, 0, len_infile_arr);
				printf("vars->tokens[%d].array_infiles[%d] :%s\n", vars->i1, index, vars->tokens[vars->i1].array_infiles[index]);
				index++;
			}
			else if (vars->tokens[vars->i1].t_str[vars->j1] == '<')
			{
				printf("\t\tCOUCOU\n");
				printf("\t\tenter else if statement : vars->j1 = %d\n", vars->j1);
				vars->j1++;
				vars->ptr_array_infiles++;
				printf("\t\tafter jump < and before jump space: vars->j1 = %d\n", vars->j1);
				printf("\t\ttoken[%d] START vars->ptr_array_infiles :%s\n", vars->i1, vars->ptr_array_infiles);
				jump_white_spaces(vars, "ptr_array_infiles");
				printf("\t\tafter jump space: vars->j1 = %d\n", vars->j1);
				printf("\t\ttoken[%d] AFTER JUMP SPACE vars->ptr_array_infiles :%s\n", vars->i1, vars->ptr_array_infiles);
				len_infile_arr = 0;
				while (vars->tokens[vars->i1].t_str[vars->j1] != ' ' && \
					vars->tokens[vars->i1].t_str[vars->j1] != '\0')
				{
					vars->j1++;
					len_infile_arr++;
				}
				printf("\t\ttoken[%d] BEFORE FT_SUBSTR vars->ptr_array_infiles :%s\n", vars->i1, vars->ptr_array_infiles);
				printf("\t\tlen_infile_arr =%d\n", len_infile_arr);
				vars->tokens[vars->i1].array_infiles[index] = ft_substr(vars->ptr_array_infiles, 0, len_infile_arr);
				printf("\t\tvars->tokens[%d].array_infiles[%d] :%s\n", vars->i1, index, vars->tokens[vars->i1].array_infiles[index]);
				index++;
			}
			vars->j1++;
			vars->ptr_array_infiles++;
			printf("\tend of j1 while loop : vars->j1 =%d\n", vars->j1);
		}
		vars->i1++;
	}
}

void	find_infile_identify_input_redirection_types_array(t_prgm *vars)
{
	int	i;

	i = 0;
	printf("===========HERE================\n");
	while (i < (vars->pipe_ct + 1))
	{
		printf("vars->tokens[%d].t_str :%s\n", i, vars->tokens[i].t_str);
		i++;
	}
	count_input_redirections(vars);
	init_array_input_redirection_types(vars);
	fill_in_array_input_redirection_types(vars);
	print_input_redirection_types(vars);
	init_array_infiles(vars);
	fill_in_array_infiles(vars);
	exit (0);
}

void	find_infile_identify_input_redirection_type(t_prgm *vars)
{
	while (vars->j1 != -1)
	{
		if (vars->j1 > 0 && vars->tokens[vars->i1].t_str[vars->j1] == '<' && \
			vars->tokens[vars->i1].t_str[vars->j1 - 1] == '<')
		{
			vars->tokens[vars->i1].in = "<<";
			vars->j1++;
			vars->ptr_infile++;
			break ;
		}
		else if (vars->tokens[vars->i1].t_str[vars->j1] == '<')
		{
			vars->tokens[vars->i1].in = "<";
			vars->j1++;
			vars->ptr_infile++;
			break ;
		}
		else
		{
			vars->j1--;
			vars->ptr_infile--;
		}
	}
}

void	find_infile_extract_heredoc_infile(t_prgm *vars)
{
	while (vars->tokens[vars->i1].t_str[vars->j1] == ' ' || \
		vars->tokens[vars->i1].t_str[vars->j1] == '\t')
	{
		vars->j1++;
		vars->start_infile++;
	}
	while ((vars->tokens[vars->i1].t_str[vars->j1] != ' ' && \
		vars->tokens[vars->i1].t_str[vars->j1] != '\0'))
	{
		vars->j1++;
		vars->len_infile++;
	}
	vars->tokens[vars->i1].infile = ft_substr(vars->ptr_infile, \
		vars->start_infile, vars->len_infile);
	printf("input type[%d]= %s\n", vars->i1, vars->tokens[vars->j1].in);
	printf("infile[%d]=%s\n", vars->j1, vars->tokens[vars->j1].infile);
}

void	find_infile_extract_redirection_infile(t_prgm *vars)
{
	while (vars->tokens[vars->i1].t_str[vars->j1] == ' ' || \
		vars->tokens[vars->i1].t_str[vars->j1] == '\t')
	{
		vars->j1++;
		vars->start_infile++;
	}
	while ((vars->tokens[vars->i1].t_str[vars->j1] != ' ' && \
		vars->tokens[vars->i1].t_str[vars->j1] != '\0'))
	{
		vars->j1++;
		vars->len_infile++;
	}
	printf("input type[%d]= %s\n", vars->i1, vars->tokens[vars->i1].in);
	vars->tokens[vars->i1].infile = ft_substr(vars->ptr_infile, \
		vars->start_infile, vars->len_infile);
	printf("infile[%d]=%s\n", vars->i1, vars->tokens[vars->i1].infile);
}

void	find_infile_extract_infile(t_prgm *vars)
{
	if (vars->tokens[vars->i1].in != NULL && \
		ft_strncmp(vars->tokens[vars->i1].in, "<<", 2) == 0)
		find_infile_extract_heredoc_infile(vars);
	else if (vars->tokens[vars->i1].in != NULL && \
		ft_strncmp(vars->tokens[vars->i1].in, "<", 1) == 0)
		find_infile_extract_redirection_infile(vars);
}

void	find_infile(t_prgm *vars)
{
	vars->i1 = 0;
	while (vars->i1 < vars->pipe_ct + 1)
	{
		find_infile_init(vars);
		find_infile_identify_input_redirection_types_array(vars);
		find_infile_go_to_string_end(vars);
		find_infile_identify_input_redirection_type(vars);
		find_infile_extract_infile(vars);
		printf("vars->tokens[%d].infile :%s\n", vars->i1, \
			vars->tokens[vars->i1].infile);
		vars->i1++;
	}
}
