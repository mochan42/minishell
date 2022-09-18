/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:08:40 by fakouyat          #+#    #+#             */
/*   Updated: 2022/08/29 15:08:40 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_is_error(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmd)
	{
		if (p->error[i][0] != '\0')
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_err_message(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmd)
	{
		if (p->error[i][0] != '\0')
			ft_printf("%s\n", p->error[i]);
		i++;
	}
}
