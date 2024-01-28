/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pengu <pengu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:15:00 by edesaint          #+#    #+#             */
/*   Updated: 2023/06/10 23:17:53 by pengu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_nbr_fd(int n, int fd, int int_convert)
{
	unsigned int	nbr;

	nbr = n;
	if (int_convert)
	{
		if (n < 0)
			nbr = 4294967296 + n;
	}
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			nbr = -n;
		}
	}
	if (nbr >= 10)
		ft_put_nbr_fd(nbr / 10, fd, int_convert);
	ft_putchar_fd(nbr % 10 + '0', fd);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// void	ft_putstr_fd(char *s, int fd)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return ;
// 	while (s[i])
// 	{
// 		ft_putchar_fd(s[i], fd);
// 		i++;
// 	}
// }
