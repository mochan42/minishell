/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:46:49 by fakouyat          #+#    #+#             */
/*   Updated: 2022/10/01 17:46:42 by mochan           ###   ########.fr       */
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

/* cmd_arg_opt.c */
void		find_cmd_opt_arg(t_prgm *vars);

/*  init.c */
// char		*find_path_in_envp(t_prgm vars);
//void		initialise_ms(t_prgm *vars);
void		init(t_prgm *vars);
void		init_each_token(t_token *token);
void		init_all_tokens(t_prgm *vars);

/* env.c */
t_env		*init_env(t_prgm *vars);
t_env		*last_node(t_env *node);
t_env		*new_node(char *value);
void		node_add_back(t_env **node, t_env *new);
void		printlist(t_env *head);

/* free.c */
void		free_table(char **table);
void		free_stuff(t_prgm *vars);
void		re_init_tokens(t_prgm *vars);

/* infile.c */
void		find_infile(t_prgm *vars);

/* outfile.c */
void		find_outfile(t_prgm *vars);

/* parsing.c */
// char		**parse_for_pipe(t_prgm *vars);
// char		**parse_for_space(t_prgm *vars);
void		splitting_pipes(t_prgm *vars);
void		parsing(t_prgm *vars);
char		*retrieve_infile(t_prgm *vars);

/* parsing_utils_1.c */
void		ft_fill_splited_array_2(char **array_split, char *s, char *needle);
int			ft_nb_words_2(char const *s, char *needle);
char		**ft_split_2(char const *s, char *needle);

/* parsing_utils_1.c */
char		*find_pipes(char *s);
void		ft_fill_splited_array_pipes(char **array_split, char *s, \
				char *pipes_loc, char c);
int			ft_nb_words_ms(char const *s, char c);
char		**ft_split_pipes(char const *s, char c);
int			is_double_quote(char c);
int			is_pipe(char c);

/* prompt.c */
int			input_loop(t_prgm *vars);
#endif
