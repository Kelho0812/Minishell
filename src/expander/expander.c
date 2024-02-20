/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:30:38 by jorteixe          #+#    #+#             */
/*   Updated: 2024/02/15 14:30:38 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_quotes_n_expand(char *str)
{
	int		j;
	bool	single_open;
	bool	double_open;

	j = 0;
	single_open = false;
	double_open = false;
	while (str[j])
	{
		update_quote_status(str[j], &single_open, &double_open);
		if (str[0] == '~' && !single_open)
			str = handle_til(str, j);
		if (str[j] == '$' && !single_open && (ft_isalnum(str[j + 1]) || str[j
					+ 1] == '_'))
			str = handle_dollar_sign(str, j, single_open);
		j++;
	}
	str = copy_inside_quotes(str);
	return (str);
}

void	update_quote_status(char c, bool *single_open, bool *double_open)
{
	if (c == '\'' && !*double_open)
		*single_open = !*single_open;
	if (c == '\"' && !*single_open)
		*double_open = !*double_open;
}

char	*handle_dollar_sign(char *str, int j, bool single_open)
{
	char	*bef_str;
	char	*aft_str;
	char	*var_name;
	size_t	i;

	if (str[j] == '$' && !single_open)
	{
		bef_str = ft_strndup(str, j);
		i = count_alphanum(str, j);
		if (i < ft_strlen(str))
			aft_str = ft_strdup(str + i);
		else
			aft_str = ft_strdup("");
		var_name = ft_strndup(str + j + 1, i - (j + 1));
		free(str);
		str = expand(bef_str, var_name, aft_str);
	}
	return (str);
}

char	*handle_til(char *str, int j)
{
	char	*bef_str;
	char	*aft_str;
	char	*var_name;
	size_t	i;

	bef_str = ft_strdup("");
	i = count_alphanum(str, j);
	if (i < ft_strlen(str))
		aft_str = ft_strdup(str + i);
	else
		aft_str = ft_strdup("");
	var_name = "HOME";
	free(str);
	str = expand(bef_str, var_name, aft_str);
	return (str);
}

char	*expand(char *before, char *str, char *after)
{
	char	*var_value;
	char	*new_str;
	int		full_string_count;

	var_value = getenv(str);
	if (var_value == NULL)
		var_value = "/";
	full_string_count = ft_strlen(before) + ft_strlen(var_value)
		+ ft_strlen(after) + 1;
	new_str = malloc(full_string_count);
	ft_strlcpy(new_str, before, full_string_count);
	if (*var_value)
		ft_strlcat(new_str, var_value, full_string_count);
	if (*after)
		ft_strlcat(new_str, after, full_string_count);
	free(before);
	before = NULL;
	free(after);
	after = NULL;
	free(str);
	str = NULL;
	return (new_str);
}