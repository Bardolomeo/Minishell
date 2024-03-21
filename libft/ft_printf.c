/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:44:27 by gsapio            #+#    #+#             */
/*   Updated: 2024/01/11 14:56:35 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_met_specifier(char *format, int *cnt_prnt, va_list args)
{
	if (*format == '%')
		ft_putchar('%', cnt_prnt);
	else if (*format == 'c')
		ft_putchar(va_arg(args, int), cnt_prnt);
	else if (*format == 's')
		ft_putstr(va_arg(args, char *), cnt_prnt);
	else if (*format == 'd' || *format == 'i')
		ft_printint(va_arg(args, int), cnt_prnt);
	else if (*format == 'p')
		ft_printaddr(va_arg(args, void *), cnt_prnt);
	else if (*format == 'u')
		ft_printuns(va_arg(args, unsigned int), cnt_prnt);
	else if (*format == 'x' || *format == 'X')
		ft_printhex(va_arg(args, unsigned int), *format, cnt_prnt);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		cnt_prnt;
	char	*cpy;

	cpy = (char *)format;
	cnt_prnt = 0;
	va_start(args, format);
	while (*cpy)
	{
		if (*cpy == '%')
		{
			cpy++;
			ft_met_specifier(cpy, &cnt_prnt, args);
			cpy++;
		}
		if (*cpy != 0 && *cpy != '%')
		{
			write(1, cpy, 1);
			cpy++;
			cnt_prnt++;
		}
	}
	va_end(args);
	return (cnt_prnt);
}

// int main()
// {
// 	unsigned int c = 20;
// 	int	s = 20;
// 	//int	i = INT_MAX;
// 	char *str;
// 	int stam;
// 	stam = ft_printf("%x\n", s);
// 	printf("%d\n", stam);
// 	stam = printf("%p  %p  %p\n", LONG_MAX, LONG_MAX, 0);
// 	printf("%d", stam);
// }
