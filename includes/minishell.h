/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiolive <ruiolive@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:02:05 by ruiolive          #+#    #+#             */
/*   Updated: 2024/02/01 10:24:23 by ruiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define D_QUOTES 34
# define S_QUOTES 39

typedef enum e_command_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NOT_BUILTIN
}					t_command_type;

typedef enum e_special_char
{
	S_LEFT_ARROW,
	D_LEFT_ARROW,
	S_RIGHT_ARROW,
	D_RIGHT_ARROW,
	AMPERZ,
	NO_SPECIAL
}					t_special_char;

typedef enum e_type_pipe
{
	N_PIPE,
	S_PIPE,
	D_PIPE
}					t_type_pipe;

typedef struct s_data
{
	char			*path_command;
	char			**command_n_args;
	t_special_char	special_char;
	t_command_type	command_type;
}					t_data;

typedef struct s_pipes
{
	struct s_pipes	*next;
	char			*input_string;
	t_type_pipe		pipe_type;
	t_data			*data;
	bool			empty_node;
}					t_pipes;

/********************/
/*		COLORS		*/
/********************/

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
# define RESET "\x1B[0m"

/****************************/
/*			ERRORS			*/
/****************************/

void				error_handler(int error_msg, void *param, void **param2);

typedef enum e_error
{
	ERROR_UNFINISHED_QUOTE,
	ERROR_SPECIAL_CHAR,
	ERROR_NEWLINE
}					t_error;

/****************************/
/*			PARSER			*/
/****************************/

int					signs_parser(char *input, int i);
int					quotes_parser(char *input);
int					check_begin_case(char *input, int *i);
int					parse_input(char *input, int *parenthesis, int *check_empty, int *x);
/****************************/
/*		PARSER	UTILS		*/
/****************************/

int					quotes_check(char *input, char c);
int					check_for_command_after(char *input);
int					check_pipe_amper_next(char *input);
int					check_end(char *input);
int					check_signs(char *input, int *i, char *myChar);
int					amper_count(char *input, int *i);
int					pipe_count(char *input, int *i);
int					major_sig_count(char *input, int *i);
int					minor_sig_count(char *input, int *i);

/****************************/
/*			LIST			*/
/****************************/

void				creat_list(t_pipes **head, char *input);

/****************************/
/*			FREE			*/
/****************************/

void				free_args(char **args);
void				coador(t_pipes **head);

/****************************/
/*			STRINGS			*/
/****************************/

char				*trim_str(char *input, t_type_pipe *pipe_check, int *i);

/****************************/
/*			READ LINE		*/
/****************************/

char				*line_read(void);
char				*get_input(void);
char				*ft_strjoin_v2(char *s1, char *s2);
char				*creat_cwd(void);
char				*trim_cwd(char *trimmed_cwd);

/****************************/
/*		READ LINE PARSER	*/
/****************************/

int					unfinished_command_line(char *input);
int					check_separator_after(char *input, int i);
int					check_separator_before(char *input, int i);
int					count_parenthesis(char *input, int *parenthesis, int *check_empty, int *x);
int					parenthesis_parser(char *input, int i, int *parenthesis, int *check_empty);

/****************************/
/*			DATA			*/
/****************************/

int					command_decider1(t_data *data);
int					command_decider2(t_data *data);
int					fill_data(t_pipes *pipe_struct, int count);
int					count_rarrow(char *str);
int					count_larrow(char *str);
int					count_amperz(char *str);
int					count_input(t_pipes *pipe);
void				prepare_split(t_data *data, t_pipes *pipe, int *back,
						int *front);
void				check_specialz(char *str, t_data *data, int *front);
int					check_only_spaces(char *input_str);
int					word_counter(char const *s, char c);
void				organize_list(t_pipes *pipe_struct);
char				**special_splitens(char *str, int *back, int *front,
						char c);

/****************************/
/*			TESTERZZZ		*/
/****************************/

void				tester(t_pipes *head);
void				input_str_tester(t_pipes *head);

#endif