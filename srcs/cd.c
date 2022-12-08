#include "minishell.h"

char    *active_dir(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
            return(env->val);
		env = env->next;
	}
    return(env->val);
}

char    *old_dir(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "OLDPWD") == 0)
            return(env->val);
		env = env->next;
	}
    return(env->val); // esto es NULL???
}

int    init_cd(char *input, t_stack *node)
{
    (void) input;
    if (node->pipe.arg[0] == NULL)
        node->pipe.arg[0] = getenv("HOME"); //ir a HOME definido en envi asi vamos a la del env
    else if (node->pipe.arg[0])
    {
        if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '/')
            expand_relative(node);
        if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '.' && node->pipe.arg[0][2] == '/')
            expand_relative2(node);
        if (strcmp(node->pipe.arg[0], "-") == 0 && !node->pipe.arg[1])  //usar los valores de node->pipe.arg cd - nos devuelve a la capreta donde estabamos
            node->pipe.arg[0] = old_dir();
    }
    else if(node->pipe.arg[2] != NULL)
    {
        fd_putstr_out("-Minishell: cd: too many arguments\n", node);
        return (1);
    }
    return (0);
}

void    update_pwd(t_stack *node) //modifica en envi no pasa a sistema para los no built in
{
	t_env	*env;

	env = g_shell.env;
    if(access((const char*)node->pipe.arg[0], F_OK) == -1) //comprobar que hay acceso al directorio
	{
		printf("-Minishell: cd: %s: No such file or directory\n", node->pipe.arg[0]); //NO es ft_putstr_out, se imprime siempre
		return ; //handle error
	}
    
	while (env)
	{
		//cojer de env y de arg hasta el = y compara, comparar el nombre de vble
		if (str_cmp(env->name, "PWD") == 0) 
		{
			//ft_strcpy(envi[j], new_input);
            env->val = node->pipe.arg[0];
			break ;
		}
		env = env->next;
	}
}

void    update_oldpwd(char *old_dir) //modifica en envi no pasa a sistema para los no built in
{
	t_env	*env;

	env = g_shell.env;
    /*
    if(access((const char*)node->pipe.arg[0], F_OK) == -1) //comprobar que hay acceso al directorio
	{
		printf("-Minishell: cd: %s: No such file or directory\n", node->pipe.arg[0]); //NO es ft_putstr_out, se imprime siempre
		return ; //handle error
	}
    */
	while (env)
	{
		//cojer de env y de arg hasta el = y compara, comparar el nombre de vble
		if (str_cmp(env->name, "OLDPWD") == 0) 
		{
			//ft_strcpy(envi[j], new_input);
            env->val = old_dir;
			break ;
		}
	env = env->next;
	}
}

void    OLD_update_oldpwd(char *old_dir) //modifica en envi no pasa a sistema para los no built in
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp("OLDPWD", env->name) == 0)
		{
            //envi[i] = "OLDPWD";
            //ft_strcpy(envi[i], "OLDPWD");
            //envi[i] = stradd(envi[i], "=");
			//envi[i] = stradd(envi[i], old_dir);
            env->val = old_dir;
			return ;
		}
		env = env->next;
	}
}

void    expand_relative(t_stack *node)
{
    char    *exp_dir;

    exp_dir = active_dir();
    node->pipe.arg[0]++; //cambiar esto?
    exp_dir = stradd(exp_dir, node->pipe.arg[0]);
    node->pipe.arg[0] = exp_dir;
}

void    expand_relative2(t_stack *node)
{
    char    *exp_dir;
    char    *tmp;
    int     i;

    exp_dir = active_dir();
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

void	cd(char *input, t_stack *node)
{
	t_env	*env;
	char	*old_dir;

	env = g_shell.env;
	old_dir = NULL;
	while (env) //get active dir
	{
		if (str_cmp(env->name, "PWD") == 0)
        {
			old_dir = ft_strdup(env->val);
            break ;
        }
		env = env->next;
	}
    if (init_cd(input, node) == 0)
        update_pwd(node);
    //old_dir = stradd("OLDPWD=", old_dir);
//    printf("guardamos old dir: %s\n", old_dir); //convertir en export y añadir a envi OLDPWD
    update_oldpwd(old_dir);
    if (old_dir)
		free(old_dir);
    //free(node->pipe.arg);
}
