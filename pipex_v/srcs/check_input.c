/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:31:45 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/16 13:31:45 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_valid_nb_args(int argc)
{
	if (argc < 5)
	{
		ft_printf("Error : fews arguments\n");
		return (0);
	}
	if (argc > 5)
	{
		ft_printf("Error : too much arguments\n");
		return (0);
	}
	return (1);
}

void	ft_check_files(t_pipe *p)
{
	ft_bzero(p->error[0], 100);
	ft_bzero(p->error[p->nb_cmd - 1], 100);
	if (p->fd_hd > 0)
		;
	else if (access(p->av[1], F_OK | R_OK) != 0)
	{
		ft_strcat(p->error[0], strerror(errno));
		ft_strcat(p->error[0], " : ");
		ft_strcat(p->error[0], p->av[1]);
	}
	if (p->fd_hd < 0)
		p->fd_args[1] = open(p->av[p->ac - 1], O_CREAT | O_TRUNC, 0777);
	else
		p->fd_args[1] = open(p->av[p->ac - 1], O_CREAT | O_APPEND, 0777);
	if (access(p->av[p->ac - 1], F_OK | W_OK) == 0)
	{
		if (p->fd_args[1] < 0)
			ft_put_error_outfile(p, strerror(errno));
		else
			close(p->fd_args[1]);
	}
	else
		ft_put_error_outfile(p, strerror(errno));
}

int	ft_valid_args(t_pipe *p)
{
	char	*d_pt;
	char	**pt;

	ft_check_files(p);
	d_pt = ft_get_path(p->env);
	pt = ft_split(&d_pt[5], ':');
	ft_parse_all(p, pt);
	free(pt);
	if (ft_is_error(p) == 1)
		return (1);
	ft_print_err_message(p);
	return (0);
}

void	ft_check_full_cmd_pt(t_pipe *p, char *tmp, int cmd)
{
	char	**tmp_cmd;
	int		i;

	if (ft_strncmp(tmp, "OK", 2) == 0)
		return ;
	if (ft_strchr(p->cmds[cmd].options[0], '/'))
	{
		tmp_cmd = ft_split(p->cmds[cmd].options[0], '/');
		i = len_path(tmp_cmd);
		p->cmds[cmd].bin_path = ft_strdup(p->cmds[cmd].options[0]);
		free(p->cmds[cmd].options[0]);
		p->cmds[cmd].options[0] = ft_strdup(tmp_cmd[i -1]);
		i = 0;
		while (tmp_cmd[i])
		{
			free(tmp_cmd[i]);
			i++;
		}
		free(tmp_cmd);
		if (access(p->cmds[cmd].bin_path, F_OK | X_OK) == 0)
			ft_bzero(p->error[cmd], 100);
	}
}
