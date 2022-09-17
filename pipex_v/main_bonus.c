/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:03:26 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/01 00:03:26 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

	ft_init_pipe(&p, argc, argv, envp);
	if (ft_valid_nb_args_bonus(argc) == 0)
		exit(0);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		ft_here_doc(&p);
	if (ft_valid_args(&p) == 0)
		exit(0);
	ft_generate_p(&p);
	while (p.child < p.nb_cmd)
	{
		p.pid[p.child] = fork();
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
