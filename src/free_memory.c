/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:57:46 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/30 14:18:46 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	coador(t_pipes **head)
{
	t_pipes	*next;
	t_pipes *current;

	current = (*head);

	while (current)
	{
		next = current->next;
		free(current->input_string);
		free_data(current->data);
		free(current);
		current = next;
	}
}

void	free_input(char **input)
{
	free(*input);
}
void	free_heardoc(char ***heardoc_read)
{
	int	i;

	i = 0;
	if (!(*heardoc_read))
			return ;
	while ((*heardoc_read)[i])
	{
		free((*heardoc_read)[i]);
		i++;
	}
	free((*heardoc_read));
	(*heardoc_read) = NULL;
}

void	free_data(t_data *data)
{
	int	i;
	int	x;
	
	x = 0;
	if (data)
	{
		while (data[x].command_n_args)
		{
			i = 0;
			while (data[x].command_n_args[i])
			{
				free(data[x].command_n_args[i]);
				i++;
			}
			free(data[x].command_n_args);
			x++;
		}
		free(data);
	}
}

void	free_envs(t_envs *envs)
{
	if (envs)
	{
		struct s_envs *current = envs;
		struct s_envs *next;
		while (current)
		{
			next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			current = next;
		}
	}
}

void	free_list(t_pipes **head)
{
	if (!(*head))
		return ;
	free_list(&(*head)->down);
	free_list(&(*head)->next);
	free((*head)->input_string);
	free_data((*head)->data);
	free(*head);
	*head = NULL;
}