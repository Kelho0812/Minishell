/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_parsers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:12:35 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/24 11:41:09 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	signs_check(char *input, char sign, int *i);
static int	pipe_amper_check(char *input, char sign, int *i);
static int	check_signs(char *input, int *i);
static int	check_last_pipe(char *input);

int	wrong_specialch_syntax(char *input)
{
	int	i;

	i = 0;
	if (!check_input(input, &i) || !check_for_command(input + i))
		return (error_handler(ERROR_WRONG_INPUT, input, NULL), 0);
	while (input[i])
	{
		if (input[i] == D_QUOTES)
			quotes_check(input + i, D_QUOTES);
		else if (input[i] == S_QUOTES)
			quotes_check(input + i, S_QUOTES);
		else if (input[i] == '|' || input[i] == '&' \
		|| input[i] == '<' || input[i] == '>')
		{
			if (!check_signs(input, &i))
				return (error_handler(ERROR_SPECIAL_CHAR, input, NULL), 0);
		}
		else if (input[i] == '\\' || input[i] == ';')
			return (error_handler(ERROR_SPECIAL_CHAR, input, NULL), 0);
		else
			i++;
	}
	if (!check_last_pipe(input))
		return (error_handler(ERROR_SPECIAL_CHAR, input, NULL), 0);
	return (1);
}

static int	check_signs(char *input, int *i)
{
	if (input[(*i)] == '|')
	{
		if (!pipe_amper_check(input, '|', i))
			return (0);
	}
	else if (input[(*i)] == '&')
	{
		if (!pipe_amper_check(input, '&', i))
			return (0);
	}
	else if (input[(*i)] == '>')
	{
		if (!signs_check(input, '>', i))
			return (0);
	}
	else if (input[(*i)] == '<')
	{
		if (!signs_check(input, '<', i))
			return (0);
	}
	return (1);
}

static int	signs_check(char *input, char sign, int *i)
{
	int	x;

	x = *i;
	if (sign == '>')
	{
		while (input[++(*i)] == '>')
			;
	}
	else if (sign == '<')
	{
		while (input[++(*i)] == '<')
			;
	}
	if ((*i) - x > 2 || !check_for_command(input + (*i)))
		return (0);
	return (1);
}

static int	pipe_amper_check(char *input, char sign, int *i)
{
	int	x;

	x = *i;
	if (sign == '|')
	{
		while (input[++(*i)] == '|')
			;
	}
	else if (sign == '&')
	{
		while (input[++(*i)] == '&')
			;
	}
	if ((*i) - x > 2 || !check_pipe_amper_next(input + (*i)))
		return (0);
	return (1);
}

static int	check_last_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i + 1])
		i++;
	while (i >= 0 && input[i] == ' ')
		i--;
	if (input[i] != '|' && input[i] != '&' \
	&& input[i] != '<' && input[i] != '>')
		return (1);
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<' \
		|| input[i] == '&')
			return (0);
		i++;
	}
	return (1);
}
