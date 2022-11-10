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
	while (i < vars->pipe_ct + 1)
	{
		j = 0;
		while (vars->tokens[i].options[j])
		{
			free(vars->tokens[i].options[j]);
			j++;
		}
		if (vars->tokens[i].bin)
			free(vars->tokens[i].bin);
		free(vars->tokens[i].options);
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

void	ft_only_file_in(t_prgm *vars, int i)
{
	int	ct_red;

	ct_red = 0;
	while (vars->tokens[i].infile[ct_red] != NULL)
	{
		if (vars->tokens[i].in[ct_red] == IN_HEREDOC)
			ft_here_doc(vars, i, ct_red);
		else if (access(vars->tokens[i].infile[ct_red], F_OK) != 0)
			printf("No such file directory : %s\n",
				vars->tokens[i].infile[ct_red]);
		ct_red++;
		vars->tok_error += 1;
	}
}

void	ft_only_file_out(t_prgm *vars, int i)
{
	int	ct_red;

	ct_red = 0;
	while (vars->tokens[i].outfile[ct_red] != NULL)
	{
		if (vars->tokens[i].out[ct_red] == OUT_REDIRECT
			&& access(vars->tokens[i].outfile[ct_red], F_OK) == 0)
		{
			unlink(vars->tokens[i].outfile[ct_red]);
			open(vars->tokens[i].outfile[ct_red], O_RDWR | O_CREAT, 0666);
		}
		ct_red++;
		vars->tok_error += 1;
	}
}

void	ft_is_builtins_cmd(t_prgm *vars, int i)
{
	int	j;

	j = 0;
	while (j < 7)
	{
		if (ft_strcmp(vars->tokens[i].options[0], vars->builts[j]) == 0)
		{
			vars->tokens[i].built_in = 1;
			break ;
		}
		j++;
	}
}

int	ft_is_error_options(t_prgm *vars, int i, int j)
{
	if (vars->tokens[i].options[j] == NULL)
	{
		vars->tok_error = 1;
		if (vars->tokens[i].infile != NULL)
			ft_only_file_in(vars, i);
		if (vars->tokens[i].outfile != NULL)
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
	while (i < vars->pipe_ct + 1)
	{
		z = 0;
		vars->tokens[i].options = ft_split_cmd(vars->tokens[i].cmd, ' ');
		if (ft_is_error_options(vars, i, z) == 1)
			return ;
		while (vars->tokens[i].options[z])
		{
			tmp = trim_quotes(vars->tokens[i].options[z]);
			free(vars->tokens[i].options[z]);
			vars->tokens[i].options[z] = ft_strdup(tmp);
			free(tmp);
			z++;
		}
		ft_is_builtins_cmd(vars, i);
		ft_parse(vars, pt, i);
		i++;
	}
}
