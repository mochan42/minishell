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
# include "../parsing/inc/parser.h"

/* check_input.c */
//int		ft_valid_nb_args(int argc);
int		ft_valid_args(t_prgm *vars);
void	ft_check_files(t_prgm *vars);
void	ft_check_full_cmd_pt(t_prgm *vars, char *tmp, int cmd);
/* utils_2.c*/
void	free_p(t_prgm *vars);
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
//int		ft_valid_nb_args_bonus(int argc);
/* here_doc.c */
//void	ft_here_doc(t_pipe *p);
#endif
