/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive  <ruiolive@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:55:58 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/06 15:55:58 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_realloc(char ***heardoc_read, t_counter *iter);
static int	add_to_line(char **new_line, char *str, \
			char ***h_doc, t_counter *iter);

void	heardoc_check(char ***heardoc_read, char *input, t_counter *itr, int i)
{
	char	*new_line;
	char	*str_condition;

	while (input[itr->i] && itr->i < i)
	{
		itr->i += quotes_ignore(input + itr->i);
		if (itr->i > 0 && input[itr->i] && !ft_strncmp(input + itr->i, "<<", 2))
		{
			str_condition = search_heardoc_condition(input, itr);
			if (!str_condition)
				return ;
			str_condition = copy_inside_quotes(str_condition);
			*heardoc_read = ft_realloc(heardoc_read, itr);
			while (1)
			{
				new_line = readline("> ");
				if (!add_to_line(&new_line, str_condition, heardoc_read, itr))
					break ;
			}
			free(str_condition);
			itr->counter++;
		}
		else
			itr->i++;
	}
}

static char	**ft_realloc(char ***heardoc_read, t_counter *iter)
{
	char	**copy;
	int		x;

	x = 0;
	copy = malloc(sizeof(char *) * (iter->counter + 2));
	if (!copy)
		return (NULL);
	if (!(*heardoc_read))
	{
		copy[0] = ft_strdup("");
		copy[1] = 0;
		return (copy);
	}
	while ((*heardoc_read)[x])
	{
		copy[x] = ft_strdup((*heardoc_read)[x]);
		free((*heardoc_read)[x]);
		x++;
	}
	copy[x] = ft_strdup("");
	x++;
	copy[x] = 0;
	free((*heardoc_read));
	return (copy);
}

static int	add_to_line(char **new_ln, char *str, \
char ***h_doc, t_counter *iter)
{
	if (!(*new_ln))
		return (err_hlr_2(ERR_READ, str, NULL), 0);
	if (!(*(*new_ln)))
	{
		free(*new_ln);
		return (1);
	}
	if (!ft_strncmp(*new_ln, str, maxlen(ft_strlen(*new_ln), ft_strlen(str))))
	{
		free(*new_ln);
		(*h_doc)[iter->counter] = add_nl((*h_doc)[iter->counter], "\n");
		(*h_doc)[iter->counter + 1] = 0;
		iter->i++;
		return (0);
	}
	if (!(*(*h_doc)[iter->counter]))
	{
		free((*h_doc)[iter->counter]);
		(*h_doc)[iter->counter] = ft_strdup(*new_ln);
		free(*new_ln);
	}
	else
		(*h_doc)[iter->counter] = \
		str_join_with_newline((*h_doc)[iter->counter], *new_ln);
	return (1);
}
