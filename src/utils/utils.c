/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:23:27 by edesaint          #+#    #+#             */
/*   Updated: 2024/01/28 12:44:20 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_add_back(t_token **token, t_token *newlist)
{
	t_token	*l;

	if (!token || !newlist)
		return ;
	if (*token)
	{
		l = ft_token_last(*token);
		l->next = newlist;
	}
	else
		*token = newlist;
}

t_token	*ft_token_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

void	ft_token_iter(t_data *data, bool (*f)(t_token *))
{
	t_token *token;

	token = data->token;
	while (token)
	{
		f(token);
		token = token->next;
	}
}

void	ft_token_iter_expander(t_data *data, void (*f)(t_env *, char *))
{
	t_token *token;
	t_env *tmp_env;
	
	token = data->token;
	tmp_env = data->env;
	while (token)
	{
		if (is_expandable(token))
			f(tmp_env, token->str);
		token = token->next;
	}
}

bool process_tokens(t_data *data, bool (*f)(char *str))
{
    t_token *token;

    token = data->token;
    while (token)
    {
        if (!f(token->str))
            return (false);
        token = token->next;
    }
    return (true);
}