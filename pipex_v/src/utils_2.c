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

#include "../../minishell.h"

void	free_vars_p(t_prgm *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->pipe_ct)
	{
		j = 0;
		while (vars->tok[i].options[j])
		{
			free(vars->tok[i].options[j]);
			j++;
		}
		if (vars->tok[i].bin)
			free(vars->tok[i].bin);
		free(vars->tok[i].options);
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

void	ft_is_builtins_cmd(t_prgm *vars, int i)
{
	int	j;

	j = 0;
	while (j < 7)
	{
		if (ft_strcmp(vars->tok[i].options[0], vars->builts[j]) == 0)
		{
			vars->tok[i].built_in = 1;
			break ;
		}
		j++;
	}
}

int	ft_is_error_options(t_prgm *vars, int i, int j)
{
	if (vars->tok[i].options[j] == NULL)
	{
		vars->tok_error = 1;
		if (vars->tok[i].infile != NULL)
			ft_only_file_in(vars, i);
		if (vars->tok[i].outfile != NULL)
			ft_only_file_out(vars, i);
		return (1);
	}
	return (0);
}

void	ft_parse_all(t_prgm *vars, char **pt)
{
	int		i;
	int		z;
	char	*tmp;

	i = 0;
	while (i < vars->pipe_ct)
	{
		z = 0;
		vars->tok[i].options = ft_split_cmd(vars->tok[i].cmd, ' ');
		if (ft_is_error_options(vars, i, z) == 1)
			return ;
		while (vars->tok[i].options[z])
		{
			tmp = trim_quotes(vars->tok[i].options[z]);
			free(vars->tok[i].options[z]);
			vars->tok[i].options[z] = ft_strdup(tmp);
			free(tmp);
			z++;
		}
		ft_is_builtins_cmd(vars, i);
		ft_parse(vars, pt, i);
		i++;
	}
}
