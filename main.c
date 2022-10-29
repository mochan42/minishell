/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 23:02:44 by fakouyat          #+#    #+#             */
/*   Updated: 2022/10/16 23:02:44 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include "./parsing/inc/parser.h"

int	main(int ac, char **av, char **env)
{
	t_prgm	*ms;

	(void)ac;
	(void)av;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, new_prompt);
	ms = malloc(sizeof(t_prgm) * 1);
	ms->env = env;
	init(ms);
	input_loop(ms);
	return (0);
}
