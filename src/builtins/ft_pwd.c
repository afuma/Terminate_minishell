/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 06:47:01 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/31 01:22:08 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Affiche le répertoire de travail actuel sur la sortie standard.
* En cas d'erreur, affiche un message d'erreur.
*/

bool	ft_pwd(t_node *node, t_env *env)
{
	char	*cwd;

	(void)node;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("ft_pwd: getcwd error");
		env->lst_exit = 1;
		return (false);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(cwd);
	env->lst_exit = 0;
	return (true);
}
