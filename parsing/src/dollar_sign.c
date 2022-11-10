/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:17:57 by mochan            #+#    #+#             */
/*   Updated: 2022/11/10 12:50:10 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	concatenate_strings_helper_1(t_prgm *v)
{
	v->ct1[5] = 0;
	v->array_concat = malloc(sizeof(char *) * (v->ct1[2] + 2));
	if (!v->array_concat)
		return ;
	v->array_concat[v->ct1[2] + 1] = NULL;
	while (v->ct1[5] < v->ct1[2])
	{
		v->array_concat[v->ct1[5]] = ft_concat(v->array_no_ds[v->ct1[5]], \
			v->array_ds_vars[v->ct1[5]]);
		v->ct1[5]++;
	}
}

void	concatenate_strings(t_prgm *v)
{
	char	*res;

	concatenate_strings_helper_1(v);
	if (v->array_concat[0] != NULL)
		res = ft_strdup(v->array_concat[0]);
	v->ct1[5] = 1;
	while (v->ct1[5] < v->ct1[2])
	{
		res = ft_concat(res, v->array_concat[v->ct1[5]]);
		v->ct1[5]++;
	}
	if (v->array_no_ds[v->ct1[2]] != NULL)
		res = ft_concat(res, v->array_no_ds[v->ct1[2]]);
	free(v->tokens[v->ct1[0]].cmd);
	v->tokens[v->ct1[0]].cmd = ft_strdup(res);
	free(res);
}

void	free_dollar_sign(t_prgm *v)
{
	free(v->tmp);
	free(v->array_ds_vars);
	free(v->array_no_ds);
	free(v->array_concat);
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
//ct1[6] : counter to go through each env variable to translate the dollar sign variable.
*/
void	interpret_dollar_sign(t_prgm *v)
{
	v->ct1[0] = 0;
	while (v->ct1[0] < v->pipe_ct + 1)
	{
		v->ct1[2] = cnt_dlr(v->tokens[v->ct1[0]].t_str);
		v->tokens[v->ct1[0]].ref_dollar = malloc(sizeof(int) * v->ct1[2]);
		if (v->ct1[2] > 0)
		{
			extract_ds_vars(v);
			translate_var(v);
		}
		v->ct1[0]++;
	}
}

// void	interpret_dollar_sign(t_prgm *vars)
// {
// 	ids_cmd_opt_arg(vars);
// 	vars->i = 0;
// 	while (vars->i < vars->pipe_ct + 1)
// 	{
// 		vars->i++;
// 	}
// }
