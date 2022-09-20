/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:33:54 by mochan            #+#    #+#             */
/*   Updated: 2022/09/19 09:38:44 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char	*find_path_in_envp(t_prgm vars)
// {
// 	char	*path_name;
// 	char	*path_env;
// 	char	*test;
// 	int		len_path_env;

// 	path_name = "PATH=";
// 	path_env = NULL;
// 	test = NULL;
// 	len_path_env = 0;
// 	while (*(vars.env))
// 	{
// 		test = ft_strnstr(*(vars.env), path_name, 5);
// 		if (test)
// 		{
// 			path_env = *(vars.env);
// 			len_path_env = ft_strlen(path_env);
// 			break ;
// 		}
// 		else
// 			(*(vars.env))++;
// 	}
// 	path_env = ft_substr(path_env, 5, len_path_env);
// 	return (path_env);
// }

void	init(t_prgm *vars)
{
	vars->pipe_ct = 0;
}
