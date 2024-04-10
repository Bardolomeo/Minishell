/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:11:08 by mtani             #+#    #+#             */
/*   Updated: 2024/04/09 15:47:10 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	//modificato per non stampare le var senza = (vedi export)
	if (ft_strchr(s, '='))
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}
