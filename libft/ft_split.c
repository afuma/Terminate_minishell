/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:35:54 by wnguyen           #+#    #+#             */
/*   Updated: 2023/11/15 21:14:24 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s++ != c)
		len++;
	return (len);
}

static size_t	ft_count_word(const char *s, char c)
{
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static void	ft_free(char **s, int i)
{
	while (i-- > 0)
	{
		if (s[i])
		{
			free (s[i]);
			s[i] = NULL;
		}
	}
	free (s);
}

int	ft_free_word(char **result, size_t i)
{
	if (!result)
	{
		ft_free(result, i);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	wordlen;
	size_t	count;
	size_t	i;
	char	**result;

	count = ft_count_word(s, c);
	i = 0;
	result = (char **) malloc ((sizeof(char *) * (count + 1)));
	if (!result)
		return (0);
	while (i < count)
	{
		while (*s && *s == c)
			s++;
		wordlen = ft_wordlen(s, c);
		result[i] = ft_substr(s, 0, wordlen);
		if (!ft_free_word(result, i))
			return (0);
		i++;
		s += wordlen;
	}
	result[count] = NULL;
	return (result);
}

/* code qui marche beaucoup plus court a etudier

#include "libft.h"

static void	ft_allocate(char **tab, char const *s, char c)
{
	char		**tab_p;
	char const	*tmp;

	tmp = s;
	tab_p = tab;
	while (*tmp)
	{
		while (*s == c)
			++s;
		tmp = s;
		while (*tmp && *tmp != c)
			++tmp;
		if (*tmp == c || tmp > s)
		{
			*tab_p = ft_substr(s, 0, tmp - s);
			s = tmp;
			++tab_p;
		}
	}
	*tab_p = NULL;
}

static int	ft_count_words(char const *s, char c)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s)
			++word_count;
		while (*s && *s != c)
			++s;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		size;

	if (!s)
		return (NULL);
	size = ft_count_words(s, c);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	ft_allocate(new, s, c);
	return (new);
}


*/