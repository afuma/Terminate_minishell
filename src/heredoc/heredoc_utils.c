/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:07:13 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/28 12:42:15 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_name_heredoc(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i < 0)
		return (NULL);
	str[i] = 'a';
	while (str[i] <= 'z' && access(str, F_OK) == 0)
		str[i]++;
	return (str);
}

char	*get_name_heredoc(void)
{
	char	*temp;

    temp = malloc(6);
    if (!temp)
		return (NULL);
    temp = ft_strcpy(temp, "/tmp/");
    if (!temp)
		return (NULL);
	while (access(temp, F_OK) == 0)
	{
		temp = ft_strjoin(temp, "a");
		if (!temp)
			return (NULL);
		temp = find_name_heredoc(temp);
		if (!temp)
			return (NULL);
	}
	return (temp);
}

void	get_and_save_heredoc_content(t_env *env, int fd, char *delimiter)
{
	char *line;

	line = readline("> ");
    while (line != NULL && ft_strcmp(line, delimiter) == 0 && errno != EINTR)
	{
        expand_string(env, line);
		write(fd, line, ft_strlen(line));
        free(line);
        line = readline("> ");
        if (!line && errno != EINTR && errno != EBADF)
			write(STDERR_FILENO, "\n", 1);
        if (errno == EINTR || errno == EBADF)
		{
			free (line);
			line = NULL;
			env->lst_exit = 128 + SIGINT;
		}
		write(fd, "\n", 1);
    }
}