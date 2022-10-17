/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochan <mochan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:17:57 by mochan            #+#    #+#             */
/*   Updated: 2022/10/17 21:30:34 by mochan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	count_dlr_sign(char *s)
{
	int	nb_dlr_sign;

	nb_dlr_sign = 0;
	if (!s)
		return (0);
	while (*s++)
	{
		if (*s == '$')
			nb_dlr_sign++;
	}
	return (nb_dlr_sign);
}

void	err_msg_quotes_not_closed(void)
{
	printf("Quotes not closed.\n");
	exit (0);
}

char	*ft_concat(char *str1, const char *str2)
{
	size_t	i;
	size_t	dst_str1;
	size_t	dst_str2;
	size_t	dst_ttl;
	char	*concatenated_str;

	dst_str1 = ft_strlen(str1);
	dst_str2 = ft_strlen(str2);
	dst_ttl = dst_str1 + dst_str2;
	concatenated_str = malloc(sizeof(char) * (dst_ttl + 1));
	ft_bzero(concatenated_str, dst_ttl);
	concatenated_str[dst_ttl] = '\0';
	i = 0;
	while (str1[i] != '\0' && i < dst_str1)
	{
		concatenated_str[i] = str1[i];
		i++;
	}
	i = 0;
	while (str2[i] != '\0' && i < dst_str2)
	{
		concatenated_str[dst_str1 + i] = str2[i];
		i++;
	}
	return (concatenated_str);
}


void	ids_cmd_opt_arg(t_prgm *vars)
{
	int		i;
	int		j;
	int		nb_dlr_sign_token;
	char	*tmp;
	char	**array_ds_vars;
	int		start;
	int		len;
	int		index;
	char	**array_no_ds;
	char	**array_concat;
	char	*res;
	// int		b_open_double_quote;
	// int		b_open_single_quote;

	i = 0;
	while (i < vars->pipe_ct + 1)
	{
		if ((count_double_quotes(vars->tokens[i].cmd) % 2 == 1) ||\
			(count_single_quotes(vars->tokens[i].cmd) % 2 == 1))
			err_msg_quotes_not_closed();
		nb_dlr_sign_token = count_dlr_sign(vars->tokens[i].cmd);
		printf("\nnb_dlr_sign_token %d= %d\n", i, nb_dlr_sign_token);
		if (nb_dlr_sign_token > 0)
		{
			array_ds_vars = malloc(sizeof(char *) * (nb_dlr_sign_token + 1));
			array_ds_vars[nb_dlr_sign_token] = NULL;
			tmp = ft_strdup(vars->tokens[i].cmd);
			j = 0;
			index = 0;
			while (tmp[j] != '\0')
			{
				if (tmp[j] == '$')
				{
					j++;
					start = j;
					len = 0;
					while ((tmp[j] >= 'a' && tmp[j] <= 'z') || (tmp[j] >= 'A' && tmp[j] <= 'Z') || (tmp[j] >= '0' && tmp[j] <= '9'))
					{
						j++;
						len++;
					}
					array_ds_vars[index] = ft_substr(tmp, start, len);
					printf("token[%d] array_ds_vars (raw)[%d] :%s\n", i, index, array_ds_vars[index]);
					index++;
				}
				else
					j++;
			}
			printf("\n");
			j = 0;
			while (j < nb_dlr_sign_token)
			{
				t_env *tmp_node;
				
				tmp_node = vars->env_head;
				while (tmp_node != NULL)
				{
					if (ft_strncmp(array_ds_vars[j], tmp_node->key, ft_strlen(array_ds_vars[j])) == 0)
					{
						free(array_ds_vars[j]);
						array_ds_vars[j] = ft_strdup(tmp_node->value);
					}
					tmp_node = tmp_node->next;
				}
				printf("token[%d] array_ds_vars (translated)[%d]:%s\n", i, j, array_ds_vars[j]);
				j++;
			}
			printf("\n");
			array_no_ds = malloc(sizeof(char *) * (nb_dlr_sign_token + 2));
			array_no_ds[nb_dlr_sign_token + 1] = NULL;
			j = 0;
			index = 0;
			while (tmp[j] != '\0' && index < (nb_dlr_sign_token + 1))
			{
				if (tmp[j] == '$')
				{
					j++;
					while ((tmp[j] >= 'a' && tmp[j] <= 'z') || (tmp[j] >= 'A' && tmp[j] <= 'Z') || (tmp[j] >= '0' && tmp[j] <= '9'))
						j++;
				}
				else
				{
					start = j;
					len = 0;
					while(tmp[j] != '$')
					{
						j++;
						len++;
					}
					array_no_ds[index] = ft_substr(tmp, start, len);
					printf("token[%d] array_no_ds[%d] :%s\n", i, index, array_no_ds[index]);
					index++;
				}
			}
			index = 0;
			array_concat = malloc(sizeof(char *) * (nb_dlr_sign_token + 2));
			array_concat[nb_dlr_sign_token + 1] = NULL;
			while (index < (nb_dlr_sign_token))
			{
				array_concat[index] = ft_concat(array_no_ds[index], array_ds_vars[index]);
				index++;
			}
			index = 0;
			while(index < (nb_dlr_sign_token + 1))
			{
				printf("token[%d] array_concat[%d] :%s\n", i, index, array_concat[index]);
				index++;
			}
			if (array_concat[0] != NULL)
				res = ft_strdup(array_concat[0]);
			index = 1;
			while (index < (nb_dlr_sign_token))
			{
				res = ft_concat(res, array_concat[index]);
				index++;
			}
			if (array_no_ds[nb_dlr_sign_token] != NULL)
				res = ft_concat(res, array_no_ds[nb_dlr_sign_token]);
			printf("res :%s\n", res);
			free(vars->tokens[i].cmd);
			vars->tokens[i].cmd = ft_strdup(res);
			printf("vars->tokens[%d].cmd :%s\n", i, vars->tokens[i].cmd);
			free(tmp);
			free(array_ds_vars);
			free(array_no_ds);
			free(res);
			free(array_concat);
		}
		i++;
	}
}

void	interpret_dollar_sign(t_prgm *vars)
{
	ids_cmd_opt_arg(vars);
}