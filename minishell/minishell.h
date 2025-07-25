/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:54:04 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/06/03 12:53:54 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>

# define WRITE_PIPE 1
# define READ_PIPE 0

extern unsigned char	g_exit_status;

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
	char			*status;
}t_node;

typedef struct s_dlist
{
	int				size;
	int				nb_pipe;
	struct s_node	*head;
	struct s_node	*end;
	size_t			id_first_quote;
	size_t			id_last_quote;
	char			*unquoted_content;
	char			*tmp_content;
	int				*norm_helper1;
	int				*norm_helper2;
}t_dlist;

typedef struct s_command
{
	char		**exec_array;
	int			pipe_fd[2];
	int			fd_in;
	int			fd_out;
	int			status_exec;
	pid_t		pid;
	int			find_var;
	int			plus_status;
}t_command;

typedef struct s_minishell
{
	char		*input;
	char		**path;
	t_dlist		*tokens;
	t_command	*command;
	t_dlist		*garbage_collector;
	int			state_token;
	char		**cp_envp;
	int			i;
	int			j;
	int			k;
	char		*token;
	char		*token2;
	char		*char_tmp;
	char		*tmp;
	char		*path_exec;
	t_node		*tmp2;
	t_node		*tmp4;
	t_node		*tmp5;
	t_node		*tmp6;
	int			l;
	int			m;
	int			nb_exec_array;
	int			return_val;
	int			return_val2;
	int			return_val3;
	int			return_val4;
	DIR			*directory;
	int			fd_exec;
	int			pid_status;
	char		*tmp_free;
	char		*path_exec2;
	int			x;
	int			y;
	int			z;
	int			i_main;
	t_node		*tmp_main;
	t_node		*tmp2_main;
	char		*var_path;
	char		*var_expand;
	char		*cp_tmp;
}t_minishell;

int		check_quote(char *input);
int		ft_strncmp(void *s1, void *s2, size_t n);
char	*ft_strjoin(char *s1, char s2);
char	*ft_strdup(char *s);
size_t	ft_strlen(const char *str);
int		ft_isalnum(int c);
char	**ft_split(char *str, char *charset);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strchr(const char *str, int c);
t_dlist	*ft_lstnew(void);
int		add_last(t_dlist *lst, void *elem);
void	rm_last_node(t_dlist *lst);
void	free_list(t_dlist *lst);
void	del_node2(t_node *del, int idx, t_node *tmp, t_dlist *list);
int		del_node(t_dlist *list, int idx);
int		is_delimiter(char str);
void	get_token(t_minishell *info);
char	**ft_cpy_envp(char **envp);
int		ft_strcmp(char *s1, char *s2);
int		add_end_path(t_minishell *info, int *i);
char	*ft_strjoin_str(char *s1, char *s2);
void	free_tab(char **tab);
int		token_into_cmd(t_minishell *info);
int		is_delimiter_str(char *str);
long	ft_atoi(char *str);
void	expand_exit_status(t_minishell *info, t_dlist *tok, int i,
			char *g_status_char);
void	var_to_expand(t_minishell *info, t_dlist *tok, int i);
char	*ft_expand(t_minishell *info, t_dlist *tok, char *quote, int i);
void	sig_init(void);
void	sig_init2(void);

//builtins
void	ft_cd(t_minishell *info, int i);
void	ft_echo(t_minishell *info, int i);
void	ft_pwd(t_minishell *info, int i, char *option);
int		ft_unset(t_minishell *info, char *var);
int		ft_export(t_minishell *info, char *var, int id);
int		ft_env(t_minishell *info, int i, int status);
int		ft_exit(t_minishell *info, int status, int i);
int		export_syntax(t_minishell *info, char *var, int id, int *j);
int		export_identifier_envp(t_minishell *info, char *var, int id, int j);
int		check_var(t_minishell *info, char *var, int id, int j);
int		export_nofindvar1(t_minishell *info, char *var, int id, int i);
void	export_nofindvar2(t_minishell *info, char *var, int id, char **cpy_env);
void	export_findvar(t_minishell *info, char *var, int id, int j);

int		ft_heredoc(char *delimiter);
int		update_path(t_minishell *info);
void	ft_putstr_fd(char *s, int fd);
int		update_oldpath(t_minishell *info);
char	*ft_itoa(int nb);

char	*get_next_line(int fd);
int		ft_verif_n(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	update_g_status(char *status, int fd_g_status);

int		ft_remove_quote(t_minishell *info, t_dlist *tokens);
int		get_path_env(t_minishell *info, char **envp);
int		get_path_env2(t_minishell *info, char **envp);

// PARSING
void	get_token_part1(t_minishell *info);
void	get_token_part2(t_minishell *info);
void	get_if_no_sep(t_minishell *info);
int		if_cmd_or_error(t_minishell *info);
void	get_token_sep(t_minishell *info);
void	get_no_sep(t_minishell *info);
void	get_token_quote(t_minishell *info);

// TOKEN INTO CMD
void	do_heredoc(t_minishell *info);
int		do_append(t_minishell *info);
int		do_replace(t_minishell *info);
int		do_read(t_minishell *info);
int		check_redir(t_minishell *info);
int		check_redir2(t_minishell *info);
void	get_nb_of_element(t_minishell *info);
int		fill_array(t_minishell *info);
int		get_exec_array(t_minishell *info);

// EXEC_CMD
int		exec_cmd(t_minishell *info);
int		exec_cmd_loop(t_minishell *info);
int		exec_last_cmd(t_minishell *info);
int		exec_cmd_parent_loop(t_minishell *info);
void	wait_childs(t_minishell *info);
void	check_builtins_status(t_minishell *info);
void	exec_builtins3(t_minishell *info);
void	exec_builtins2(t_minishell *info);
void	exec_builtins(t_minishell *info);
void	dup2_loop_child(t_minishell *info);
void	close_pipe_loop_child(t_minishell *info);
void	exec_abs_path_child_loop2(t_minishell *info);
void	exec_abs_path_child_loop(t_minishell *info);
void	exec_relative_path_find_loop_child2(t_minishell *info);
void	exec_relative_path_find_loop_child(t_minishell *info);
void	exec_relative_path_child_loop2(t_minishell *info);
void	exec_relative_path_child_loop(t_minishell *info);
void	dup2_child_last(t_minishell *info);
void	close_pipes_child_last(t_minishell *info);
void	exec_abs_child_last2(t_minishell *info);
void	exec_abs_child_last(t_minishell *info);
void	exec_relative_find_last2(t_minishell *info);
void	exec_relative_find_last(t_minishell *info);
void	close_pipes_relative_child_last(t_minishell *info);
void	exec_relativ_child_last2(t_minishell *info);
void	exec_relativ_child_last(t_minishell *info);
void	close_pipes_parent_last(t_minishell *info);
void	builtins_close_pipe_end(t_minishell *info);
void	close_directory(t_minishell *info);

//MAIN
int		ft_init(t_minishell *info, char **envp);
int		ft_read_input(t_minishell *info);
int		if_input_valid(t_minishell *info);
int		free_tokens(t_minishell *info);
void	free_end(t_minishell *info);
void	error_malloc_cmd(t_minishell *info);

#endif
