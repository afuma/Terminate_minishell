/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:13:03 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/31 20:46:18 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_builtin(t_node *node)
{
	if (!node || !node->tab_exec || !node->tab_exec[0] || !node->type
		|| ft_strcmp(node->tab_exec[0], "echo") == 0
		|| ft_strcmp(node->tab_exec[0], "cd") == 0
		|| ft_strcmp(node->tab_exec[0], "pwd") == 0
		|| ft_strcmp(node->tab_exec[0], "export") == 0
		|| ft_strcmp(node->tab_exec[0], "unset") == 0
		|| ft_strcmp(node->tab_exec[0], "env") == 0
		|| ft_strcmp(node->tab_exec[0], "exit") == 0)
	{
		return (true);
	}
	else
		return (false);
}

int	builtin_command(t_node *node, t_env *env)
{
	if (!node || !node->tab_exec || !node->tab_exec[0] || !node->type)
		return (ft_putstr_fd("Invalid command\n", STDERR_FILENO), 1);
	if (ft_strcmp(node->tab_exec[0], "echo") == 0)
		return (ft_echo(node, env));
	else if (ft_strcmp(node->tab_exec[0], "cd") == 0)
		return (ft_cd(node, env));
	else if (ft_strcmp(node->tab_exec[0], "pwd") == 0)
		return (ft_pwd(node, env));
	else if (ft_strcmp(node->tab_exec[0], "export") == 0)
		return (ft_export(node, env));
	else if (ft_strcmp(node->tab_exec[0], "unset") == 0)
		return (ft_unset(node, env));
	else if (ft_strcmp(node->tab_exec[0], "env") == 0)
		return (ft_env(node, env));
	else if (ft_strcmp(node->tab_exec[0], "exit") == 0)
		return (ft_exit(node, env));
	return (0);
}

bool	exec_builtin(t_node *node, t_env *env)
{
	int	exit_status;
	int	cpy_stdout;

	exit_status = 0;
	if (node->redir_out || node->redir_append)
	{
		cpy_stdout = dup(STDOUT_FILENO);
		if (cpy_stdout < 0)
			return (perror("dup"), false);
	}
	exit_status = builtin_command(node, env);
	if (node->redir_out || node->redir_append)
	{
		if (dup2(cpy_stdout, STDOUT_FILENO) < 0)
			return (perror("dup2"), false);
	}
	return (exit_status);
}
