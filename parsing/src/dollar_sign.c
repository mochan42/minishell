/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:17:57 by mochan            #+#    #+#             */
/*   Updated: 2022/11/15 00:00:42 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	free_dollar_sign(t_prgm *v)
{
	free(v->tmp);
	free(v->d_v);
}

/* int		i; //ct1[0] : counter to go through each token (token = string 
within pipes)
int		j; //ct1[1] : counter to go through each char of each token
int		nb_dlr_sign_token; //ct1[2] : counter for number of dollar sign
 for each token
int		start; //ct1[3] : counter for start of string to copy used
 in ft_substr
int		len; //ct1[4] : length of a string to copy used in ft_substr
int		index; //ct1[5] : counter for each string of the array of strings
*/
void	interpret_dollar_sign(t_prgm *v)
{
	v->ct1[0] = 0;
	while (v->ct1[0] < v->pipe_ct)
	{
		v->ct1[2] = cnt_dlr(v->tok[v->ct1[0]].t_str);
		if (v->ct1[2] > 0)
		{
			v->tok[v->ct1[0]].rf_d = malloc(sizeof(int) * (v->ct1[2]));
			extract_ds_vars(v);
			translate_var(v);
		}
		v->ct1[0] += 1;
	}
}
