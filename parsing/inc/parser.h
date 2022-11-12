/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:46:49 by fakouyat          #+#    #+#             */
/*   Updated: 2022/11/12 13:44:32 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* INCLUDES */
/* ########################################################################## */
# include "../../libft/inc/libft.h"
# include "../../pipex_v/inc/pipex.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include </Users/fakouyat/goinfre/.brew/opt/readline/include/readline/readline.h>
# include </Users/fakouyat/goinfre/.brew/opt/readline/include/readline/history.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

/* ########################################################################## */
/* STRUCTURES */

// typedef struct s_finding_pipes
// {
// 	char	*s;
// 	char	*pipes_loc;
// 	int		i;
// 	int		b_open_double_quote;
// 	int		b_open_single_quote;
// }				t_finding_pipes;

typedef struct s_trim_quotes
{
	int		i;
	int		quote_opened;
	char	c;
	char	*res;
	int		j;
}				t_trim_quotes;

typedef struct s_fill_splitted_array_cmd
{
	int		word_start;
	int		length;
	int		word;
	int		flag;
	int		i;
	char	c;
	int		s_len;
}				t_fill_splitted_array_cmd;

/* ########################################################################## */
/* CONSTANTS */

/* ########################################################################## */
/* FUNCTIONS */

/* dollar_sign.c */
void		free_dollar_sign(t_prgm *v);
void		interpret_dollar_sign(t_prgm *v);

/* dollar_sign_2.c */
void		extract_ds_vars_helper(t_prgm *v);
void		extract_ds_vars(t_prgm *vars);
void		translate_var(t_prgm *v);
void		translate_var_helper(t_prgm *v, t_env *tmp_node, int flag);

/*  init.c */
void		init(t_prgm *vars);
void		init_each_token(t_prgm *vars, int i);
void		init_all_tokens(t_prgm *vars);

/* env.c */
void		init_env_init(t_prgm *vars);
void		init_env_split(t_prgm *vars);
t_env		*init_env(t_prgm *vars);

/* env_utils_1.c */
int			ft_list_size(t_env *begin_list);
t_env		*last_node(t_env *node);
t_env		*new_node(char *value);
void		node_add_back(t_env **node, t_env *n_node);
void		printlist(t_env *head);
int			ft_list_size(t_env *begin_list);

/* free.c */
void		free_table(char **table);
void		free_stuff(t_prgm *vars);
void		re_init_tokens(t_prgm *vars);

/* infile.c */
void		extract_infiles(t_prgm *vars);
void		find_infile(t_prgm *vars);
void		subs_infile(t_prgm *vars, int *start, int index);
void		extract_infiles_init(t_prgm *vars);

/* infile_utils_1.c */
int			count_input(t_prgm *vars);
int			is_input_redirect_and_not_inside_quotes(t_prgm *vars, int j);
int			is_heredoc_and_not_inside_quotes(t_prgm *vars, int j);

/* infile_utils_2.c */
void		extract_infile_heredoc_and_fill_in_cmd_string(t_prgm *vars);
void		extract_infile_input_redirect_and_fill_in_cmd_string(t_prgm *vars);
void		fill_in_cmd_string_no_infile(t_prgm *vars);
void		skip_white_spaces(t_prgm *vars, int *start, int cnt);

/* outfile.c */
void		extract_outfile(t_prgm *vars);
void		extract_outfiles_init(t_prgm *vars);
void		find_outfile(t_prgm *vars);
void		subs_outfile(t_prgm *vars, int *start, int index);

/* outfile_utils_1.c */
int			count_output(t_prgm *vars);
int			is_append_and_not_inside_quotes(t_prgm *vars, int j);
int			is_output_redirect_and_not_inside_quotes(t_prgm *vars, int j);

/* outfile_utils_2.c */
void		extract_outfile_append_and_fill_in_cmd_string(t_prgm *vars);
void		extract_outfile_output_redirect_and_fill_in_cmd_string(t_prgm \
			*vars);
void		fill_in_cmd_string_no_outfile(t_prgm *vars);

/* parsing.c */
void		count_true_pipes(t_prgm *vars);
void		splitting_pipes(t_prgm *vars);
void		splitting_pipes_no_pipes(t_prgm *vars);
void		parsing(t_prgm *vars);

/* parsing_utils_2.c */
char		*find_pipes(char *s);
void		ft_fill_splited_array_pipes(char **array_split, char *s, \
				char *pipes_loc, char c);
int			ft_nb_words_ms(char const *s, char c);
char		**ft_split_pipes(char const *s, char c);
// void		init_true_pipes(t_finding_pipes *vars_tp, char *s);

/* parsing_utils_3.c */
int			cnt_dquotes(char *s);
int			cnt_squotes(char *s);
int			is_double_quote(char c);
int			is_pipe(char c);
int			is_single_quote(char c);

/* parsing_utils_4.c */
int			cnt_dlr(char *s);
void		err_msg_quotes_not_closed(void);
void		extract_ds_vars_helper(t_prgm *v);
void		ft_str_replace(char **str, char *subs_to_r, char *r_by, int ref);

/* parsing_utils_5.c */
// void		check_if_double_quote_open_or_closed(t_finding_pipes *vars_tp);
// void		check_if_single_quote_open_or_closed(t_finding_pipes *vars_tp);
// void		init_true_pipes(t_finding_pipes *vars_tp, char *s);
char		*trim_quotes(char *s);
void		trim_quotes_helper(t_trim_quotes *tmp, char *s);
void		init_trim_quotes(t_trim_quotes *tmp, char *s);

/* parsing_utils_6.c */
int			ft_nb_words_cmd(char const *s, char c);
void		ft_fill_splited_array_cmd(char **array_split, char *s, char c);
char		**ft_split_cmd(char *s, char c);
void		init_fill_splitted_array_cmd(t_fill_splitted_array_cmd *tmp, \
			char c);

/* prompt.c */
void		high_level_tasks(t_prgm *vars);
int			input_loop(t_prgm *vars);

/* quotes.c */
int			are_quotes_closed_v3(char *s);
int			expand_ds(char *s, int ref);
int			**ft_ref_quote(char *s, char c);
void		ft_ref_quote_helper(int **tab, char *s, char c);
int			*is_between_quotes(char *s, char c, int ref);

/* quotes_utils_1.c */
int			cnt_quotes(char *s, char c);
#endif
