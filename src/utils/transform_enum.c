/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_enum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:37:17 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/28 19:54:19 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Détermine le type de caractère (guillemet, espace, etc.) pour le lexer. */
t_stick_token ft_type_char(char c)
{
    if (c == '\'')
        return (S_QUOTE);
    else if (c == '"')
        return (D_QUOTE);
    else if (is_space(c))
        return (S_SPACE);
    else if (is_syntax_char(c))
        return (S_SYNTAX);
    else if (c == '\0')
        return (S_NULL);
    else
        return (S_CHAR);
}

// Pour l'affichage (print et debug)
char *transform_enum_type_token(t_state num_c)
{
	if (num_c == T_COMMAND)
		return ("T_COMMAND");
	else if (num_c == T_ARGUMENT)
		return ("T_ARGUMENT");
	else if (num_c == T_FILE)
		return ("T_FILE");
	else if (num_c == T_PIPE)
		return ("T_PIPE");
	else if (num_c == T_REDIR_IN)
		return ("T_REDIR_IN");
	else if (num_c == T_REDIR_OUT)
		return ("T_REDIR_OUT");
	else if (num_c == T_REDIR_APPEND)
		return ("T_REDIR_APPEND");
	else if (num_c == T_REDIR_HEREDOC)
		return ("T_REDIR_HEREDOC");
	else if (num_c == T_NULL)
		return ("T_NULL");
	return (NULL);
}

// num_c pour numéro du caractere
char *transform_enum_quote(t_stick_token num_c)
{
    if (num_c == S_QUOTE)
        return ("S_QUOTE");
    else if (num_c == D_QUOTE)
        return ("D_QUOTE");
    else if (num_c == S_SPACE)
        return ("S_SPACE");
    else if (num_c == S_SYNTAX)
        return ("S_SYNTAX");
    else if (num_c == S_NULL)
        return ("S_NULL");
    else
        return ("S_CHAR");
}

// // Fonction pour convertir le type de token en type de redirection
// t_state token_type_to_redirection_type(t_state type)
// {
//     if (type == T_REDIR_IN)
//         return T_REDIR_IN;
//     else if (type == T_REDIR_OUT)
//         return T_REDIR_OUT;
//     else if (type == T_REDIR_APPEND)
//         return T_REDIR_APPEND;
//     else if (type == T_REDIR_HEREDOC)
//         return T_REDIR_HEREDOC;
//     else
//         return -1;
// }