/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:56:23 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/22 23:56:23 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
int	input_loop(t_prgm *vars);

int	main(int ac, char **av, char **env)
{
	t_prgm	*ms;

	(void)ac;
	(void)av;
	ms = malloc(sizeof(t_prgm) * 1);
	ms->env = env;
	initialise_ms(ms);
	// print_dir();
	//input_loop(ms);
	//free_stuff(ms);
	return (0);
}