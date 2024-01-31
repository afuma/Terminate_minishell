/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 08:31:10 by blax              #+#    #+#             */
/*   Updated: 2024/01/31 22:01:25 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "enum.h"
# include "structures.h"
# include "libft.h"

# define _POSIX_C_SOURCE 200809L
# include <signal.h>
# include <unistd.h> // access
# include <stdlib.h> // malloc
# include <readline/readline.h> // readline
# include <readline/history.h> // addhistory
#include <sys/wait.h> //wait
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
// # include <bsd/string.h>
// # include <stddef.h> //ft_strcmp

extern volatile sig_atomic_t	signal_received;

// ------------------------- MAIN ---------------------------------

// main.c
bool main_loop(t_env *my_env);
bool ft_main(t_data *data, t_env *env);

// ------------------------- BUILTIN ---------------------------------

// builtins.c
bool				ft_cd(t_node *node, t_env *env);
bool				ft_echo(t_node *node, t_env *env);
bool				ft_env(t_node *node, t_env *env);
bool				ft_pwd(t_node *node, t_env *env);
bool				ft_unset(t_node *node, t_env *env);
bool				ft_exit(t_node *node, t_env *env);
bool				ft_export(t_node *node, t_env *env);

// ft_unset.c
int				is_valid_env_name(const char *str);
void			unset_error(char *arg);

// ------------------------- ENV ---------------------------------

// env_utils.c
void			add_env_var(t_env *env, const char *name, const char *content);
void			update_env_var(t_env *env, const char *name,
					const char *content);
char			*get_env_name(t_env *env, const char *name);
char			*get_env_content(const char *str);

// env_utils_2.c
char			*join_var_in_str(t_env_link *env_link);
char			**convert_env_to_tab(t_env *env);

// shlvl.c
void			update_shlvl(t_env *env);

// ------------------------- SYNTAX ---------------------------------

// is_syntax.c
bool is_syntax_char(char c);
bool is_syntax_string(char *str);
bool is_syntax(char c);
bool is_syntax_redir(char *str);

// syntax_utils_1.c
bool is_quote(char c);
bool is_space(char c);
bool is_double_symbol(t_data *data, int i, char c);

// syntax_utils_2.c
void update_is_quote(t_data *data, char letter);
bool is_closed_quotes(t_data *data);

// syntax_utils_3.c
bool is_begin_by_pipe(t_token *token);
bool is_end_by_pipe(t_token *token);
bool check_redir(t_token *token);
bool is_valid_redir(t_token *token);

// syntax.c
bool verif_syntax(t_token *token);

// trim.c
int nb_trim_left(char *str);
int nb_trim_right(char *str);
char *trim_str(char *str);

// ------------------------- FREE ------------------------------

// free.c
void free_tab_exec(char **tab_exec);
void free_nodes(t_node *node);
void free_tokens(t_token *token);
void free_data(t_data *data);
void	clear_single_node(t_node **node);
void	ft_node_delone(t_node *node);

// free_env.c
void    free_env(t_env *env);
void	free_node(t_node *node);
void	free_tab(char **tab);

// free_2.c
void free_all(t_data *data);

// error.c
bool ft_error(char *str);
void ft_error_2(t_data *data, char *str);

// ------------------ INIT --------------------

// init_env.c
t_env_link	*env_new_link(char *str);
void	env_connect_links(t_env_link *prev, t_env_link *current);
t_env	*init_mini_env(void);
t_env *init_env(char **system_env);
void	init_env_null(t_env *env);

//init_data.c
// t_data *malloc_data(t_data *data);
t_data	*malloc_and_init_data(char *str, t_env *env);

// ------------------ UTILS --------------------

// utils.c
void	ft_token_add_back(t_token **token, t_token *newlist);
t_token	*ft_token_last(t_token *token);
void	ft_token_iter(t_data *data, bool (*f)(t_token *));
void	ft_token_iter_expander(t_data *data, char *(*f)(t_env *, char *));
bool process_tokens(t_data *data, bool (*f)(char *str));

// transform_enum.c
t_stick_token ft_type_char(char c);
char *transform_enum_type_token(t_state num_c);
char *transform_enum_quote(t_stick_token num_c);

// ------------------ LEXER --------------------

// lexer.c
bool ft_lexer(t_data *data);
bool process_string(t_data *data, int *i);
bool process_quote(t_data *data, int *i);
bool process_syntax(t_data *data, int *i);

// lexer_utils_1.c
int set_len(t_data *data, int end);
bool skip_spaces(t_data *data, int *i);
bool is_empty_quotes(t_data *data, int *i);

// lexer_token.c
t_stick_token set_type_lstick(t_data *data);
t_token *init_token(void);
t_token *create_token(t_data *data, int end, int len);
bool add_token(t_data *data, int end, int len);

// lexer_print.c
void print_tokens(t_token *tokens);

// ------------------ Parser --------------------

// parser.c
void parser(t_data *data);

// parser_utils_1.c
bool is_command(bool *is_cmd, t_state cur_state);
bool is_pipe(char *str, bool *is_cmd);
t_state	what_redirection(char *str);
bool is_type_redir(t_state type_token);

// parser_utils_2.c
bool in_node(t_data *data, t_token *token);
int compt_args(t_data *data);
int compt_nodes(t_data *data);

// parser_print.c
void print_tab_exec(t_node *node);
void print_redir(t_node *node);
void print_nodes(t_data *data);

// parser_node.c
t_node *create_node(t_data *data);
void add_node(t_data *data);
void init_nodes(t_data *data);
bool fill_nodes(t_data *data);
bool delimit_node(t_data *data, t_token *token);

// parser_redir.c
bool update_redir(t_env *env, t_node *node, t_token *token);
bool init_redir(t_data *data, t_node *node, t_token *token);
bool sub_process_heredoc(t_env *env, t_node *node, char *delimiter);

// parser_redir_utils.c
bool is_redir(t_state type);
bool is_file_redir(t_token *token);
char *get_name_redir(t_token *token);

// parser_getters.c
t_token *get_first_token(t_data *data, t_node *node, t_token *token);
t_token *get_end_token(t_data *data, t_token *token);
char *get_argument(t_data *data, t_token *token);
char *get_command(t_token *token);

// parser_tab_exec.c
char **create_tab_exec(t_data *data, t_token *token, int nb_args);
char **init_tab_exec(t_data *data, t_token *token);

// parser_type_token.c
void update_token_type(t_token *token, bool *is_cmd, t_state cur_state);
void	determine_token_types(t_data *data);
void determine_next_token_type(t_state type_token, t_state *cur_state);

// ------------------ Expander --------------------

// expander.c
bool is_expandable(t_token *token);
char *expand_string(t_env *env, char *str);
void replace_string(char **original, const char *new_string);

// expander_utils_1.c
bool is_valid_varname_expand(char c);
char* expand_variables(t_env *env, char *token_str);
char* process_dollar_sign(t_env *env, char **str, char *result);
char* process_text_until_next_dollar(char **str, char *result);

// expander_utils_2.c
char* append_variable_value(t_env *env, char *result, char *varName);
char* extract_var_name(char **str);
char* copy_until_char(char *dest, char *src, char delimiter);

// ------------------ Filtres --------------------

// filters

// filter_main.c
bool pass_on_filters(t_data *data);

// filter_reserved_word.c
bool filter_reserved_word(char *str);
bool filter_authorized_word(char *str);

// filter_affectation.c
bool filter_affectation(char *str);
bool filter_affectation_varname(char *str, char *sign_equal);
// bool filter_affectation_content(char *str, char *sign_equal);

// filter_quotes.c
bool filter_quotes(char *str);
bool remove_quotes(char *input, char type_quote);

// filter_concatenate.c
bool filter_concatenate(t_token *token);
bool is_space_between_tokens(t_token *token);
bool ft_merge_token(t_token *token);
bool merge_token(t_token *dst, t_token *src);
char *merge_token_str(t_token *dst, t_token *src);

// ------------------ HEREDOC --------------------

// heredoc_utils.c
char	*find_name_heredoc(char *str);
char	*get_name_heredoc(void);
void	get_and_save_heredoc_content(t_env *env, int fd, char *delimiter);

// heredoc.c
// bool fill_heredoc(t_data *data);
// bool sub_process_heredoc(t_env *env, t_node *node, char *delimiter);
// bool process_heredoc(t_data *data, t_node *node);

// ------------------ EXEC --------------------

// exec.c
void			execute_command_node(t_node *node, t_env *env);
bool	execute_single_cmd(t_node *node, t_env *env);

// get_path.c
char			*get_cmd_path(char *cmd, char **envp);

// exec_redir.c
bool				exec_redir(t_node *node);
bool				exec_redir_1(t_node *node);
bool				exec_redir_2(t_node *node);

// exec_is_redir.c
bool is_empty_file(char *name);
bool is_redir_in(char *name);
bool is_redir_out(char *name, int type_redir);

// exec_builtin.c
bool			is_builtin(t_node *node);
int				builtin_command(t_node *node, t_env *env);
bool				exec_builtin(t_node *node, t_env *env);

// exec_cmd.c
bool				execute_command(t_node *node, char **envp);
void    exec_child_process(t_node *node, int in_fd, t_env *env, int *pipe_fds);
void	manage_parent_process(int *in_fd, int *pipe_fds, t_node *current_node);

// exec_pipeline.c
void			exec_pipeline(t_node *node, t_env *env);

// ------------------ SIGNAL --------------------

// signals.c
void			handle_sigint(int signum);
bool			handle_ctrl_d(char *input);

#endif
