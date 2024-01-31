/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:51:49 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/31 00:19:59 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_oldpwd(t_env *env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("cd: getcwd error"));
	update_env_var(env, "OLDPWD", oldpwd);
	free(oldpwd);
}

void	update_pwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("cd: getcwd error"));
	update_env_var(env, "PWD", pwd);
	free(pwd);
}

static char	*get_cd_path(t_node *node, t_env *env, bool *is_allocated)
{
	char	*path;

	*is_allocated = 0;
	if (node->tab_exec[1] && ft_strcmp(node->tab_exec[1], "~") != 0)
		path = node->tab_exec[1];
	else
	{
		path = get_env_name(env, "HOME");
		if (!path)
			return (NULL);
	}
	if (ft_strcmp(path, "-") == 0)
	{
		path = get_env_name(env, "OLDPWD");
		if (!path)
			return (NULL);
		*is_allocated = 1;
	}
	return (path);
}

static bool	handle_cd_error(t_env *env, char *error_msg, int status, char *path)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	env->lst_exit = status;
	if (path)
		free(path);
	return (false);
}

bool	ft_cd(t_node *node, t_env *env)
{
	char	*path;
	bool	is_path_allocated;

	if (node->tab_exec[1] && node->tab_exec[2])
		return (handle_cd_error(env, "cd: too many arguments\n", 1, NULL));
	path = get_cd_path(node, env, &is_path_allocated);
	if (!path)
		return (handle_cd_error(env, "cd: path error\n", 1, NULL));
	update_oldpwd(env);
	if (chdir(path) == -1)
	{
		if (is_path_allocated)
			free(path);
		return (handle_cd_error(env, "cd: chdir error\n", 1, NULL));
	}
	update_pwd(env);
	if (is_path_allocated)
		free(path);
	env->lst_exit = 0;
	return (true);
}

// bool	ft_cd(t_node *node, t_env *env)
// {
// 	char	*path;

// 	if (node->tab_exec[1] && node->tab_exec[2])
// 		return (handle_cd_error(env, "cd: too many arguments\n", 1, NULL));
// 	if (node->tab_exec[1] && ft_strcmp(node->tab_exec[1], "~") != 0)
// 		path = node->tab_exec[1];
// 	else
// 	{
// 		path = get_env_name(env, "HOME");
// 		if (!path)
// 			return (handle_cd_error(env, "cd: HOME not set\n", 1, NULL));
// 	}
// 	if (ft_strcmp(path, "-") == 0)
// 	{
// 		path = get_env_name(env, "OLDPWD");
// 		if (!path)
// 			return (handle_cd_error(env, "cd: OLDPWD not set\n", 1, NULL));
// 	}
// 	update_oldpwd(env);
// 	if (chdir(path) == -1)
// 		return (handle_cd_error(env, "cd: chdir error\n", 1, NULL));
// 	update_pwd(env);
// 	free(path);
// 	env->lst_exit = EXIT_SUCCESS;
// 	return (true);
// }
