/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:00:04 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/31 23:33:54 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env_var(t_env *env)
{
	t_env_link	*current;

	current = env->first;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(current->content, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}

void	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	check_env_name(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '=')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '='
			&& str[i] != ':' && str[i] != '/')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static bool	process_export_arg(char *arg, t_env *env)
{
	char	*name;
	char	*content;
	bool	status;

	status = true;
	if (check_env_name(arg))
	{
		if (ft_strchr(arg, '='))
		{
			name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
			content = get_env_content(arg);
			update_env_var(env, name, content);
			free(name);
			free(content);
		}
		else
			add_env_var(env, arg, "");
	}
	else
	{
		export_error(arg);
		status = false;
	}
	return (status);
}

bool	ft_export(t_node *node, t_env *env)
{
	int		i;
	bool	status;

	i = 1;
	status = true;
	if (!node->tab_exec[1] || node->tab_exec[1][0] == '#')
		print_env_var(env);
	else
	{
		while (node->tab_exec[i] && node->tab_exec[i][0] != '#')
		{
			if (!process_export_arg(node->tab_exec[i], env))
				status = false;
			i++;
		}
	}
	env->lst_exit = status;
	return (status);
}
