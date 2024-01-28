/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:01:14 by letnitan          #+#    #+#             */
/*   Updated: 2024/01/28 19:49:29 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_link	*env_new_link(char *str)
{
	char		*tmp;
	t_env_link	*new_link;

	if (!str)
		return (NULL);
	// new_link = memset_malloc(0, sizeof(t_env_link));
	new_link = malloc(sizeof(t_env_link));
	if (!new_link)
		return (NULL);
	tmp = ft_strchr(str, '=');
	if (tmp == 0)
		new_link->name = ft_strdup(str);
	else
	{
		new_link->name = ft_strndup(str, (tmp - &str[0]));
		new_link->content = ft_strdup(&tmp[1]);
	}
	return (new_link);
}

void	env_connect_links(t_env_link *prev, t_env_link *current)
{
	if (prev)
		prev->next = current;
	if (current)
		current->prev = prev;
}

t_env	*init_mini_env(void)
{
	t_env		*mini_env;
	t_env_link	*temp;
	char		*pwd;
	char		*path;

	mini_env = malloc(sizeof(t_env));
	pwd = getcwd(NULL, 0);
	if (!mini_env || !pwd)
		return (NULL);
	mini_env->first = env_new_link("_=/usr/bin/env");
	env_connect_links(mini_env->first, env_new_link("SHLVL=1"));
	path = ft_strjoin("PWD=", pwd);
	mini_env->last = env_new_link(path);
	env_connect_links(mini_env->first->next, mini_env->last);
	free(path);
	path = ft_strjoin("PATH=",
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	temp = env_new_link(path);
	free (path);
	env_connect_links(mini_env->last, temp);
	mini_env->last = temp;
	mini_env->lst_exit = 0;
	mini_env->len = 4;
	return (mini_env);
}

t_env *init_env(char **system_env)
{
	t_env		*env_main;
	t_env_link	*current;
	t_env_link	*prev;

	env_main = malloc(sizeof(t_env));
	if (!env_main)
		return (NULL);
	env_main->len = 0;
	current = env_new_link(system_env[env_main->len]); // faire le len++ dedans
	env_main->first = current;
	env_main->len++;
	prev = current;
	while (system_env[env_main->len])
	{
		current = env_new_link(system_env[env_main->len]);
		if (prev)
			env_connect_links(prev, current);
		env_main->len++;
		prev = prev->next;
	}
	env_main->last = current;
	env_main->lst_exit = 0;
	// update_shlvl(env_main);
	return (env_main);

}