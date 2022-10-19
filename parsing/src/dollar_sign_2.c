/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:05:31 by mochan            #+#    #+#             */
/*   Updated: 2022/10/19 20:32:48 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	extract_ds_vars_helper(t_prgm *v)
{
	v->array_ds_vars = malloc(sizeof(char *) * (v->ct1[2] + 1));
	v->array_ds_vars[v->ct1[2]] = NULL;
	v->tmp = ft_strdup(v->tokens[v->ct1[0]].cmd);
	v->ct1[1] = 0;
	v->ct1[5] = 0;
}

void	extract_ds_vars(t_prgm *v)
{
	extract_ds_vars_helper(v);
	while (v->tmp[v->ct1[1]] != '\0')
	{
		if (v->tmp[v->ct1[1]] == '$')
		{
			v->ct1[1]++;
			v->ct1[3] = v->ct1[1];
			v->ct1[4] = 0;
			while ((v->tmp[v->ct1[1]] >= 'a' && v->tmp[v->ct1[1]] <= 'z') \
				|| (v->tmp[v->ct1[1]] >= 'A' && v->tmp[v->ct1[1]] <= 'Z') \
				|| (v->tmp[v->ct1[1]] >= '0' && v->tmp[v->ct1[1]] <= '9'))
			{
				v->ct1[1]++;
				v->ct1[4]++;
			}
			v->array_ds_vars[v->ct1[5]] = ft_substr(v->tmp, v->ct1[3], \
				v->ct1[4]);
			printf("token[%d] array_ds_vars (raw)[%d] :%s\n", v->ct1[0], v->ct1[5], v->array_ds_vars[v->ct1[5]]);
			v->ct1[5]++;
		}
		else
			v->ct1[1]++;
	}
}

void	translate_var(t_prgm *v)
{
	t_env	*tmp_node;

	v->ct1[1] = 0;
	while (v->ct1[1] < v->ct1[2])
	{
		tmp_node = v->env_head;
		while (tmp_node != NULL)
		{
			if (ft_strncmp(v->array_ds_vars[v->ct1[1]], tmp_node->key, \
				ft_strlen(v->array_ds_vars[v->ct1[1]])) == 0)
			{
				free(v->array_ds_vars[v->ct1[1]]);
				v->array_ds_vars[v->ct1[1]] = \
					ft_strdup(tmp_node->value);
			}
			tmp_node = tmp_node->next;
		}
		printf("token[%d] array_ds_vars (translated)[%d]:%s\n", v->ct1[0], v->ct1[1], v->array_ds_vars[v->ct1[1]]);
		v->ct1[1]++;
	}
}

void	extract_string_no_ds_helper(t_prgm *v)
{
	v->array_no_ds = malloc(sizeof(char *) * (v->ct1[2] + 2));
	v->array_no_ds[v->ct1[2] + 1] = NULL;
	v->ct1[1] = 0;
	v->ct1[5] = 0;
}

void	extract_string_no_ds(t_prgm *v)
{
	extract_string_no_ds_helper(v);
	while (v->tmp[v->ct1[1]] != '\0' && v->ct1[5] < (v->ct1[2] + 1))
	{
		if (v->tmp[v->ct1[1]] == '$')
		{
			v->ct1[1]++;
			while ((v->tmp[v->ct1[1]] >= 'a' && v->tmp[v->ct1[1]] <= 'z') \
				|| (v->tmp[v->ct1[1]] >= 'A' && v->tmp[v->ct1[1]] <= 'Z') \
				|| (v->tmp[v->ct1[1]] >= '0' && v->tmp[v->ct1[1]] <= '9'))
				v->ct1[1]++;
		}
		else
		{
			v->ct1[3] = v->ct1[1];
			v->ct1[4] = 0;
			while (v->tmp[v->ct1[1]] != '$')
			{
				v->ct1[1]++;
				v->ct1[4]++;
			}
			v->array_no_ds[v->ct1[5]] = \
				ft_substr(v->tmp, v->ct1[3], v->ct1[4]);
			printf("token[%d] array_no_ds[%d] :%s\n", v->ct1[0], v->ct1[5], v->array_no_ds[v->ct1[5]]);
			v->ct1[5]++;
		}
	}
}
