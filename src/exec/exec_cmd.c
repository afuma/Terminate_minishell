/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:57:41 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/24 16:02:49 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command(t_node *node, char **envp)
{
	char	*cmd_path;

	if (ft_strchr(node->tab_exec[0], '/'))
		cmd_path = ft_strdup(node->tab_exec[0]);
	else
		cmd_path = get_cmd_path(node->tab_exec[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(node->tab_exec[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (127);
	}
	if (execve(cmd_path, node->tab_exec, envp) == -1)
	{
		perror("execve error");
		free(cmd_path);
		return (126);
	}
	free(cmd_path);
	return (0);
}
