/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:10:35 by mochan            #+#    #+#             */
/*   Updated: 2022/09/30 12:15:46 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../minishell.h"
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
void	node_add_back(t_env **node, t_env *new)
{
	t_env	*p;

	if (*node == NULL)
		*node = new;
	else
	{
		p = last_node(*node);
		p->next = new;
	}
}

int	ft_list_size(t_env *begin_list)
{
	t_env *tmp;
	int counter;

	counter = 0;
	tmp = begin_list;
	while(tmp != NULL)
	{
		tmp = tmp->next;
		counter++;
	}
	return (counter);
}


t_env	*init_env(t_prgm *vars)
{
	t_env	*head;
	int		i;
	char	**tmp;
	char	**keys;
	char	**values;
	int		env_size;
	char	***res;
	t_env	*temporary;

	i = 0;
	head = NULL;// do not move this line down otherwise the program wont work.
	tmp = vars->env;// do not move this line down otherwise the program wont work.
	env_size = 0;
	while (*vars->env != NULL)
	{
		env_size++;
		vars->env++;
	}
	printf("env_size = %d\n\n", env_size);
	res = malloc(sizeof(char **) * (env_size + 1));
	keys = malloc(sizeof(char *) * (env_size + 1));
	values = malloc(sizeof(char *) * (env_size + 1));
	res[env_size] = NULL;
	keys[env_size] = NULL;
	values[env_size] = NULL;
	i = 0;
	while (tmp[i] != NULL)
	{
		res[i] = ft_split(tmp[i], '=');
		keys[i] = res[i][0];
		values[i] = res[i][1];
		i++;
	}
	i = 0;
	while (keys[i] != NULL)
	{
		node_add_back(&head, new_node(keys[i]));
		i++;
	}
	i = 0;
	temporary = head;
	while (temporary != NULL)
	{
		temporary->value = values[i];
		i++;
		temporary = temporary->next;
	}
	// free(tmp); do not forget to free tmp but when? if uncomment this line, prgm will abort.
	return (head);
}

/* printlist:
*	print the values of the nodes of a linked list.
*	useful function to check if the linked list is created, sorted, etc.
*	not required for the project.
*/
void	printlist(t_env *head)
{
	t_env	*temporary;
	int		i;

	i = 0;
	temporary = head;
	while (temporary != NULL)
	{
		printf("key[%d]		: %s\n", i, temporary->key);
		printf("value[%d]	: %s\n", i, temporary->value);
		i++;
		temporary = temporary->next;
	}
	printf("\n");
}


// void	print_original_env(t_prgm *vars)
// {
// 	int	counter;

// 	while(vars->env)
// 	{
		 
// 	}
// }