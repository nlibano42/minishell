/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xbasabe- <xbasabe-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 12:19:59 by xbasabe-          #+#    #+#             */
/*   Updated: 2022/12/08 02:22:02 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
//# include <stdbool.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <stddef.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
    char	*input;
    char    *parsed_input;
    int		p[2];
    char	**envi; //esto hay que quitar. trasladar todo a struct
//    struct s_env	*env;
	char	*ext_path;
    char	*cmd;
    char	**arg;
    //pid_t   node_pid;
} t_pipe;

typedef struct s_stack
{
    t_pipe          pipe;
    struct s_stack  *next;
    struct s_stack  *prev;
}	t_stack;

typedef struct	s_shell
{
	int				num_quit;
	struct s_env	*env;
}	t_shell;

t_shell	g_shell;

//builtin
int			echo(t_stack *stack, char *input);
void		env(t_stack *node);
void	    pwd(t_stack *node);
void	    unset(char *input);
void        exit_kill(t_stack *node);
int         exec_built_in(char *input, t_stack *node);

//export
char	**export_add(char **envi, char *vbl);
char	**sort_env(char **env);
void    export(char *input, t_stack *node);
void	export_no_args(char **env, t_stack *node);

//cd
char    *active_dir(void);
int     init_cd(char *input, t_stack *node);
void    update_pwd(t_stack *node);
void    expand_relative(t_stack *node);
void    expand_relative2(t_stack *node);
void    cd(char *input, t_stack *node);

//execbash
void    exec_in_child(char *input, t_stack *stack);
pid_t	child_launch(char *input, t_stack *stack);
void    exec_stack(t_stack *stack, char *input);

//execv
int	    launch(char *intro, t_stack *node);
const char	*search_cmd(char *txt);
const char	*path_exe(char *txt);
int	accesible(const char *path);

//in_out
int     is_built(char *input);
int     fd_putstr_out(char *str, t_stack *node);
void    redirect_pipes(t_stack *node);
int     read_pipe(int fd, char *str); //deshuso
int     write_pipe(int fd, char *str); //deshuso

//main
void	clear(char **intro);
void	free_all_params(t_stack **stack, char **input, char ***tokens);

//parse
int     expand(char **txt);
int     expand2(char *txt);
char	*literal(char *input);
int     inside_open_quotes(char *input);
    /*version 1*/
void    quote_in_or_out(char txt, int *count, int *flags);
void    quote_d_count(char *txt, int *count);
void	remove_quote(char *txt, int init);
char    *search_vble_env(char *txt, int init);
char	*parse(char *txt);
int	    OLD_quote_in_or_out(char *txt, int ini);
void    flag_check(int flag, int *flags);
char    *expand_vble(char *txt, int *init);
char    *quote_in_or_out_loop(char *txt, int *count, int *flags);
char    *expand_loop(char *txt);
int     inside_simple(char *txt, int *flags, int *count, int *i);
int     inside_doble(char *txt, int *flags, int *count, int *i);

void	flip_flag(char *txt, int *flags, int *count, int i, int f);


    /*version 2*/
char	*parsing	(char *input);
char    *expand3(char *txt, int init, int end);
int inside_open_quotes2(char *input);
int outside_quotes(char *input);
char	**parse_split(char *input, char c);
int count_words(char *str);
void	fill(char *str, char **word, int index);
void	malloc_split(char *entry, char **splited, int index);



//lexer
void    create_cmds(t_stack **node);
void    cmd_path(t_stack **node);
void    relative_path(t_stack *node);
void    exp_act_path(t_stack *node);
void    exp_up_path(t_stack *node);

//stack
t_stack  *pipe_stack(char * input);
t_stack  *create_node(char *txt);
void            insert_f_pipe(t_stack *node, t_stack *stack);
void            insert_l_pipe(t_stack *node, t_stack *stack);
void            free_stack(t_stack *stack);
void            free_node(t_stack *node);
void            deleteAllNodes(t_stack *start);
void            free_node_content(t_stack *node);

int			str_cmp(char *str1, char *str2);

//reorder
 void    mov_last(t_stack *node, t_stack *stack);
 int     exit_cmd_in_stack(t_stack *stack);
 t_stack *reorder_stack(t_stack *stack);
 t_stack *jump_to(t_stack *stack, int to);
 //void    jump_to(t_stack *stack, int to);
 t_stack *stack_first(t_stack *stack);

//signals
void 	sig_handler(int sig);
void	restore_prompt(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);

//enviroment
void	set_envi(t_env **envi, char **env);
//t_env  *create_vble(char *envi);
//void    insert_env(t_env *envi, t_env *vble);
//void deleteEnviro(t_env *envi);

//lst_env
t_env	*ft_lstnew(char *name, char *val);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstfind(t_env *lst, char *name);
void	ft_lstclear(t_env **lst);
void	ft_lstdelone(t_env *lst);
t_env   *ft_lstlast(t_env *lst);

#endif
