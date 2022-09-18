/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:55:22 by mochan            #+#    #+#             */
/*   Updated: 2022/09/18 16:17:16 by mochan           ###   ########.fr       */
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

typedef struct s_prgm
{
	char	*cmd_line;
	char	**env;
	char	*env_path;
	char	**cmd_paths;
	int		pipe_ct;
}	t_prgm;

typedef struct s_token
{
	int		id;
	char	*str;
	char	*cmd;
	char	*options;
}	t_token;

/* ########################################################################## */
/* CONSTANTS */
# define MAXCOM 1000 // max number of letters to support directory printing

/* ########################################################################## */
/* FUNCTIONS */

/*  init.c */
char		*find_path_in_envp(t_prgm vars);
void		init(t_prgm *vars);

/* free.c */
void		free_table(char **table);
void		free_stuff(t_prgm *vars);

/* parsing.c */
char		**parse_space(t_prgm *vars);
void		parsing(t_prgm *vars);

#endif