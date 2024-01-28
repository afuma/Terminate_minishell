/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:09:43 by wnguyen           #+#    #+#             */
/*   Updated: 2023/11/15 21:14:49 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	llen;

	llen = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while (*big && len-- >= llen)
	{
		if (ft_strncmp(big, little, llen) == 0)
			return ((char *)big);
		big++;
	}
	return (0);
}
