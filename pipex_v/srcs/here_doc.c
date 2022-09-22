/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 23:40:43 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/17 23:40:43 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// void	ft_here_doc(t_prgm *vars)
// {
// 	char	*tmp_read;

// 	p->fd_hd = open("tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
// 	//p->nb_cmd -= 1;
// 	while (1)
// 	{
// 		tmp_read = get_next_line(0);
// 		if (ft_strncmp(vars->av[2], tmp_read, ft_strlen(p->av[2])) == 0)
// 		{
// 			free(tmp_read);
// 			break ;
// 		}
// 		write(p->fd_hd, tmp_read, ft_strlen(tmp_read));
// 		free(tmp_read);
// 	}
// 	close(p->fd_hd);
// 	p->fd_hd = open("tmp.txt", O_RDONLY);
// 	unlink("tmp.txt");
// }
