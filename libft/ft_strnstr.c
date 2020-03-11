/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kradoste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 22:30:51 by kradoste          #+#    #+#             */
/*   Updated: 2018/04/23 13:11:18 by kradoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	x;

	if (!(*needle))
		return ((char *)haystack);
	x = ft_strlen(needle);
	while (*haystack && len-- >= x)
	{
		if (*haystack == *needle && ft_memcmp(haystack, needle, x) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return ((void *)0);
}
