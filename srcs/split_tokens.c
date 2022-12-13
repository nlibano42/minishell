
#include "minishell.h"


char	**token_add(char **dst, const char *s,  size_t i, size_t len)
{
	dst[i] = (char *)malloc(sizeof(char) * len + 1);
	if (!dst[i])
	{
		while (i)
			free (dst[--i]);
		free(dst);
		return (NULL);
	}
	ft_strlcpy(dst[i], s - len, len + 1);
	return (dst);
}

void	flag_change(char *txt, int *flags, int i, int f)
{
	int	init;

	init = i;
	flags[f] = flags[f] * -1;
	remove_quote(txt, init);
}


char	**split_tokens_add(char *txt)
{
	int		i;
	//int		*j;
	int		flags[2];
	char	**tokens;
	//char	*temp;
	char	temp[999];
	int		d;
	int		c;

	i = 0;
	d = 0;
	//j = &i;
	c = 0;
	flags[0] = 1;
	flags[1] = 1;
	//temp = (char *)malloc(sizeof(char) * ft_strlen(txt) + 1);
	//temp = NULL;
	tokens = (char **)malloc((sizeof(char *) * 1) + 1);
	//tokens = (char **)malloc((sizeof(char *) * 20));
	while (txt[i] != '\0')
	{
		if (txt[i] == 39) // simples ' 39 ascci de '
		{
			if (flags[0] != -1 && flags[1] != -1)//dentro, entramos simples (ignorar dentro las dobles)
			{
				flag_change(txt, flags, i, 1);
				while (txt[i] != 39) // 39 es el ascii de '
				{
					temp[d] = txt[i];
					if (txt[i] == '\0')
					{
						printf("opened quotes in command line\n");
						g_shell.num_quit = 1;
						exit(1);
					}	
					i++;
					d++;
				}
				flag_change(txt, flags, i, 1);
			}
		}
		else if (txt[i] == 34) //34 es el ascci de ""
		{
			if (flags[1] != -1 && flags[0] != -1) //dentro, entramos dobles (ignorar dentro las simples)
			{
				flag_change(txt, flags, i, 0);
				while (txt[i] != 34)
				{
					temp[d] = txt[i];
					if (txt[i] == '\0')
					{
						printf("opened quotes in command line\n");
						g_shell.num_quit = 1;
						exit(1);
					}
					i++;
					d++;
				}
				flag_change(txt, flags, i, 0);
			}
		}
		else if (txt[i] == '|')
		{
			remove_quote(txt, i);
			temp[d] = '\0';
			//tokens[c] = ft_strdup(temp);
			//tokens[c] = temp;
			tokens = token_add(tokens, temp, c, ft_strlen(temp) + 1);
			c++;
			d = 0;
		}
		temp[d] = txt[i];
		i++;
		d++;
	}
	temp[d] = '\0';
	//tokens[c] = ft_strdup(temp);
	//tokens[c] = temp;
	tokens = token_add(tokens, temp, c, ft_strlen(temp) + 1);
	//tokens[c + 1] = NULL;
	return (tokens);
}


char	**split_tokens(char *txt)
{
	int		i;
	//int		*j;
	int		flags[2];
	char	**tokens;
	//char	*temp;
	char	temp[999];
	int		d;
	int		c;

	i = 0;
	d = 0;
	//j = &i;
	c = 0;
	flags[0] = 1;
	flags[1] = 1;
	//temp = (char *)malloc(sizeof(char) * ft_strlen(txt) + 1);
	//temp = NULL;
	tokens = (char **)malloc((sizeof(char *) * 20));
	while (txt[i] != '\0')
	{
		if (txt[i] == 39) // simples ' 39 ascci de '
		{
			if (flags[0] != -1 && flags[1] != -1)//dentro, entramos simples (ignorar dentro las dobles)
			{
				flag_change(txt, flags, i, 1);
				while (txt[i] != 39) // 39 es el ascii de '
				{
					temp[d] = txt[i];
					if (txt[i] == '\0')
					{
						printf("opened quotes in command line\n");
						g_shell.num_quit = 1;
						exit(1);
					}	
					i++;
					d++;
				}
				flag_change(txt, flags, i, 1);
			}
		}
		else if (txt[i] == 34) //34 es el ascci de ""
		{
			if (flags[1] != -1 && flags[0] != -1) //dentro, entramos dobles (ignorar dentro las simples)
			{
				flag_change(txt, flags, i, 0);
				while (txt[i] != 34)
				{
					temp[d] = txt[i];
					if (txt[i] == '\0')
					{
						printf("opened quotes in command line\n");
						g_shell.num_quit = 1;
						exit(1);
					}
					i++;
					d++;
				}
				flag_change(txt, flags, i, 0);
			}
		}
		else if (txt[i] == '|')
		{
			remove_quote(txt, i);
			temp[d] = '\0';
			tokens[c] = ft_strdup(temp);
			//tokens[c] = temp;
			c++;
			d = 0;
		}
		temp[d] = txt[i];
		i++;
		d++;
	}
	temp[d] = '\0';
	tokens[c] = ft_strdup(temp);
	//tokens[c] = temp;
	tokens[c + 1] = NULL;
	return (tokens);
}



/* separar los bucles de comillas para pasar norma
split_tokens_simples()

split_tokens_doubles()
*/