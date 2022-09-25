/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:44:16 by fakouyat          #+#    #+#             */
/*   Updated: 2022/05/06 21:44:16 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pointer;
	int		length;

	length = size * nmemb;
	pointer = (void *)malloc(length);
	if (!pointer)
		return (0);
	ft_bzero(pointer, length);
	return (pointer);
}
