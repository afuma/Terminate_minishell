/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:00:04 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/27 19:22:09 by wnguyen          ###   ########.fr       */
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
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

static int	process_export_arg(char *arg, t_env *env)
{
	char	*name;
	char	*content;

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
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_node *node, t_env *env)
{
	int	i;

	i = 1;
	if (!node->tab_exec[1] || node->tab_exec[1][0] == '#')
		return (print_env_var(env), 0);
	while (node->tab_exec[i] && node->tab_exec[i][0] != '#')
	{
		if (process_export_arg(node->tab_exec[i], env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

// int	ft_export(t_node *node, t_env *env)
// {
// 	int		i;
// 	char	*name;
// 	char	*content;

// 	i = 1;
// 	if (!node->tab_exec[1] || node->tab_exec[1][0] == '#')
// 		return (print_env_var(env), 0);
// 	while (node->tab_exec[i] && node->tab_exec[i][0] != '#')
// 	{
// 		if (check_env_name(node->tab_exec[i]))
// 		{
// 			if (ft_strchr(node->tab_exec[i], '='))
// 			{
// 				name = ft_substr(node->tab_exec[i], 0,
// 						ft_strchr(node->tab_exec[i], '=') - node->tab_exec[i]);
// 				content = get_env_content(node->tab_exec[i]);
// 				update_env_var(env, name, content);
// 				free(name);
// 				free(content);
// 			}
// 			else
// 				add_env_var(env, node->tab_exec[i], "");
// 		}
// 		else
// 			export_error(node->tab_exec[i]);
// 		i++;
// 	}
// 	return (0);
// }

