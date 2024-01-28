/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 06:47:01 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/24 14:41:59 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Affiche le répertoire de travail actuel sur la sortie standard.
* En cas d'erreur, affiche un message d'erreur.
*/

int	ft_pwd(t_node *node, t_env *env)
{
	char	*cwd;

	(void)node;
	(void)env;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		free(cwd);
	}
	else
	{
		perror("ft_pwd: getcwd error");
		return (1);
	}	
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
