/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:46:49 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/25 16:37:42 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* INCLUDES */
# include "../../libft/inc/libft.h"
# include "../../pipex_v/inc/pipex.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define MAX_CMD  150

/* ########################################################################## */
/* STRUCTURES */

// typedef struct s_env
// {
// 	struct s_env	*next;
// 	struct s_env	*prev;
// 	char			*key;
// 	char			*value;
// }	t_env;

// typedef struct s_pipe
// {
// 	int			fd[MAX_CMD][2];
// 	int			child;
// 	int			pid[MAX_CMD];
// 	int			nb_cmd;
// 	int			status;
// 	t_env		envp;
// 	char		error[MAX_CMD][100];
// 	char		*tmp_file;
// 	int			fd_hd;
// }	t_pipe;

// typedef struct s_token
// {
// 	char	*in; //specify if it is < or <<
// 	char	*out; //specify if it is > or >>
// 	char	*infile; // TO DO 
// 	char	*outfile; // TO DO 
// 	char	*bin;
// 	int		built_in; // 0 is exec, 1 is built-in
// 	char	**options; // TO DO : cmd + options;
// 	char	*t_str;
// 	char	*t_str_exp; // TO DO
// 	char	*cmd; // TO DO : only cmd
// }	t_token;

// typedef struct s_prgm
// {
// 	char	*cmd_line;
// 	char	**env; //transform into a linked list
// 	t_token	*tokens;
// 	int		pipe_ct;
// t_pipe	p;
// }	t_prgm;



// typedef struct s_env
// {
// 	struct s_env	*next;
// 	struct s_env	*prev;
// 	char			*key;
// 	char			*value;
// } 				t_env;

// typedef struct s_pipe
// {
// 	int		fd[MAX_CMD][2];
// 	int		child;
// 	int		pid[MAX_CMD];
// 	int		nb_cmd;
// 	int		status;
// 	t_env	envp;
// 	char	error[MAX_CMD][100];
// 	char	*tmp_file;
// 	int		fd_hd;
// }				t_pipe;

// typedef struct s_token
// {
// 	char	*in;
// 	char	*out;
// 	char	*infile;
// 	char	*outfile;
// 	char	*bin;
// 	int		built_in;
// 	char	**options;
// 	char	*t_str;
// 	char	*t_str_exp; 
// 	char	*cmd;
// }				t_token;

// typedef struct s_env
// {
//     struct s_env    *next;
//     struct s_env    *prev;
//     char            *key;
//     char            *value;
// }                 t_env;


/* ########################################################################## */
/* CONSTANTS */

# define MAX_CMD 150

/* ########################################################################## */
/* FUNCTIONS */

/*  init.c */
// char		*find_path_in_envp(t_prgm vars);
//void		initialise_ms(t_prgm *vars);
void		init(t_prgm *vars);
void		init_each_token(t_token *token);
void		init_all_tokens(t_prgm *vars);

/* executer.c */
// void		ms_executer(t_prgm *vars);

/* free.c */
void		free_table(char **table);
void		free_stuff(t_prgm *vars);

/* parsing.c */
// char		**parse_for_pipe(t_prgm *vars);
// char		**parse_for_space(t_prgm *vars);
void		parsing(t_prgm *vars);
void		parsing_pipes(t_prgm *vars);
void		parsing_in_redir_heredoc(t_prgm *vars);
void		parsing_out_redir_heredoc(t_prgm *vars);
char		*retrieve_infile(t_prgm *vars);
// prompt.c
int	input_loop(t_prgm *vars);
#endif
