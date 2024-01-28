/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pengu <pengu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:15:00 by edesaint          #+#    #+#             */
/*   Updated: 2023/06/10 23:17:35 by pengu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_len(int n, int int_convert)
{
	int				len;
	unsigned int	nbr;

	len = 0;
	if (n == 0)
		return (1);
	if (!int_convert && n < 0)
	{
		if (n == INT_MIN)
			return (11);
		len++;
		n *= -1;
	}
	nbr = n;
	if (int_convert && n < 0)
		nbr = 4294967296 + n;
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t	len;

// 	len = 0;
// 	while (*str++)
// 		len++;
// 	return (len);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	int		i;
// 	char	cc;

// 	i = 0;
// 	cc = (char)c;
// 	if (!s)
// 		return (0);
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == cc)
// 			return ((char *)(s + i));
// 		i++;
// 	}
// 	if (s[i] == (char)c)
// 		return ((char *)(s + i));
// 	return (0);
// }
