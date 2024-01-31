/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:21:48 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/31 16:26:19 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_env_name(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_link(t_env *env, t_env_link *link)
{
	t_env_link	*current;
	t_env_link	*previous;

	current = env->first;
	previous = NULL;
	while (current)
	{
		if (current == link)
		{
			if (previous)
				previous->next = current->next;
			else
				env->first = current->next;
			free(link->name);
			free(link->content);
			free(link);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

// void	unset_error(char *arg)
// {
// 	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
// 	ft_putstr_fd(arg, STDERR_FILENO);
// 	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
// }

void	remove_env_var(t_env *env, char *name)
{
	t_env_link	*current;
	t_env_link	*next;

	current = env->first;
	while (current)
	{
		next = current->next;
		if (ft_strcmp(current->name, name) == 0)
		{
			remove_env_link(env, current);
			env->len--;
			break ;
		}
		current = next;
	}
}

bool	ft_unset(t_node *node, t_env *env)
{
	char	**args;
	int		i;

	args = node->tab_exec;
	i = 1;
	while (args[i])
	{
		if (is_valid_env_name(args[i]))
			remove_env_var(env, args[i]);
		i++;
	}
	env->lst_exit = 0;
	return (true);
}

// bool	ft_unset(t_node *node, t_env *env)
// {
// 	t_env_link	*current;
// 	t_env_link	*next;
// 	char		**args;
// 	int			i;

// 	args = node->tab_exec;
// 	i = 1;
// 	while (args[i])
// 	{
// 		if (!is_valid_env_name(args[i]))
// 		{
// 			unset_error(args[i]);
// 			i++;
// 		}
// 		current = env->first;
// 		while (current)
// 		{
// 			next = current->next;
// 			if (ft_strcmp(current->name, args[i]) == 0)
// 			{
// 				remove_env_link(env, current);
// 				env->len--;
// 			}
// 			current = next;
// 		}
// 		i++;
// 	}
// 	return (true);
// }
