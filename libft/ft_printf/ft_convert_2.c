/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:02:54 by edesaint          #+#    #+#             */
/*   Updated: 2023/01/22 14:24:01 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert_hex(size_t nb, int upper)
{
	char		tmp;
	static int	i;

	i = 0;
	if (nb)
	{
		ft_convert_hex(nb / 16, upper);
		if (nb % 16 < 10)
			tmp = (nb % 16) + '0';
		else
		{
			if (upper)
				tmp = (nb % 16) - 10 + 'a' - 32;
			else
				tmp = (nb % 16) - 10 + 'a';
		}
		write(1, &tmp, 1);
		i++;
	}
	return (i);
}

int	ft_convert_x(va_list arg, int upper)
{
	unsigned int	nb;

	nb = (int) va_arg(arg, int);
	if (!nb)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	return (ft_convert_hex(nb, upper));
}
