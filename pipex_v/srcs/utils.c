/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:43:16 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/16 15:43:16 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen(envp[i]))
			&& (envp[i][0] == 'P'))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

void	ft_set_cmd_error_msg(t_pipe *p, char **tmp, int cmd)
{
	if ((ft_strncmp(*tmp, "OK", 2) != 0)
		&& (p->error[cmd][0] == 0))
	{
		ft_strcat(p->error[cmd], "command not found : ");
		ft_strcat(p->error[cmd], p->av[cmd + 2]);
	}
}

void	ft_parse(t_pipe *p, char **paths, int cmd)
{
	char	*tmp[3];
	int		i;

	i = 0;
	tmp[2] = "";
	while (paths[i])
	{
		if (p->cmds[cmd].options[0][0] != '/')
			tmp[0] = ft_strjoin("/", p->cmds[cmd].options[0]);
		else
			tmp[0] = ft_strjoin("../", p->cmds[cmd].options[0]);
		tmp[1] = ft_strjoin(paths[i], tmp[0]);
		if (access(tmp[1], F_OK | X_OK) == 0)
		{
			p->cmds[cmd].bin_path = ft_strdup(tmp[1]);
			tmp[2] = "OK";
		}
		free(tmp[0]);
		free(tmp[1]);
		i++;
	}
	ft_set_cmd_error_msg(p, &tmp[2], cmd);
	ft_check_full_cmd_pt(p, tmp[2], cmd);
}

void	ft_put_error_outfile(t_pipe *p, char *error)
{
	ft_strcat(p->error[1], error);
	ft_strcat(p->error[1], " : ");
	ft_strcat(p->error[1], p->av[p->ac - 1]);
}
