/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:36:47 by nrey              #+#    #+#             */
/*   Updated: 2024/10/09 07:05:20 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*wordcpy(const char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static int	add_word(char **result, const char *word, int *j)
{
	result[*j] = (char *)word;
	if (!result[*j])
	{
		while ((*j)-- > 0)
			free(result[*j]);
		free(result);
		return (0);
	}
	(*j)++;
	return (1);
}

static int	fill_result(char **result, const char *s, char c, int i)
{
	int		j;
	int		start;
	char	*word;

	i = 0;
	j = 0;
	start = -1;
	while (s[i])
	{
		if (s[i] != c && start == -1)
			start = i;
		if ((s[i] == c || s[i + 1] == '\0') && start != -1)
		{
			if (s[i] == c)
				word = wordcpy(s, start, i);
			else
				word = wordcpy(s, start, i + 1);
			if (!add_word(result, word, &j))
				return (0);
			start = -1;
		}
		i++;
	}
	result[j] = NULL;
	return (1);
}

static int	countwords(char const *s, char c)
{
	int	insideword;
	int	count;

	count = 0;
	insideword = 0;
	while (*s)
	{
		if (*s != c && insideword == 0)
		{
			insideword = 1;
			count++;
		}
		else if (*s == c)
			insideword = 0;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		n;

	if (!s)
		return (NULL);
	n = countwords(s, c);
	result = (char **)malloc((n + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_result(result, s, c, 0))
		return (NULL);
	return (result);
}
