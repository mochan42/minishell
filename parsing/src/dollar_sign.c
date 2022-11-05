/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:17:57 by mochan            #+#    #+#             */
/*   Updated: 2022/11/05 21:25:56 by mochan           ###   ########.fr       */
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
		printf("token [%d]: v->array_concat[%d] :%s\n", v->ct1[0], v->ct1[5], v->array_concat[v->ct1[5]]);
		v->ct1[5]++;
	}
}

void	concatenate_strings(t_prgm *v)
{
	char	*res;

	concatenate_strings_helper_1(v);
	// v->ct1[5] = 0;
	// while (v->ct1[5] < v->ct1[2])
	// {
	// 	v->ct1[5]++;
	// }
	// printf("v->ct1[5] = %d\n", v->ct1[5]++);
	if (v->array_concat[0] != NULL)
	{
		printf("\ttoken[%d] HERE 0 \n", v->ct1[0]);
		res = ft_strdup(v->array_concat[0]);
		printf("\ttoken[%d] res HERE 0 :%s\n", v->ct1[0], res);
	}
	v->ct1[5] = 1;
	while (v->ct1[5] < v->ct1[2])
	{
		printf("\ttoken[%d] HERE %d \n", v->ct1[0], v->ct1[5]);
		res = ft_concat(res, v->array_concat[v->ct1[5]]);
		printf("\ttoken[%d] res HERE %d :%s\n", v->ct1[0], v->ct1[5], res);
		v->ct1[5]++;
	}
	printf("res - 1 :%s\n", res);
	if (v->array_no_ds[v->ct1[2]] != NULL)
	{
		printf("\ttoken[%d] array_no_ds[%d] :%s\n", v->ct1[0], v->ct1[2], v->array_no_ds[v->ct1[2]]);
		res = ft_concat(res, v->array_no_ds[v->ct1[2]]);
	}
	printf("res - 2 :%s\n", res);
	free(v->tokens[v->ct1[0]].cmd);
	v->tokens[v->ct1[0]].cmd = ft_strdup(res);
	printf("vars->tokens[%d].cmd :%s\n", v->ct1[0], v->tokens[v->ct1[0]].cmd);
	free(res);
	printf("token [%d] -  HERE\n", v->ct1[0]);
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
void	ids_cmd_opt_arg(t_prgm *v)
{
	v->ct1[0] = 0;
	while (v->ct1[0] < v->pipe_ct + 1)
	{
		if ((cnt_dquotes(v->tokens[v->ct1[0]].cmd) % 2 == 1) || \
			(cnt_squotes(v->tokens[v->ct1[0]].cmd) % 2 == 1))
			err_msg_quotes_not_closed();
		v->ct1[2] = cnt_dlr(v->tokens[v->ct1[0]].cmd);
		// printf("\nnb_dlr_sign_token %d= %d\n", v->ct1[0], v->ct1[2]);
		if (v->ct1[2] > 0)
		{
			extract_ds_vars(v);
			// printf("\n");
			translate_var(v);
			printf("v->tokens[%d].cmd :%s\n", v->ct1[0], v->tokens[v->ct1[0]].cmd);
			// printf("\n");
			// extract_string_no_ds(v);
			// concatenate_strings(v);
			// free_dollar_sign(v);
		}
		v->ct1[0]++;
	}
}

void	interpret_dollar_sign(t_prgm *vars)
{
	ids_cmd_opt_arg(vars);
	vars->i = 0;
	while (vars->i < vars->pipe_ct + 1)
	{
		printf("\tCHECK\t: vars->tokens[%d].cmd :%s\n", vars->i, vars->tokens[vars->i].cmd);
		vars->i++;
	}
}
