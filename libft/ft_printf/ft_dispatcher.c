/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:02:38 by edesaint          #+#    #+#             */
/*   Updated: 2023/01/22 14:21:09 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert_chosen(va_list arg, char c)
{
	if (c == 'c')
		return (ft_convert_c(arg));
	else if (c == 's')
		return (ft_convert_s(arg));
	else if (c == 'p')
		return (ft_convert_p(arg));
	else if (c == 'd' || c == 'i')
		return (ft_convert_di(arg));
	else if (c == 'u')
		return (ft_convert_u(arg));
	else if (c == 'x')
		return (ft_convert_x(arg, 0));
	else if (c == 'X')
		return (ft_convert_x(arg, 1));
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	return (0);
}
