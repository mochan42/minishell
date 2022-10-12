/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:49:17 by mochan            #+#    #+#             */
/*   Updated: 2022/09/30 18:49:52 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	is_pipe(char c)
{
	int	i;

	if (c == '|')
		i = 1;
	else
		i = 0;
	return (i);
}

int	is_double_quote(char c)
{
	int	i;

	if (c == '\"')
		i = 1;
	else
		i = 0;
	return (i);
}
