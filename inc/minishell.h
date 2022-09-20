/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:55:22 by mochan            #+#    #+#             */
/*   Updated: 2022/09/20 18:17:29 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ########################################################################## */
/* INCLUDES */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/* ########################################################################## */
/* STRUCTURES */

typedef struct s_token
{
	char	*in;
	char	*out;
	char	*cmd;
	int		built_in;
	char	*options;
	char	*token_str;
	char	*exp_var;
}	t_token;

typedef struct s_prgm
{
	char	*cmd_line;
	char	**env; //transform into a linked list
	t_token	*array_tokens;
	int		pipe_ct;
}	t_prgm;

/* ########################################################################## */
/* CONSTANTS */
# define MAXCOM 1000 // max number of letters to support directory printing

/* ########################################################################## */
/* FUNCTIONS */

/*  init.c */
// char		*find_path_in_envp(t_prgm vars);
void		init(t_prgm *vars);

/* executer.c */
void		ms_executer(t_prgm *vars);

/* free.c */
void		free_table(char **table);
void		free_stuff(t_prgm *vars);

/* parsing.c */
// char		**parse_for_pipe(t_prgm *vars);
// char		**parse_for_space(t_prgm *vars);
void		parsing(t_prgm *vars);
void		parsing_lvl1(t_prgm *vars);

#endif