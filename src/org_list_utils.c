/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:47:25 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/24 15:57:03 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_input(t_pipes *pipe)
{
	char	*str;
	int		count;

	count = 1;
	str = pipe->input_string;
	count += count_larrow(str);
	count += count_rarrow(str);
	count += count_amperz(str);
	return (count);
}

int	count_larrow(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			count++;
			if (str[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (count);
}

int	count_rarrow(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			count++;
			if (str[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (count);
}

int	count_amperz(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '&' && str[i + 1] == '&')
			count++;
		i++;
	}
	return (count);
}

int	fill_data(t_pipes *pipe_struct, int count)
{
	int		i;
	int		back;
	int		front;
	t_data	*data;

	data = pipe_struct->data;
	i = 0;
	front = 0;
	while (i < count)
	{
		prepare_split(&data[i], pipe_struct, &back, &front);
		data[i].command_n_args = special_splitens(pipe_struct->input_string
				+ back, &back, &front, 32);
		if (!command_decider1(&data[i]) && !command_decider2(&data[i]))
			data[i].command_type = NOT_BUILTIN;
		i++;
	}
	return (0);
}

int	command_decider1(t_data *data)
{
	if (ft_strncmp(data->command_n_args[0], "echo", 5) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\"echo\"", 7) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\'echo\'", 7) == 0)
		data->command_type = ECHO;
	else if (ft_strncmp(data->command_n_args[0], "cd", 3) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\"cd\"", 5) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\'cd\'", 5) == 0)
		data->command_type = CD;
	else if (ft_strncmp(data->command_n_args[0], "pwd", 4) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\"pwd\"", 6) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\'pwd\'", 6) == 0)
		data->command_type = PWD;
	else if (ft_strncmp(data->command_n_args[0], "export", 7) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\"export\"", 9) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\'export\'", 9) == 0)
		data->command_type = EXPORT;
	else
		return (0);
	return (1);
}

int	command_decider2(t_data *data)
{
	if (ft_strncmp(data->command_n_args[0], "unset", 6) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\"unset\"", 8) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\'unset\'", 8) == 0)
		data->command_type = UNSET;
	else if (ft_strncmp(data->command_n_args[0], "env", 4) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\"env\"", 6) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\'env\'", 6) == 0)
		data->command_type = ENV;
	else if (ft_strncmp(data->command_n_args[0], "exit", 5) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\"exit\"", 7) == 0 \
		|| ft_strncmp(data->command_n_args[0], "\'exit\'", 7) == 0)
		data->command_type = EXIT;
	else
		return (0);
	return (1);
}