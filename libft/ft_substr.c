/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:19:45 by wnguyen           #+#    #+#             */
/*   Updated: 2023/11/15 21:14:59 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	get_len(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	max;

	max = 0;
	slen = ft_strlen(s);
	if (start < slen)
		max = slen - start;
	if (max > len)
		max = len;
	return (max);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	max;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	max = get_len(s, start, len);
	str = (char *)malloc(sizeof(char) * (max) + 1);
	if (!str)
		return (0);
	while (i < max)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
