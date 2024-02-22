/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:07:37 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/05 16:15:29 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_cd(t_envs *head, char **str)
{
	char	*new_dir;
	if (str[1] == NULL)
	{
		new_dir = ft_getenv(head, "HOME");
		chdir(new_dir);
		free(new_dir);
		new_dir = NULL;
		return ;
	}
	if (str[2] != NULL)
		printf("\nruiolive&&jorteixe@minishell: cd: too many arguments\n");
	else
	{
		if (strcmp(str[1], "") == 0 || strcmp(str[1], "~") == 0
			|| str[1] == NULL)
			new_dir = ft_getenv(head, "HOME");
		else
			new_dir = ft_strdup(str[1]);
		if (chdir(new_dir) == (-1))
		{
			err_num_chdir(new_dir);
			free(new_dir);
			new_dir = NULL;
			return ;
		}
		free(new_dir);
	}
}

void	err_num_chdir(char *str)
{
	if (errno == ENOENT)
		printf("\nruiolive&&jorteixe@minishell:"
			"cd: %s: No such file or directory\n",
			str);
	else if (errno == ENOTDIR)
		printf("\nruiolive&&jorteixe@minishell: cd: %s: Not a directory\n",
			str);
}
