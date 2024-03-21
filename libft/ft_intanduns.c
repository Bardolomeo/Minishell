/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intanduns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:48:41 by gsapio            #+#    #+#             */
/*   Updated: 2023/11/10 12:05:35 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printint(int n, int *cnt)
{
	long int	nb;

	if (n < 0)
	{
		if (n == INT_MIN)
		{
			*cnt += write(1, "-2147483648", 11);
			return ;
		}
		else
			nb = -n;
		*cnt += write(1, "-", 1);
	}
	else
		nb = n;
	if (nb == 10)
		ft_putstr("10", cnt);
	if (nb > 10)
	{
		ft_printint(nb / 10, cnt);
		ft_printint(nb % 10, cnt);
	}
	if (nb < 10)
		ft_putchar(nb + 48, cnt);
}

void	ft_printuns(unsigned int nb, int *cnt)
{
	if (nb == 10)
		ft_putstr("10", cnt);
	if (nb > 10)
	{
		ft_printint(nb / 10, cnt);
		ft_printint(nb % 10, cnt);
	}
	if (nb < 10)
		ft_putchar(nb + 48, cnt);
}
