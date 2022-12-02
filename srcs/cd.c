#include "minishell.h"

char    *active_dir(char **envi)
{
    char	**var;
	int		i;

	i = 0;
	while (envi[i])
	{
		var = ft_split(envi[i], '=');
		if (str_cmp(var[0], "PWD") == 0)
        {
            break ;
            //return(var[1]);
        }
		i++;
		clear(var);
	}
    return(var[1]);
}

char    *old_dir(char **envi)
{
    char	**var;
	int		i;

	i = 0;
	while (envi[i])
	{
		var = ft_split(envi[i], '=');
		if (str_cmp(var[0], "OLDPWD") == 0)
        {
            break ;
            //return(var[1]);
        }
		i++;
		clear(var);
	}
    return(var[1]);
}

int    init_cd(char *input, char **envi, t_stack *node)
{
    (void) input;
    if (node->pipe.arg[0] == NULL)
        node->pipe.arg[0] = getenv("HOME"); //ir a HOME definido en envi asi vamos a la del env
    else if (node->pipe.arg[0])
    {
        if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '/')
            expand_relative(envi, node);
        if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '.' && node->pipe.arg[0][2] == '/')
            expand_relative2(envi, node);
        if (strcmp(node->pipe.arg[0], "-") == 0 && !node->pipe.arg[1])  //usar los valores de node->pipe.arg cd - nos devuelve a la capreta donde estabamos
            node->pipe.arg[0] = old_dir(envi);
    }
    else if(node->pipe.arg[2] != NULL)
    {
        fd_putstr_out("-Minishell: cd: too many arguments\n", node);
        return (1);
    }
    return (0);
}

void    update_pwd(char **envi, t_stack *node) //modifica en envi no pasa a sistema para los no built in
{
	char *new_input;
    char **var;
    char **envi_var;
    int    j;

    if(access((const char*)node->pipe.arg[0], F_OK) == -1) //comprobar que hay acceso al directorio
	{
		printf("-Minishell: cd: %s: No such file or directory\n", node->pipe.arg[0]); //NO es ft_putstr_out, se imprime siempre
		return ; //handle error
	}
    new_input = stradd("PWD=", node->pipe.arg[0]);
    var = ft_split(new_input, '=');
	j = -1;
	while (envi[++j])
	{
		//cojer de env y de arg hasta el = y compara, comparar el nombre de vble
		envi_var = ft_split(envi[j], '=');
		if (str_cmp(envi_var[0], var[0]) == 0) 
		{
			ft_strcpy(envi[j], new_input);
			clear(envi_var);
			break ;
		}
		clear(envi_var);
	}
    clear(var);
}

void    update_oldpwd(char **envi, char *old_dir) //modifica en envi no pasa a sistema para los no built in
{
	int		i;
    char    **line;

    i = 0;
	while (envi[i])
	{
		line = ft_split(envi[i], '=');
		if (str_cmp("OLDPWD", line[0]) == 0)
		{
            //envi[i] = "OLDPWD";
            ft_strcpy(envi[i], "OLDPWD");
            envi[i] = stradd(envi[i], "=");
			envi[i] = stradd(envi[i], old_dir);
            
            clear(line);
			return ;
		}
		i++;
	}
    clear(line);
}

void    expand_relative(char **envi, t_stack *node)
{
    char    *exp_dir;

    exp_dir = active_dir(envi);
    node->pipe.arg[0]++; //cambiar esto?
    exp_dir = stradd(exp_dir, node->pipe.arg[0]);
    node->pipe.arg[0] = exp_dir;
}

void    expand_relative2(char **envi, t_stack *node)
{
    char    *exp_dir;
    char    *tmp;
    int     i;

    exp_dir = active_dir(envi);
    i = ft_strlen(exp_dir);
    while(exp_dir[i] != '/')
        i--;
    tmp = (char *)malloc(sizeof(char) * (i + 2));
    tmp[i + 1] = '\0';
    while(i >= 0)
    {
        tmp[i] = exp_dir[i];
        i--;
    }
    node->pipe.arg[0]++;
    node->pipe.arg[0]++;
    node->pipe.arg[0]++;
    exp_dir = tmp;
    exp_dir = stradd(exp_dir, node->pipe.arg[0]);
    printf("Expand ../ --> %s\n", exp_dir);
    node->pipe.arg[0] = exp_dir;
}

void	cd(char *input, char **envi, t_stack *node)
{
	char	*old_dir;
	char	**var;
	int		i;

	i = 0;
	while (envi[i]) //get active dir
	{
		var = ft_split(envi[i], '=');
		if (str_cmp(var[0], "PWD") == 0)
        {
			old_dir = var[1];
            break ;
        }
		i++;
		clear(var);
	}
    if (init_cd(input, envi, node) == 0)
        update_pwd(envi, node);
    //old_dir = stradd("OLDPWD=", old_dir);
    printf("guardamos old dir: %s\n", old_dir); //convertir en export y añadir a envi OLDPWD
    update_oldpwd(envi, old_dir);
    clear(var);
    //free(node->pipe.arg);
}
