/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 22:43:32 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/15 22:43:32 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

	ft_init_pipe(&p, argc, argv, envp);
	if (ft_valid_nb_args(argc) == 0)
		exit(0);
	if (ft_valid_args(&p) == 0)
		exit(0);
	ft_generate_p(&p);
	while (p.child < p.nb_cmd)
	{
		p.pid[p.child] = fork();
		if (p.pid[p.child] < 0)
		{
			perror("Error fork ");
			exit(0);
		}
		if (p.pid[p.child] == 0)
		{
			ft_childs_process(&p);
			execve(p.cmds[p.child].bin_path, p.cmds[p.child].options, p.env);
		}
		p.child += 1;
	}
	ft_parent_process(&p);
	return (0);
}
