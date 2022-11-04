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

char	*ft_creat_tmp_file(void)
{
	char	*tmp;
	char	*tmp_2;
	int		i;

	i = 0;
	tmp = ft_strdup("__tmp__here_doc__");
	tmp_2 = NULL;
	while (access(tmp, F_OK) == 0)
	{
		if (tmp_2)
			free(tmp_2);
		tmp_2 = ft_strdup(tmp);
		free(tmp);
		tmp = ft_strjoin(tmp_2, ft_itoa(i));
		i++;
	}
	if (tmp_2)
		free(tmp_2);
	return (tmp);
}

void	ft_here_doc(t_prgm *vars, int cmd, int j)
{
	char	*tmp_read;
	char	*delimiter;
	char	*tmp;

	tmp = ft_strjoin(ft_creat_tmp_file(), ft_itoa(cmd));
	delimiter = vars->tokens[cmd].infile[j];
	vars->tokens[cmd].fd_args[j][0] = open(tmp,
			O_RDWR | O_CREAT | O_APPEND, 0666);
	while (1)
	{
		tmp_read = readline("> ");
		if (ft_strncmp(delimiter, tmp_read, ft_strlen(delimiter)) == 0)
		{
			free(tmp_read);
			break ;
		}
		write(vars->tokens[cmd].fd_args[j][0], tmp_read, ft_strlen(tmp_read));
		free(tmp_read);
		write(vars->tokens[cmd].fd_args[j][0], "\n", 1);
	}
	close(vars->tokens[cmd].fd_args[j][0]);
	vars->tokens[cmd].fd_args[j][0] = open(tmp, O_RDONLY);
	unlink(tmp);
	free(tmp);
}
