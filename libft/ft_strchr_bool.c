/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_bool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:08:17 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/24 22:07:31 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

bool	ft_strchr_bool(const char *str, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = (char)c;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == cc)
			return (true);
		i++;
	}
	return (false);
}
