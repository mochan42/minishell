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

#include "../../minishell.h"

int	ft_valid_args(t_prgm *vars)
{
	char	*d_pt;
	char	**pt;

	d_pt = ft_get_path(vars->env);
	pt = ft_split(&d_pt[5], ':');
	ft_parse_all(vars, pt);
	free_2_pt(pt);
	if (ft_is_error(vars) == 1)
		return (1);
	return (0);
}

void	ft_check_full_cmd_pt(t_prgm *vars, char **tmp, int cmd)
{
	char	**tmp_cmd;
	int		i;

	if (ft_strncmp(*tmp, "OK", 2) == 0)
		return ;
	if (ft_strchr(vars->tokens[cmd].options[0], '/'))
	{
		tmp_cmd = ft_split(vars->tokens[cmd].options[0], '/');
		i = len_path(tmp_cmd);
		if (i == 0 || !tmp_cmd[0])
		{
			vars->tok_error = 1;
			return ;
		}
		vars->tokens[cmd].bin = ft_strdup(vars->tokens[cmd].options[0]);
		free(vars->tokens[cmd].options[0]);
		vars->tokens[cmd].options[0] = ft_strdup(tmp_cmd[i - 1]);
		i = 0;
		while (tmp_cmd[i])
		{
			free(tmp_cmd[i]);
			i++;
		}
		free(tmp_cmd);
		if (vars->tokens[cmd].bin && access(vars->tokens[cmd].bin,
				F_OK | X_OK) == 0)
			*tmp = "OK";
	}
}
