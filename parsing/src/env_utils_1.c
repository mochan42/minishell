/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:17:39 by mochan            #+#    #+#             */
/*   Updated: 2022/11/08 20:57:33 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

/* *last_node:
*	Return the last node of a linked list.
*/
t_env	*last_node(t_env *node)
{
	if (node == NULL)
		return (NULL);
	if (node->next == NULL)
		return (node);
	else
		return (last_node(node->next));
}

/* *new_node:
*	Create a new node but it is not linked.
*/
t_env	*new_node(char *key)
{
	t_env	*p;

	p = (t_env *)malloc(sizeof(t_env));
	if (!p)
		return (NULL);
	p->value = NULL;
	p->next = NULL;
	p->prev = NULL;
	p->key = key;
	return (p);
}

/* *new_node:
*	Create a new node at the end of the linked list.
*/
void	node_add_back(t_env **node, t_env *n_node)
{
	t_env	*p;

	if (*node == NULL)
		*node = n_node;
	else
	{
		p = last_node(*node);
		p->next = n_node;
	}
}

int	ft_list_size(t_env *begin_list)
{
	t_env	*tmp;
	int		counter;

	counter = 0;
	tmp = begin_list;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		counter++;
	}
	return (counter);
}

