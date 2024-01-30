/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:23:51 by blax              #+#    #+#             */
/*   Updated: 2024/01/30 18:05:51 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

int				g_info;

// il faut afficher un message de sortie: "exit" quand on clique sur ctrl+D
// void	handle_signal(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		ft_putstr_fd("\n", STDERR_FILENO);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

bool ft_main(t_data *data, t_env *env)
{
    // t_data *data;

    if (!is_closed_quotes(data))
    	return (free_all(data), perror("unclosed quotes"), false);
		// ft_error_2(data, "unclosed_quotes");
    ft_lexer(data);
    if (!data->token)
        return (free_all(data), false);
    determine_token_types(data);
    if (!verif_syntax(data->token))
        return (free_all(data), perror("syntax_erreur"), false);
    if (!pass_on_filters(data))
		return (free_all(data), perror("filter_erreur"), false);
        // ft_error_2(data, "filter_erreur");
    parser(data);
    // print_tokens(data->token);
    // print_nodes(data);
	if (!execute_command_node(data->node, env))
		return (false);
    // free_all(data);
	if (data->node && data->node->tab_exec &&
		ft_strcmp(data->node->tab_exec[0], "exit") == 0)
	{
		free_all(data);
		exit(EXIT_SUCCESS);
	}
    return (true);
}

int	main(int argc, char *argv[], char **env)
{
	t_data	*data;
	t_env	*my_env;

	if (argc > 2) //(1)
		return (printf("minishell : parameters : bad usage\n"), 0);
	data = NULL;
	my_env = NULL;
	argv[0] = '\0';
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	// init_env_null(my_env);
	if (!env || !env[0])
		my_env = init_mini_env();
	else
		my_env = init_env(env);
	update_shlvl(my_env);
	main_loop(data, my_env);
	free_env(my_env);
	return (0);
}

bool main_loop(t_data *data, t_env *my_env)
{
	char	*command;
	
	while (1)
	{
		command = readline("minishell> ");
		if (handle_ctrl_d(command))
			break;
		if (command && *command)
		{
			add_history(command);
			data = init_data(command, my_env);
			ft_main(data, my_env);
			// printf("je free data encore !");
			free_data(data);
		}
		free(command);
	}
	rl_clear_history();
	free_all(data);
	return (true);
}