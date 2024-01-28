/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:31:23 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/24 14:47:32 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Check if the input string is the '-n' option.
 * Returns true if it matches, false otherwise.
 */

bool	is_n_option(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/*
 * Custom implementation of the 'echo' command.
 * Outputs the given arguments to the standard output.
 * Supports the '-n' option to suppress the trailing newline.
 */

int	ft_echo(t_node *node, t_env *env)
{
	int	i;
	int	n_option;

	(void)env;
	i = 1;
	n_option = 0;
	if (!node->tab_exec[1])
		return (ft_putchar_fd('\n', STDOUT_FILENO), 0);
	while (node->tab_exec[i] && is_n_option(node->tab_exec[i]))
	{
		n_option = 1;
		i++;
	}
	while (node->tab_exec[i])
	{
		ft_putstr_fd(node->tab_exec[i], STDOUT_FILENO);
		if (node->tab_exec[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
