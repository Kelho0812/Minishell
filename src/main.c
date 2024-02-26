/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:58:22 by ruiolive          #+#    #+#             */
/*   Updated: 2024/01/31 15:14:18 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	char		**heardoc_read;
	t_counter	count_struc;
	t_pipes		*head;
	t_envs		*head_envs;

	head = NULL;
	heardoc_read = NULL;
	head_envs = create_env_list(env);
	(void)argv;
	(void)env;
	if (argc == 1)
	{
		while (1)
		{
			count_struc.i = 0;
			count_struc.counter = 0;
			input = line_read(&heardoc_read, &count_struc);
			if (input && *input)
				add_history(input);
			else
				continue ;
			// printf("%s\n", ft_getenv(head_envs, input));
			input = check_quotes_n_expand(head_envs, input);
			creat_list(&head, input);
			// input_str_tester(head);
			// // freezzzz(input, &heardoc_read, &head);
			organize_list(head);
			executer(head_envs, head);
			// tester(head);
			// input = ft_split(input," ");
			// printf("%s\n", input);
			//execute_command(head, env);
			coador(&head);
			head = NULL;
			free(input);
		}
		free_env_list(head_envs);
		rl_clear_history();
	}
}
