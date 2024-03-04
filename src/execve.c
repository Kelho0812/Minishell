/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:35:59 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/26 10:35:59 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execve(t_pipes *node)
{
	char	*path_str;
	char	**paths_array;
	char	*temp_str;
	int		i;

	if (access(node->data.command_n_args[0], F_OK) == 0)
		executens_ve(node);
	else
	{
		path_str = ft_getenv(node->init.envs, "PATH");
		paths_array = ft_split(path_str, ':');
		free(path_str);
		i = 0;
		temp_str = ft_strdup(node->data.command_n_args[0]);
		paths_array[i] = ft_strjoin_free(paths_array[i], "/");
		node->data.command_n_args[0] = ft_strjoin_free_v2(paths_array[i], node->data.command_n_args[0]);
		while (access(node->data.command_n_args[0], F_OK) != 0 && paths_array[i] != NULL)
		{
			paths_array[i] = ft_strjoin_free(paths_array[i], "/");
			free(node->data.command_n_args[0]);
			node->data.command_n_args[0] = ft_strjoin(paths_array[i], temp_str);
			i++;
		}
		free(temp_str);
		free_args(paths_array);
		executens_ve(node);
	}
}

void	executens_ve(t_pipes *node)
{
	pid_t	pid;
	char	**env_array;
	int		status;

	pid = fork();
	if (pid < 0)
		error_handler(ERR_FORK, NULL, NULL);
	else if (pid == 0)
	{
		if (node->in_out.input_type == HEARDOC)
			read();
		else
		{
			env_array = envlist_to_array(node->init.envs);
			status = execve(node->data.command_n_args[0], node->data.command_n_args, env_array);
			if (status == -1)
			{
				if (errno == ENOENT)
					printf("Command not found\n");
				else
					perror("execve");
			}
		}
	}
	waitpid(pid, NULL, 0);
}

char	**envlist_to_array(t_envs *envs)
{
	char	**env_array;
	t_envs	*current;
	int		i;

	current = envs;
	env_array = malloc(sizeof(char *) *( listlen(envs) + 1));
	i = 0;
	while (current != NULL)
	{
		env_array[i] = ft_strdup(current->whole_str);
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	listlen(t_envs *envs)
{
	t_envs	*current;
	int		len;

	len = 0;
	current = envs;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	printf("envs len: %d", len);
	return (len);
}
