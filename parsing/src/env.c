/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:10:35 by mochan            #+#    #+#             */
/*   Updated: 2022/10/24 18:14:02 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_env_init(t_prgm *vars)
{
	int	i;
	int	env_size;

	i = 0;
	env_size = 0;
	while (vars->env[i] != NULL)
	{
		env_size++;
		i++;
	}
	printf("env_size = %d\n\n", env_size);
	vars->res = malloc(sizeof(char **) * (env_size + 1));
	vars->keys = malloc(sizeof(char *) * (env_size + 1));
	vars->values = malloc(sizeof(char *) * (env_size + 1));
	vars->res[env_size] = NULL;
	vars->keys[env_size] = NULL;
	vars->values[env_size] = NULL;
}

void	init_env_split(t_prgm *vars)
{
	int	i;

	i = 0;
	while (vars->array_tmp[i] != NULL)
	{
		vars->res[i] = ft_split(vars->array_tmp[i], '=');
		vars->keys[i] = vars->res[i][0];
		vars->values[i] = vars->res[i][1];
		i++;
	}
}

t_env	*init_env(t_prgm *vars)
{
	t_env	*head;
	int		i;
	t_env	*temporary;

	head = NULL;
	vars->array_tmp = vars->env;
	init_env_init(vars);
	init_env_split(vars);
	i = 0;
	while (vars->keys[i] != NULL)
	{
		node_add_back(&head, new_node(vars->keys[i]));
		i++;
	}
	i = 0;
	temporary = head;
	while (temporary != NULL)
	{
		temporary->value = vars->values[i];
		i++;
		temporary = temporary->next;
	}
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

	temporary = head;
	while (temporary != NULL)
	{
		if (temporary->value)
			printf("%s=%s\n", temporary->key, temporary->value);
		else
			printf("%s\n", temporary->key);
		temporary = temporary->next;
	}
	printf("\n");
}
