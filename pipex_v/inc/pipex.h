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
# define MAX_CMD  150
# define MAX_LEN_DIR 300
# include "../../libft/inc/libft.h"
# include "../../gnl/inc/get_next_line.h"
# include "../../parsing/inc/parser.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

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
	char	*in;
	char	*out;
	char	*infile;
	char	*outfile;
	char	*bin;
	int		built_in;
	char	**options;
	char	*t_str;
	char	*t_str_exp; 
	char	*cmd;
	int		fd_args[2];
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
}	t_prgm;

/* check_input.c */
//int		ft_valid_nb_args(int argc);
int		ft_valid_args(t_prgm *vars);
void	ft_check_files(t_prgm *vars);
void	ft_check_full_cmd_pt(t_prgm *vars, char *tmp, int cmd);
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
void	ft_exec_cmd_1(t_prgm *vars);
void	ft_exec_cmd_last(t_prgm *vars);
void	ft_close_fds(t_prgm *vars);
/* childs_process.c */
void	ft_childs_process(t_prgm *vars);
/* errors.c */
int		ft_is_error(t_prgm *vars);
void	ft_print_err_message(t_prgm *vars);
/* util_3.c */
void	ft_generate_p(t_prgm *vars);
void	free_2_pt(char **pt);
//int		ft_valid_nb_args_bonus(int argc);
/* here_doc.c */
void	ft_here_doc(t_prgm *vars, int cmd);
/* builtins.c*/
void	execbuilt_in(t_prgm *vars);
void    ft_cd(t_prgm *vars);
void	ft_pwd(t_prgm *vars);
void	ft_env(t_prgm *vars);
void	ft_export(t_prgm *vars);
void	ft_exit(t_prgm *vars);
void	ft_unset(t_prgm *vars);
void	ft_echo(t_prgm *vars);
/* pipex.c */
int		ms_executor(t_prgm *vars);

#endif
