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
# include </Users/mochan/goinfre/.brew/opt/readline/include/readline/readline.h>
# include </Users/mochan/goinfre/.brew/opt/readline/include/readline/history.h>

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*key;
	char			*value;
} 				t_env;

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
	int		*in; // for each token, indicates how many input files there are
	int		*out;
	char	**infile;
	char	**outfile;
	char	*bin;
	int		built_in;
	char	**options;
	char	*t_str;
	char	*t_str_og;
	char	*cmd;
	int		fd_args[100][2];
	int		nb_input;
	int		nb_output;
	int		*ref_dollar;
}				t_token;

typedef struct s_prgm
{
	char	*cmd_line;
	char	**env; //transform into a linked list
	t_env	*env_head;
	t_token	*tokens;
	int		pipe_ct;
	t_pipe	p;
	char	*builts[7];
	int		ct1[7]; // 7 counters for dollar sign expansion of command option arguments
	char	**array_ds_vars;
	char	**array_no_ds;
	char	**array_concat;
	char	*tmp;
	char	**array_tmp;
	char	**keys;
	char	**values;
	char	***res;
	int		i;
	int		j;
	char	*ptr_coa;
	int		start_coa;
	int		len_coa;
	int		i1;
	int		j1;
	char	*ptr_infile;
	char	*ptr_array_infiles;
	int		start_infile;
	int		len_infile;
	int		i2;
	int		j2;
	char	*ptr_outfile;
	int		start_outfile;
	int		len_outfile;
}	t_prgm;

/* check_input.c */
//int		ft_valid_nb_args(int argc);
int		ft_valid_args(t_prgm *vars);
void	ft_check_files(t_prgm *vars);
void	ft_check_full_cmd_pt(t_prgm *vars, char **tmp, int cmd);
/* utils_2.c*/
void	free_vars_p(t_prgm *vars);
int		len_path(char **paths);
void	ft_parse_all(t_prgm *vars, char **pt);
void	ft_init_pipe(t_prgm *vars);
/* utils.c */
char	*ft_get_path(char **envp);
void	ft_parse(t_prgm *vars, char **paths, int cmd);
void	ft_put_error_outfile(t_prgm *vars, char *error);
void	ft_set_cmd_error_msg(t_prgm *vars, char **tmp, int cmd);
/* parent.c */
void	ft_parent_process(t_prgm *vars);
/* exec_cmd.c*/
void	ft_exec_cmd_1(t_prgm *vars, int *let_error);
void	ft_exec_cmd_last(t_prgm *vars, int *let_error);
void	ft_close_fds(t_prgm *vars);
/* childs_process.c */
void	ft_childs_process(t_prgm *vars);
void	ft_in_redirect(t_prgm *vars, int *let_error);
void	ft_mid_heredoc(t_prgm *vars);
void	ft_redirect_out(t_prgm	*vars);
void	ft_infile_checking(t_prgm *vars, int *let_error);
/* errors.c */
int		ft_is_error(t_prgm *vars);
void	ft_print_err_message(t_prgm *vars);
/* util_3.c */
void	ft_generate_p(t_prgm *vars);
void	free_2_pt(char **pt);
void	ft_exit_code(int ex_code, int mode);
//int		ft_valid_nb_args_bonus(int argc);
/* here_doc.c */
void	ft_here_doc(t_prgm *vars, int cmd, int j);
char	*ft_creat_tmp_file(void);
/* builtins.c*/
void	execbuilt_in(t_prgm *vars);
void    ft_cd(t_prgm *vars);
void	ft_pwd(void);
void	ft_env(t_prgm *vars);
void	ft_export(t_prgm *vars);
void	ft_exit(t_prgm *vars);
void	ft_unset(t_prgm *vars, char *var);
void	ft_echo(t_prgm *vars);
int		is_our_env_path(t_prgm *vars);
void	ft_update_env(t_env *envp, char *oldpwd);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_export_new_key(t_prgm *vars);
void	ft_t_env_to_array(t_env *envp, char ***env_ord);
void	ft_print_exported_env(char ***env_ord, int env_size);
char	*get_our_env(t_prgm *vars, char *var);
t_env   *ft_creat_var_node(char *delim, t_prgm *vars, int i, int curr);
int		ft_unset_single_var(t_prgm *vars, char *var);
/* pipex.c */
int		ms_executor(t_prgm *vars);
void	ft_execve_cmds(t_prgm *vars);
int		ft_anticipate_heredoc(t_prgm *vars);
int		ft_only_outfile(t_prgm *vars);
/* signal .c */
void    new_prompt(int sign_num);
void    exit_shell(int sign_num);
void    end_state(int sign_num);
void    erase_prompt(void);
#endif
