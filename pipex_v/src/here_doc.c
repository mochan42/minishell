/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:40:43 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/17 23:40:43 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include "../inc/pipex.h"

void	ft_here_doc(t_prgm *vars, int cmd)
{
	char	*tmp_read;
    char    *delimiter;

    delimiter = vars->tokens[cmd].infile;
	// printf("delimiter :%s\n", delimiter);
	// printf("heredoc_file :%s\n", heredoc_file);
	// exit (0);
	vars->tokens[cmd].fd_args[0] = open("tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
	while (1)
	{
		tmp_read = readline("> ");
		if (ft_strncmp(delimiter, tmp_read, ft_strlen(delimiter)) == 0)
		{
			free(tmp_read);
			break ;
		}
		write(vars->tokens[cmd].fd_args[0], tmp_read, ft_strlen(tmp_read));
		free(tmp_read);
		write(vars->tokens[cmd].fd_args[0], "\n", 1);
	}
	close(vars->tokens[cmd].fd_args[0]);
	vars->tokens[cmd].fd_args[0] = open("tmp.txt", O_RDONLY);
	unlink("tmp.txt");
}
