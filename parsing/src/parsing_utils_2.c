/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:07:35 by mochan            #+#    #+#             */
/*   Updated: 2022/11/12 21:55:34 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	ft_only_file_in(t_prgm *vars, int i)
{
	int	ct_red;

	ct_red = 0;
	while (vars->tok[i].infile[ct_red] != NULL)
	{
		if (vars->tok[i].in[ct_red] == IN_HEREDOC)
			ft_here_doc(vars, i, ct_red);
		else if (access(vars->tok[i].infile[ct_red], F_OK) != 0)
			printf("No such file directory : %s\n",
				vars->tok[i].infile[ct_red]);
		ct_red++;
		vars->tok_error += 1;
	}
}

void	ft_only_file_out(t_prgm *vars, int i)
{
	int	ct_red;

	ct_red = 0;
	while (vars->tok[i].outfile[ct_red] != NULL)
	{
		if (vars->tok[i].out[ct_red] == OUT_REDIRECT
			&& access(vars->tok[i].outfile[ct_red], F_OK) == 0)
		{
			unlink(vars->tok[i].outfile[ct_red]);
			open(vars->tok[i].outfile[ct_red], O_RDWR | O_CREAT, 0666);
		}
		ct_red++;
		vars->tok_error += 1;
	}
}

int	ft_check_ex_options(t_prgm *vars)
{
	int	i;

	i = 1;
	while (vars->tok[vars->p.child].options[i])
	{
		if (i > 1)
		{
			printf("too many arguments\n");
			ft_exit_code(1, 1);
			return (1);
		}
		if (ft_assert_numeric(vars, i) == 1)
			return (1);
		i++;
	}
	return (0);
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

int	is_numeric(char c)
{
	if (!(c >= '0' && c <= '9') && c != '-')
		return (1);
	return (0);
}
