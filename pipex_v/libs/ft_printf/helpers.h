/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 02:03:52 by fakouyat          #+#    #+#             */
/*   Updated: 2022/06/09 02:03:52 by fakouyat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef HELPERS_H
# define HELPERS_H
# include <unistd.h>

void	ft_print_int(int nb, int *str_len);
void	ft_print_char(int c, int *str_len);
void	ft_print_str(char *str, int *str_len);
void	ft_print_unsigned(unsigned int nb, int *str_len);
void	ft_print_ptr(unsigned long long nb, int *str_len);
void	ft_print_hex(unsigned int nb, int *str_len, char c);
#endif