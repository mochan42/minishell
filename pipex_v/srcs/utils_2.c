/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 04:37:57 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/21 04:37:57 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_init_pipe(t_pipe *p, int argc, char **argv, char **envp)
{
	p->fd_args[0] = 0;
	p->fd_args[1] = 0;
	p->nb_cmd = argc - 3;
	p->ac = argc;
	p->av = argv;
	p->child = 0;
	p->env = envp;
	p->tmp_file = (char *)ft_calloc(sizeof(char), 1);
	p->fd_hd = -1;
}

void	free_p(t_pipe *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < p->nb_cmd)
	{
		j = 0;
		while (p->cmds[i].options[j])
		{
			free(p->cmds[i].options[j]);
			j++;
		}
		free(p->cmds[i].bin_path);
		free(p->cmds[i].options);
		i++;
	}
}

int	len_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		i++;
	}
	return (i);
}

void	ft_parse_all(t_pipe *p, char **pt)
{
	int	i;

	i = 0;
	while (i < p->nb_cmd)
	{
		if (p->fd_hd < 0)
			p->cmds[i].options = ft_split(p->av[2 + i], ' ');
		else
			p->cmds[i].options = ft_split(p->av[3 + i], ' ');
		ft_parse(p, pt, i);
		i++;
	}
}
