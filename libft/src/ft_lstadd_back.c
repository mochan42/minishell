/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:42:29 by fakouyat          #+#    #+#             */
/*   Updated: 2022/09/25 15:27:52 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	head = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (head)
	{
		if (head->next == NULL)
		{
			head->next = new;
			break ;
		}
		head = head->next;
	}
}
