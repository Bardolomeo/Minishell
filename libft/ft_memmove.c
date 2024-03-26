/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:01:54 by mtani             #+#    #+#             */
/*   Updated: 2023/10/14 16:25:38 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmpdest;
	unsigned char	*tmpsrc;
	size_t			i;

	if (!dest && !src)
		return (dest);
	tmpdest = (unsigned char *)dest;
	tmpsrc = (unsigned char *)src;
	i = 0;
	if (tmpdest < tmpsrc)
	{
		while (i < n)
		{
			tmpdest[i] = tmpsrc[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			tmpdest[n] = tmpsrc[n];
	}
	return (dest);
}

/*int main()
{
	char string1[12];
	char string2[] = "Hello my baby";

	ft_memmove(string1, string2, 8);

	printf("%s", string1);
}*/
