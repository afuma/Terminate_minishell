/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 07:33:34 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/30 19:57:32 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_env(t_node *node, t_env *env)
{
	t_env_link	*current;

	if (node->tab_exec[1])
		return (false);
	current = env->first;
	while (current != NULL)
	{
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(current->content, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
	return (true);
}
