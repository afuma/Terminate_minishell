/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 06:47:01 by wnguyen           #+#    #+#             */
/*   Updated: 2024/01/30 18:37:36 by edesaint         ###   ########.fr       */
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
		return (false);
	}	
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (false);
}
