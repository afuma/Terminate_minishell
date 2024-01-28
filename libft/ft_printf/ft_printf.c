/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:02:46 by edesaint          #+#    #+#             */
/*   Updated: 2023/01/22 14:20:32 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// le prototype provient du man 3 printf

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		len;

	len = 0;
	va_start(arg, format);
	if (!format)
		return (0);
	if (!ft_strchr((char *) format, '%'))
	{
		ft_putstr_fd((char *) format, 1);
		return (ft_strlen(format));
	}
	while (*format)
	{
		if (*format != '%')
			len += write(1, format, 1);
		else
		{
			len += ft_convert_chosen(arg, *(format + 1));
			format++;
		}
		format++;
	}
	va_end(arg);
	return (len);
}
// retourne une valeur negative si une erreur apparait