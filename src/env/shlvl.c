/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:52:34 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/27 17:01:36 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_shlvl(t_env *env)
{
	int		shlvl;
	char	*shlvl_str;
	char	*new_shlvl;

	shlvl_str = get_env_name(env, "SHLVL");
	if (!shlvl_str)
	{
		add_env_var(env, "SHLVL", "1");
		return ;
	}
	shlvl = ft_atoi(shlvl_str);
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	if (new_shlvl)
	{
		update_env_var(env, "SHLVL", new_shlvl);
		free(new_shlvl);
	}
	else
		perror("malloc error");
}
