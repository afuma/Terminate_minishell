/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:21:12 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/27 19:21:37 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_var_in_str(t_env_link *env_link)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(env_link->name, "=");
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, env_link->content);
	free (temp);
	if (!res)
		return (NULL);
	return (res);
}

char	**convert_env_to_tab(t_env *env)
{
	unsigned int	i;
	char			**res;
	t_env_link		*env_link;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (env->len + 1));
	if (!res)
		return (NULL);
	env_link = env->first;
	while (i < env->len)
	{
		res[i] = join_var_in_str(env_link);
		if (!res[i])
			return (res); // a free
		env_link = env_link->next;
		i++;
	}
	res[i] = 0;
	return (res);
}
