/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:58:40 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/14 20:46:51 by xbasabe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_split_tokens(int *index, int *flags)
{
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	flags[0] = 1;
	flags[1] = 1;
}

char	**split_tokens(char *txt)
{
	int		flags[2];
	char	**tokens;
	char	temp[999];
	int		index[3];

	init_split_tokens(index, flags);
	tokens = (char **)malloc((sizeof(char *) * 20));
	while (txt[index[0]] != '\0')
	{
		if (txt[index[0]] == 39)
			split_tokens_s(flags, txt, temp, index);
		if (str_cmp(txt, "opened quotes in command line") == 0)
			return (NULL);
		else if (txt[index[0]] == 34)
			split_tokens_d(flags, txt, temp, index);
		if (str_cmp(txt, "opened quotes in command line") == 0)
			return (NULL);
		else if (txt[index[0]] == '|')
		{
			remove_quote(txt, index[0]);
			temp[index[1]] = '\0';
			tokens[index[2]] = ft_strdup(temp);
			index[2] = index[2] + 1;
			index[1] = 0;
		}
		temp[index[1]] = txt[index[0]];
		index[0] = index[0] + 1;
		index[1] = index[1] + 1;
	}
	temp[index[1]] = '\0';
	tokens[index[2]] = ft_strdup(temp);
	tokens[index[2] + 1] = NULL;
	return (tokens);
}

void	split_tokens_s(int *flags, char *txt, char *temp, int *index)
{	
	if (flags[0] != -1 && flags[1] != -1)
	{
		flag_change(txt, flags, &index[0], 1);
		while (txt[index[0]] != 39)
		{
			temp[index[1]] = txt[index[0]];
			if (txt[index[0]] == '\0')
			{
				printf("opened quotes in command line\n");
				txt = strdup("opened quotes in command line\n");
				g_shell.num_quit = 1;
				return ;
			}	
			index[0] = index[0] + 1;
			index[1] = index[1] + 1;
		}
		flag_change(txt, flags, &index[0], 1);
	}
}

void	split_tokens_d(int *flags, char *txt, char *temp, int *index)
{
	if (flags[1] != -1 && flags[0] != -1)
	{
		flag_change(txt, flags, &index[0], 0);
		while (txt[index[0]] != 34)
		{
			temp[index[1]] = txt[index[0]];
			if (txt[index[0]] == '\0')
			{
				printf("opened quotes in command line\n");
				txt = strdup("opened quotes in command line\n");
				g_shell.num_quit = 1;
				return ;
			}
			index[0] = index[0] + 1;
			index[1] = index[1] + 1;
		}
		flag_change(txt, flags, &index[0], 0);
	}
}

void	flag_change(char *txt, int *flags, int *i, int f)
{
	int	init;

	init = *i;
	flags[f] = flags[f] * -1;
	remove_quote(txt, init);
}
