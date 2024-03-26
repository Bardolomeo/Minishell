/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:20:44 by mtani             #+#    #+#             */
/*   Updated: 2023/10/18 11:23:58 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include "ft_isalpha.c"
//#include "ft_isdigit.c"
#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1)
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	int c = '-';
	
	if (ft_isalnum(c) == 1)
		printf("%c is alphanumerical\n", c);
	else
		printf("%c is NOT alphanumerical\n", c);
}*/
