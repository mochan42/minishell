/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:46:49 by fakouyat          #+#    #+#             */
/*   Updated: 2022/11/05 21:49:15 by mochan           ###   ########.fr       */
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
// # include </Users/mochan/goinfre/.brew/opt/readline/include/readline/readline.h>
// # include </Users/mochan/goinfre/.brew/opt/readline/include/readline/history.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define MAX_CMD  150

/* ########################################################################## */
/* STRUCTURES */

typedef struct s_finding_pipes
{
	char	*s;
	char	*pipes_loc;
	int		i;
	int		b_open_double_quote;
	int		b_open_single_quote;
}				t_finding_pipes;

/* ########################################################################## */
/* CONSTANTS */

# define MAX_CMD 150

/* ########################################################################## */
/* FUNCTIONS */

/* cmd_opt_arg.c */
void		find_cmd_opt_arg(t_prgm *vars);
void		find_cmd_opt_arg_both_redirections(t_prgm *vars);
void		find_cmd_opt_arg_input_redirection_only(t_prgm *vars);
void		find_cmd_opt_arg_no_redirection_(t_prgm *vars);
void		find_cmd_opt_arg_output_redirection_only(t_prgm *vars);

/* cmd_opt_arg_utils_1.c */
void		go_to_beginning_cmd_opt_arg(t_prgm *vars);
void		go_to_string_end(t_prgm *vars);
void		jump_cmd_opt_arg_input_redirect(t_prgm *vars);
void		jump_infile(t_prgm *vars);
void		jump_white_spaces(t_prgm *vars, char *s);

/* cmd_opt_arg_utils_2.c */
void		find_beginning_of_cmd_opt_arg(t_prgm *vars);
void		jump_cmd_opt_arg_output_redirect(t_prgm *vars);
void		jump_cmd_opt_arg_when_output_redirection_only(t_prgm *vars);
void		move_backwards_by_one_char(t_prgm *vars);
void		move_forward_by_one_char(t_prgm *vars);

/* cmd_opt_arg_utils_3.c */
void		check_if_cmd_is_builtin(t_prgm *vr, int i);
void		extract_cmd_opt_arg_both_redirections(t_prgm *vars);
void		extract_cmd_opt_arg_middle_input_redirection_only(t_prgm *vars);
void		extract_coa_at_string_middle_both_redirections(t_prgm *vars);
void		extract_coa_at_string_start_both_redirections(t_prgm *vars);

/* cmd_opt_utils_4.c */
void		extract_cmd_opt_arg_start_both_redirections_out2in(t_prgm *vars);
void		extract_cmd_opt_arg_start_input_redirection_only(t_prgm *vars);
void		extract_cmd_opt_arg_start_output_redirection_only(t_prgm *vars);
void		jump_outfile(t_prgm *vars);

/* dollar_sign.c */
void		concatenate_strings_helper_1(t_prgm *v);
void		concatenate_strings(t_prgm *v);
void		extract_string_no_ds_helper(t_prgm *v);
void		extract_string_no_ds(t_prgm *v);
void		ids_cmd_opt_arg(t_prgm *vars);
void		interpret_dollar_sign(t_prgm *vars);

/* dollar_sign_2.c */
void		extract_ds_vars_helper(t_prgm *v);
void		extract_ds_vars(t_prgm *vars);
void		translate_var(t_prgm *v);

/*  init.c */
void		init(t_prgm *vars);
void		init_each_token(t_token *token);
void		init_all_tokens(t_prgm *vars);

/* env.c */
void		init_env_init(t_prgm *vars);
void		init_env_split(t_prgm *vars);
t_env		*init_env(t_prgm *vars);

/* env_utils_1.c */
int			ft_list_size(t_env *begin_list);
t_env		*last_node(t_env *node);
t_env		*new_node(char *value);
void		node_add_back(t_env **node, t_env *new);
void		printlist(t_env *head);
int			ft_list_size(t_env *begin_list);

/* free.c */
void		free_table(char **table);
void		free_stuff(t_prgm *vars);
void		re_init_tokens(t_prgm *vars);

/* infile.c */
void		find_infile(t_prgm *vars);
void		find_infile_extract_heredoc_infile(t_prgm *vars);
void		find_infile_extract_infile(t_prgm *vars);
void		find_infile_extract_redirection_infile(t_prgm *vars);
void		find_infile_identify_input_redirection_type(t_prgm *vars);

int			count_input(t_prgm *vars);
void		extract_infiles(t_prgm *vars);
void		skip_white_spaces(t_prgm *vars, int *start, int cnt);
void		subs_infile(t_prgm *vars, int *start, int index);

/* infile_utils_1.c */
void		find_infile_init(t_prgm *vars);
void		find_infile_go_to_string_end(t_prgm *vars);

/* outfile.c */
void		find_outfile(t_prgm *vars);
void		find_outfile_identify_output_redirection_type(t_prgm *vars);
void		find_outfile_extract_outfile(t_prgm *vars);
void		find_outfile_extract_redirection_outfile(t_prgm *vars);
void		find_outfile_extract_heredoc_outfile(t_prgm *vars);

int			count_output(t_prgm *vars);
void 		extract_outfile(t_prgm *vars);

/* outfile_utils_1.c */
void		find_outfile_init(t_prgm *vars);
void		find_outfile_go_to_string_end(t_prgm *vars);

/* parsing.c */
void		splitting_pipes(t_prgm *vars);
void		splitting_pipes_no_pipes(t_prgm *vars);
void		parsing(t_prgm *vars);

/* parsing_utils_2.c */
char		*find_pipes(char *s);
void		ft_fill_splited_array_pipes(char **array_split, char *s, \
				char *pipes_loc, char c);
int			ft_nb_words_ms(char const *s, char c);
char		**ft_split_pipes(char const *s, char c);
void		init_true_pipes(t_finding_pipes *vars_tp, char *s);

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
char		*ft_concat(char *str1, const char *str2);
void		ft_str_replace(char **str, char *subs_to_r, char *r_by);

/* parsing_utils_5.c */
void		check_if_double_quote_open_or_closed(t_finding_pipes *vars_tp);
void		check_if_single_quote_open_or_closed(t_finding_pipes *vars_tp);
void		init_true_pipes(t_finding_pipes *vars_tp, char *s);

/* prompt.c */
void		high_level_tasks(t_prgm *vars);
int			input_loop(t_prgm *vars);
#endif
