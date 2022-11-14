/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:05:31 by mochan            #+#    #+#             */
/*   Updated: 2022/11/15 00:18:28 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	extract_ds_vars_helper(t_prgm *v)
{
	v->d_v = malloc(sizeof(char *) * (v->ct1[2]));
	if (!v->d_v)
	{
		free(v->d_v);
		return ;
	}
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
			while (v->tmp[v->ct1[1]] != '\0')
			{
				if (!ft_isalpha(v->tmp[v->ct1[1]]) && 
					v->tmp[v->ct1[1]] != '_' && v->tmp[v->ct1[1]] != '$')
				{
					v->ct1[1] += 1;
					break ;
				}
				if (v->tmp[v->ct1[1]] == '$')
					break ;
				v->ct1[1] += 1;
				if (v->tmp[v->ct1[1]] != '\0' && !ft_isalpha(v->tmp[v->ct1[1]]))
					break ;
			}
			if (v->ct1[1] - v->ct1[3] >= 1)
			{
				v->d_v[v->ct1[5]] = ft_substr(v->tmp, v->ct1[3], v->ct1[1] - v->ct1[3]);
				v->ct1[5] += 1;
			}
		}
		else
			v->ct1[1] += 1;
	}
}

void	translate_var_helper(t_prgm *v, t_env *tp_nd, int flag)
{
	int	i;

	while (tp_nd != NULL)
	{
		if (ft_strcmp(v->d_v[v->ct1[6]] + 1, tp_nd->key) == 0)
		{
			if (*tp_nd->value == '\0')
				break;
			ft_str_replace(&v->tok[v->ct1[0]].t_str,
				v->d_v[v->ct1[6]], tp_nd->value,
				v->tok[v->ct1[0]].rf_d[v->ct1[6]]);
			flag = 1;
			break ;
		}
		tp_nd = tp_nd->next;
	}
	if (flag == 0 && ft_strcmp(v->d_v[v->ct1[6]], "$?") == 0)
	{
		ft_str_replace(&v->tok[v->ct1[0]].t_str, v->d_v[v->ct1[6]],
		 	ft_itoa(g_exit_code),
			v->tok[v->ct1[0]].rf_d[v->ct1[6]]);
			i = 1;
		while(v->ct1[6] + i < v->ct1[2])
		{
			v->tok[v->ct1[0]].rf_d[v->ct1[6] + i] -= 2;
			i++;
		}
	}
	else if (flag == 0)
	{
		ft_str_replace(&v->tok[v->ct1[0]].t_str, v->d_v[v->ct1[6]], "",
		v->tok[v->ct1[0]].rf_d[v->ct1[6]]);
		i = 1;
		while(v->ct1[6] + i < v->ct1[2])
		{
			v->tok[v->ct1[0]].rf_d[v->ct1[6] + i] -= ft_strlen(v->d_v[v->ct1[6]]);
			i++;
		}
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
		if (expand_ds(v->tok[v->ct1[0]].t_str_og,
			v->tok[v->ct1[0]].rf_d[v->ct1[6]]) == 1)
				translate_var_helper(v, tp_nd, flag);
		v->ct1[6] += 1;
	}
}
