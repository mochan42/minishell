/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 02:31:27 by fakouyat          #+#    #+#             */
/*   Updated: 2022/11/16 02:31:27 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	init_val_sq_ref(int **res, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		res[i] = malloc(sizeof(int) * 2);
		res[i][0] = -1;
		res[i][1] = -1;
		i++;
	}
}

void	ft_map_val_sq_ref(char *s, int **res, int **qts, int *cpt)
{
	if (is_btw_q(s, '"', qts[cpt[0]][0]) == NULL)
	{
		if (res[cpt[1]][0] == -1)
			res[cpt[1]][0] = qts[cpt[0]][0];
		else
			res[cpt[1]][1] = qts[cpt[0]][0];
	}
	if (is_btw_q(s, '"', qts[cpt[0]][1]) == NULL)
	{
		if (res[cpt[1]][0] == -1)
			res[cpt[1]][0] = qts[cpt[0]][1];
		else
			res[cpt[1]][1] = qts[cpt[0]][1];
	}
}

int	**ft_valid_sq_ref(char *s, char c)
{
	int	**qts;
	int	q_size;
	int	**res;
	int	*cpt;

	q_size = ft_get_ref_qt_size(s, c);
	qts = ft_ref_quote(s, c);
	res = malloc(sizeof(int *) * (q_size / 2));
	cpt = malloc(sizeof(int) * 2);
	cpt[0] = 0;
	cpt[1] = 0;
	init_val_sq_ref(res, q_size / 2);
	while (cpt[0] < q_size / 2)
	{
		ft_map_val_sq_ref(s, res, qts, cpt);
		if (res[cpt[1]][0] != -1 && res[cpt[1]][1] != -1)
			cpt[1] += 1;
		free(qts[cpt[0]]);
		cpt[0] += 1;
	}
	free(qts);
	free(cpt);
	return (res);
}

int	*is_btw_val_sq(char *s, char c, int ref)
{
	int	j[3];
	int	**qts;
	int	*res;

	j[2] = ft_get_ref_qt_size(s, c);
	res = malloc(sizeof(int) * 2);
	qts = ft_valid_sq_ref(s, c);
	j[0] = 0;
	j[1] = 0;
	while (j[0] < j[2] / 2)
	{
		if (qts[j[0]][0] != -1 && qts[j[0]][1] != -1)
		{
			if (check(ref, qts[j[0]][0], qts[j[0]][1], res) == 0 && j[1] == 0)
			{
				free(qts[j[0]]);
				j[1] = 1;
			}
		}
		j[0] += 1;
	}
	free(qts);
	if (j[1] == 1)
		return (res);
	return (NULL);
}
