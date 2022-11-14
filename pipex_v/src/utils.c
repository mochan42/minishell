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

#include "../../minishell.h"
//#include "../inc/pipex.h"

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

void	ft_set_cmd_error_msg(t_prgm *vars, char **tmp, int cmd)
{
	if ((ft_strncmp(*tmp, "OK", 2) != 0)
		&& (vars->p.error[cmd][0] == 0) && vars->tok[cmd].built_in == 0)
	{
		ft_strcat(vars->p.error[cmd], "command not found : ");
		ft_strcat(vars->p.error[cmd], vars->tok[cmd].options[0]);
		ft_exit_code(127, 1);
	}
}

// must be rewritten 
void	ft_parse(t_prgm *vars, char **paths, int cmd)
{
	char	*tmp[3];
	int		i;

	i = 0;
	tmp[2] = "";
	while (paths[i])
	{
		if (vars->tok[cmd].options[0][0] != '/')
			tmp[0] = ft_strjoin("/", vars->tok[cmd].options[0]);
		else
			tmp[0] = ft_strjoin("../", vars->tok[cmd].options[0]);
		tmp[1] = ft_strjoin(paths[i], tmp[0]);
		if (access(tmp[1], F_OK | X_OK) == 0)
		{
			if (ft_strcmp(tmp[2], "Ok") == 0)
				free(vars->tok[cmd].bin);
			vars->tok[cmd].bin = ft_strdup(tmp[1]);
			tmp[2] = "OK";
		}
		free(tmp[0]);
		free(tmp[1]);
		i++;
	}
	ft_check_full_cmd_pt(vars, &tmp[2], cmd);
	ft_set_cmd_error_msg(vars, &tmp[2], cmd);
}

int	ft_assert_numeric(t_prgm *vars, int indice)
{
	int	j;

	j = 0;
	while (vars->tok[vars->p.child].options[indice][j])
	{
		if (is_numeric(
				vars->tok[vars->p.child].options[indice][j]) == 1)
		{
			printf("numeric argument required : %s\n",
				vars->tok[vars->p.child].options[indice]);
			ft_exit_code(255, 1);
			return (1);
		}
		j++;
	}
	return (0);
}
