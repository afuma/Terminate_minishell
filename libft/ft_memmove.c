/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:08:04 by wnguyen           #+#    #+#             */
/*   Updated: 2023/11/15 21:13:51 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d_ptr;
	unsigned const char	*s_ptr;

	d_ptr = dest;
	s_ptr = src;
	if (!dest && !src)
		return (0);
	if (dest > src)
	{
		while (n-- > 0)
			*(d_ptr + n) = *(s_ptr + n);
	}
	else
	{
		while (n-- > 0)
			*d_ptr++ = *s_ptr++;
	}
	return (dest);
}
