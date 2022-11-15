/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:03:24 by fakouyat          #+#    #+#             */
/*   Updated: 2022/11/16 00:03:24 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	add_var(t_prgm *v)
{
	if (v->ct1[1] - v->ct1[3] >= 1)
	{
		v->d_v[v->ct1[5]] = ft_substr(v->tmp, v->ct1[3], v->ct1[1] - v->ct1[3]);
		v->ct1[5] += 1;
	}
	else if (v->ct1[1] - v->ct1[3] == 1)
	{
		v->d_v[v->ct1[5]] = ft_strdup("$");
		v->ct1[5] += 1;
	}
}

void	loop_find_var(t_prgm *v)
{
	while (v->tmp[v->ct1[1]] != '\0')
	{
		if (!ft_isalpha(v->tmp[v->ct1[1]])
			&& v->tmp[v->ct1[1]] != '_' && v->tmp[v->ct1[1]] != '$')
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
}

void	ft_adapt_ref(t_prgm *v)
{
	int	i;

	i = 1;
	while (v->ct1[6] + i < v->ct1[2])
	{
		v->tok[v->ct1[0]].rf_d[v->ct1[6] + i] -= 2;
		i++;
	}
}

void	update_expand_cmd(t_prgm *v, char *value)
{
	if (*value == '\0' && ft_strcmp(v->d_v[v->ct1[6]], "$") == 0)
		value = "$";
	ft_str_replace(&v->tok[v->ct1[0]].t_str, v->d_v[v->ct1[6]], value,
		v->tok[v->ct1[0]].rf_d[v->ct1[6]]);
}
