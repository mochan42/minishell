/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:05:31 by mochan            #+#    #+#             */
/*   Updated: 2022/11/16 01:32:33 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	extract_ds_vars_helper(t_prgm *v)
{
	if (v->d_v != NULL)
		free_2_pt(v->d_v);
	v->d_v = malloc(sizeof(char *) * (v->ct1[2]));
	if (!v->d_v)
	{
		free(v->d_v);
		return ;
	}
	if (v->tmp != NULL)
		free(v->tmp);
	v->tmp = ft_strdup(v->tok[v->ct1[0]].t_str);
	v->ct1[1] = 0;
	v->ct1[5] = 0;
}

void	extract_ds_vars(t_prgm *v)
{
	extract_ds_vars_helper(v);
	while (v->tmp[v->ct1[1]] != '\0' && (v->ct1[5] < v->ct1[2]))
	{
		if (v->tmp[v->ct1[1]] == '$')
		{
			v->ct1[3] = v->ct1[1];
			v->tok[v->ct1[0]].rf_d[v->ct1[5]] = v->ct1[1];
			v->ct1[1] += 1;
			loop_find_var(v);
			add_var(v);
		}
		else
			v->ct1[1] += 1;
	}
}

void	translate_var_helper(t_prgm *v, t_env *tp_nd, int flag)
{
	while (tp_nd != NULL)
	{
		if (ft_strcmp(v->d_v[v->ct1[6]] + 1, tp_nd->key) == 0)
		{
			if (*tp_nd->value == '\0')
				break ;
			update_expand_cmd(v, tp_nd->value);
			flag = 1;
			break ;
		}
		tp_nd = tp_nd->next;
	}
	if (flag == 0 && ft_strcmp(v->d_v[v->ct1[6]], "$?") == 0)
	{
		update_expand_cmd(v, ft_itoa(g_exit_code));
		ft_adapt_ref(v, 2);
	}
	else if (flag == 0)
	{
		update_expand_cmd(v, "");
		ft_adapt_ref(v, ft_strlen(v->d_v[v->ct1[6]]));
	}
}

void	translate_var(t_prgm *v)
{
	t_env	*tp_nd;
	int		flag;

	v->ct1[6] = 0;
	flag = 0;
	while (v->ct1[6] < v->ct1[2])
	{
		tp_nd = v->env_head;
		if (expand_ds(ft_strdup(v->tok[v->ct1[0]].t_str_og),
				v->tok[v->ct1[0]].rf_d[v->ct1[6]]) == 1)
			translate_var_helper(v, tp_nd, flag);
		v->ct1[6] += 1;
	}
}
