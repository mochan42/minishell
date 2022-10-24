/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:53:30 by mochan            #+#    #+#             */
/*   Updated: 2022/10/24 17:55:51 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	interpret_quotes(t_prgm *vars)
{
	int	i;

	i = 0;
	printf("==========INTERPRET QUOTES COA==============\n");
	while (i < vars->pipe_ct + 1)
	{
		printf("vars->tokens[%d].cmd :%s\n", i, vars->tokens[i].cmd);
		i++;
	}
}