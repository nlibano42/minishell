
#include "minishell.h"

char	*quote_in_or_out_loop(char *txt)
{
	int	i;
	int	*j;
	int	flags[2];

	i = 0;
	j = &i;
	while (txt[i] != '\0')
	{
		if (txt[i] == 39) // simples ' 39 ascci de '
		{	
			if (flags[0] != -1)//dentro, entramos simples (ignorar dentro las dobles)
			{
				flip_flag(txt, flags, i, 1);
				while (txt[i] != 39) // 39 es el ascii de '
				{
					if (txt[i] == '\0')
						return (NULL);
					i++;
				}
				flip_flag(txt, flags, i, 1);
			}
		}
		else if (txt[i] == 34) //34 es el ascci de ""
		{
			if (flags[1] != -1) //dentro, entramos dobles (ignorar dentro las simples)
			{
				flag_change(txt, flags, count, i, 0);
				while (txt[i] != 34)
				{
					if (txt[i] == '\0')
					{
						return (NULL);
					}
					if (txt[i] == 36) //36 es el ascci de $
					{
						txt = expand_vble(txt, j);
					}
					i++;
				}
				flag_change(txt, flags, count, i, 0);
			}
		}
		else if (txt[i] == 36) //36 es el ascci de $
		{	
			txt = expand_vble_out(txt, j);
		}
		else if (txt[i] == 39 || txt[i] == 34)
			return (NULL);
		i++;
	}
	return (txt);
}

void	flag_change(char *txt, int *flags, int i, int f)
{
	int	init;

	init = i;
	flags[f] = flags[f] * -1;
	remove_quote(txt, init);
}
