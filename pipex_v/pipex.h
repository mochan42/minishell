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
# include "libs/ft_printf/ft_printf.h"
# include "libs/gnl/get_next_line.h"
# include "libs/libft/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*bin_path;
	char	**options;
}			t_cmd;
typedef struct s_pipe
{
	int		fd[MAX_CMD][2];
	t_cmd	cmds[MAX_CMD];
	int		fd_args[2];
	int		child;
	int		pid[MAX_CMD];
	int		nb_cmd;
	int		status;
	int		ac;
	char	**av;
	char	**env;
	char	error[MAX_CMD][100];
	char	*tmp_file;
	int		fd_hd;
}				t_pipe;
/* check_input.c */
int		ft_valid_nb_args(int argc);
int		ft_valid_args(t_pipe *p);
void	ft_check_files(t_pipe *p);
void	ft_check_full_cmd_pt(t_pipe *p, char *tmp, int cmd);
/* utils_2.c*/
void	free_p(t_pipe *p);
int		len_path(char **paths);
void	ft_parse_all(t_pipe *p, char **pt);
void	ft_init_pipe(t_pipe *p, int argc, char **argv, char **envp);
/* utils.c */
char	*ft_get_path(char **envp);
void	ft_parse(t_pipe *p, char **paths, int cmd);
void	ft_put_error_outfile(t_pipe *p, char *error);
void	ft_set_cmd_error_msg(t_pipe *p, char **tmp, int cmd);
/* parent.c */
void	ft_parent_process(t_pipe *p);
/* exec_cmd.c*/
void	ft_exec_cmd_1(t_pipe *p);
void	ft_exec_cmd_last(t_pipe *p);
void	ft_close_fds(t_pipe *p);
/* childs_process.c */
void	ft_childs_process(t_pipe *p);
/* errors.c */
int		ft_is_error(t_pipe *p);
void	ft_print_err_message(t_pipe *p);
/* util_3.c */
void	ft_generate_p(t_pipe *p);
int		ft_valid_nb_args_bonus(int argc);
/* here_doc.c */
void	ft_here_doc(t_pipe *p);
#endif
