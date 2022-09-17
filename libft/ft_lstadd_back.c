/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:42:29 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/13 16:23:32 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
