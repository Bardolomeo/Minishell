/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexvalues.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:10:28 by gsapio            #+#    #+#             */
/*   Updated: 2023/11/10 12:52:11 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printaddr(void *ptr, int *cnt)
{
	if (!ptr)
	{
		*cnt += write (1, "(nil)", 5);
		return ;
	}
	*cnt += write (1, "0x", 2);
	ft_printhex((unsigned long int)ptr, 'x', cnt);
}

void	ft_printhex(unsigned long int n, char c, int *cnt)
{
	if (n == 16)
		ft_putstr("10", cnt);
	if (n > 16)
	{
		ft_printhex(n / 16, c, cnt);
		ft_printhex(n % 16, c, cnt);
	}
	if (n < 16)
	{
		if (n < 10)
			ft_putchar(n + 48, cnt);
		if (n >= 10 && c == 'X')
			ft_putchar(n + 55, cnt);
		if (n >= 10 && c == 'x')
			ft_putchar(n + 87, cnt);
	}
}
