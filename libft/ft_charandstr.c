/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charandstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:40:08 by gsapio            #+#    #+#             */
/*   Updated: 2023/11/09 19:59:55 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(int c, int *cnt)
{
	char	cha;

	cha = c;
	write(1, &cha, 1);
	(*cnt)++;
}

void	ft_putstr(char *s, int *cnt)
{
	char	*cpy;

	cpy = s;
	if (!cpy)
	{
		*cnt += write(1, "(null)", 6);
		return ;
	}
	while (*cpy)
	{
		ft_putchar(*cpy, cnt);
		cpy++;
	}
}
