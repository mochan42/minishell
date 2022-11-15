/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:15:05 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/16 13:15:05 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* INCLUDES */
/* ########################################################################## */
#ifndef PIPEX_H
# define PIPEX_H
# define MAX_CMD  200
# define MAX_LEN_DIR 300
# define IN_STD 10
# define IN_REDIRECT 11
# define IN_HEREDOC 12
# define OUT_STD 20
# define OUT_REDIRECT 21
# define OUT_APPEND 22
# include "../../libft/inc/libft.h"
# include "../../gnl/inc/get_next_line.h"
# include "../../parsing/inc/parser.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include </Users/fakouyat/goinfre/.brew/opt/readline/include/readline/readline.h>
# include </Users/fakouyat/goinfre/.brew/opt/readline/include/readline/history.h>
// # include <readline/readline.h>
// # include <readline/history.h>

/* ########################################################################## */
/* STRUCTURES */

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*key;
	char			*value;
}				t_env;

typedef struct s_pipe
{
	int		fd[MAX_CMD][2];
	int		child;
	int		pid[MAX_CMD];
	int		nb_cmd;
	int		status;
	char	error[MAX_CMD][100];
}				t_pipe;

typedef struct s_token
{
	int		*in;
	int		*out;
	char	**infile;
	char	**outfile;
	char	*bin;
	int		built_in;
	char	**opts;
	char	*t_str;
	char	*t_str_og;
	char	*cmd;
	int		fd_args[200][2];
	int		nb_input;
	int		nb_output;
	int		*rf_d;
}				t_token;

typedef struct s_prgm
{
	char	*cmd_line;
	char	**env;
	t_env	*env_head;
	t_token	*tok;
	int		pipe_ct;
	t_pipe	p;
	char	*builts[7];
	int		ct1[7];
	char	**d_v;
	char	*tmp;
	char	**array_tmp;
	char	**keys;
	char	**values;
	char	***res;
	int		i;
	int		j;
	int		k;
	int		start;
	int		index;
	int		exit;
	int		tok_error;
}	t_prgm;

/* ########################################################################## */
/* FUNCTIONS */

/* check_input.c */
//int		ft_valid_nb_args(int argc);
int		ft_valid_args(t_prgm *vars);
int		ft_catch_empty_cmd(t_prgm *vars, char **tmp_cmd, int i);
void	ft_check_full_cmd_pt(t_prgm *vars, char **tmp, int cmd);
void	ft_check_files(t_prgm *vars);

/* utils_2.c*/
void	free_vars_p(t_prgm *vars);
int		len_path(char **paths);
void	ft_parse_all(t_prgm *vars, char **pt);
void	ft_is_builtins_cmd(t_prgm *vars, int i);
int		ft_is_error_opts(t_prgm *vars, int i, int j);

/* utils.c */
char	*ft_get_path(char **envp);
void	ft_set_cmd_error_msg(t_prgm *vars, char **tmp, int cmd);
void	ft_parse(t_prgm *vars, char **paths, int cmd);
void	ft_put_error_outfile(t_prgm *vars, char *error);
int		ft_assert_numeric(t_prgm *vars, int indice);

/* parent.c */
void	ft_parent_process(t_prgm *vars);

/* exec_cmd.c*/
void	ft_processing_output_1(t_prgm *vars);
void	ft_exec_cmd_1(t_prgm *vars, int *let_error);
void	ft_processing_output(t_prgm *vars);
void	ft_exec_cmd_last(t_prgm *vars, int *let_error);
void	ft_close_fds(t_prgm *vars);

/* childs_process.c */
void	ft_infile_checking(t_prgm *vars, int *let_error);
void	ft_in_redirect(t_prgm *vars, int *let_error);
void	ft_redirect_out(t_prgm	*vars);
void	ft_childs_process(t_prgm *vars);

/* errors.c */
int		ft_is_error(t_prgm *vars);
void	ft_print_err_message(t_prgm *vars);

/* util_3.c */
void	ft_generate_p(t_prgm *vars);
void	free_2_pt(char **pt);
void	ft_exit_code(int ex_code, int mode);
int		ft_check_ex_opts(t_prgm *vars);
int		is_numeric(char c);

/* here_doc.c */
char	*ft_creat_tmp_file(void);
void	ft_close_tmp_here_file(t_prgm *vars, char *tmp, int j, int cmd);
void	ft_here_doc(t_prgm *vars, int cmd, int j);

/* builtins_1.c*/
void	execbuilt_in(t_prgm *vars);
void	ft_pwd(void);
void	ft_env(t_prgm *vars);
void	ft_exit(t_prgm *vars);
void	ft_exit_shell(t_prgm *vars);

/* builtins_2.c */
void	ft_t_env_to_array(t_env *envp, char ***env_ord);
void	ft_sorting_env(char ***env_ord, int env_size);
void	ft_print_exported_env(char ***env_ord, int env_size);
void	ft_export(t_prgm *vars);
void	ft_only_file_in(t_prgm *vars, int i);

/*builtins_3.c */
void	ft_echo(t_prgm *vars);
void	ft_unset(t_prgm *vars, char *var);
int		ft_unset_single_var(t_prgm *vars, char *var);
void	ft_only_file_out(t_prgm *vars, int i);

/* builtins_4.c */
char	*get_our_env(t_prgm *vars, char *var);
int		is_our_env_path(t_prgm *vars);
void	ft_cd(t_prgm *vars);
void	ft_update_env(t_env *envp, char *oldpwd);

/* builtins_5.c */
int		ft_strcmp(const char *s1, const char *s2);
t_env	*ft_creat_var_node(char *delim, t_prgm *vars, int i, int curr);
void	ft_export_new_key(t_prgm *vars);
int		ft_is_env_buil_ins_check(t_prgm *vars);

/* pipex.c */
void	ft_execve_cmds(t_prgm *vars);
int		ft_is_env_buil_ins(t_prgm *vars);
int		ft_catch_parse_error(t_prgm *vars);
int		ms_executor(t_prgm *vars);
int		ft_anticipate_heredoc(t_prgm *vars);

/* signal .c */
void	new_prompt(int sign_num);
void	erase_prompt(void);
#endif