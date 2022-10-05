/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:54:54 by fakouyat          #+#    #+#             */
/*   Updated: 2022/10/01 13:54:54 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* find the appropriate command, then execut it
* cd, echo, export, unset, pwd, env, exit
*/
void	ft_cd(t_prgm *vars)
{
	char repo[MAX_LEN_DIR];
	int fd;

	fd = open("cwd.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (!vars->tokens[vars->p.child].options[1])
		chdir("");
	else
		chdir(vars->tokens[vars->p.child].options[1]);
	ft_bzero(vars->curr_dir, MAX_LEN_DIR);
	ft_strlcpy(vars->curr_dir, getcwd(repo, MAX_LEN_DIR), MAX_LEN_DIR);
	write(fd, vars->curr_dir, ft_strlen(vars->curr_dir));
	close(fd);
}

void	ft_pwd(t_prgm *vars)
{
    printf("\033[0;34m%s:\n", vars->curr_dir);
    printf("\033[0;37m");
}

// void	ft_env(t_prgm *vars)
// {

// }

void	execbuilt_in(t_prgm *vars)
{
    if (ft_strncmp(vars->tokens[vars->p.child].options[0], "cd", 2) == 0)
        ft_cd(vars);
    else if (ft_strncmp(vars->tokens[vars->p.child].options[0], "pwd", 3) == 0)
        ft_pwd(vars);
    exit(0);
}

