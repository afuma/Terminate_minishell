/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:23:51 by blax              #+#    #+#             */
/*   Updated: 2024/01/31 22:18:02 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

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

volatile sig_atomic_t	signal_received = 0;

bool ft_main(t_data *data, t_env *env)
{
	t_node *first_node;
	
	if (!is_closed_quotes(data))
		return (free_all(data), perror("unclosed quotes"), false);		// ft_error_2(data, "unclosed_quotes");
	ft_lexer(data);
	if (!data->token)
		return (free_all(data), false);
	determine_token_types(data);
	if (!verif_syntax(data->token))
		return (free_all(data), perror("syntax_erreur"), false);
	if (!pass_on_filters(data))
		return (free_all(data), perror("filter_erreur"), false);
	parser(data);
	// print_tokens(data->token);
	// print_nodes(data);
	free_tokens(data->token);
	data->token = NULL;
	free(data->str);
	data->str = NULL;
	first_node = data->node;
	data->node = NULL;
	free(data);
	data = NULL;
	execute_command_node(first_node, env);
	// free_nodes(first_node);
	return (true);
}

int	main(int argc, char *argv[], char **env)
{
	t_env	*my_env;

	if (argc > 2) //(1)
		return (printf("minishell : parameters : bad usage\n"), 0);
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
	main_loop(my_env);
	free_env(my_env);
	return (0);
}

bool main_loop(t_env *my_env)
{
	t_data *data;
	char	*command;
	
	data = NULL;
	while (1)
	{
		if (signal_received)
		{
			signal_received = 0;
			continue ;
		}
		command = readline("minishell> ");
		if (handle_ctrl_d(command))
			break ;
		if (command && *command)
		{
			add_history(command);
			data = malloc_and_init_data(command, my_env);
			if (!data)
				return (perror("malloc failed"), false);
			ft_main(data, my_env);
		}
		if (command)
		{
			free(command);
			command = NULL;
		}
	}
	rl_clear_history();
	return (true);
}