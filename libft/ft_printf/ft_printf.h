/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:34:31 by wnguyen           #+#    #+#             */
/*   Updated: 2023/12/25 09:38:28 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../../include/libft.h"

// size_t	ft_strlen(const char *str);
// char	*ft_strchr(const char *s, int c);
// void	ft_putchar_fd(char c, int fd);
// void	ft_putstr_fd(char *s, int fd);
void	ft_put_nbr_fd(int n, int fd, int int_convert);
int		ft_putnbr_len(int n, int int_convert);

int		ft_printf(const char *format, ...);
int		ft_convert_x(va_list arg, int upper);
int		ft_convert_c(va_list arg);
int		ft_convert_s(va_list arg);
int		ft_convert_p(va_list arg);
int		ft_convert_di(va_list arg);
int		ft_convert_u(va_list arg);
int		ft_convert_hex(size_t nb, int upper);
int		ft_convert_chosen(va_list arg, char c);

#endif