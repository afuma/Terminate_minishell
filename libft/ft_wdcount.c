/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wdcount.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:37:51 by pengu             #+#    #+#             */
/*   Updated: 2023/11/15 21:15:16 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_wdcount(const char *str, char delimiter)
{
	size_t	count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != delimiter)
		{
			count++;
			while (*str != delimiter && *str)
				str++;
		}
		else
			str++;
	}
	return (count);
}
