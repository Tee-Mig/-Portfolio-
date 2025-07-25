/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:12:56 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/29 16:41:12 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_pipex
{
	int		**pipefd;
	int		begin_arg;
	int		fd_output;
	int		fd_input;
	int		index_pipe;
	int		id;
	int		i;
	int		fd;
	int		nb_command;
	int		index_pid;
	int		nb_arg;
	int		*pid;
	char	*line;
	char	**path;
	char	**commands;
}t_pipex;

int		find_nb_arg(char *str);
int		ft_strlen(char *str);
int		ft_strncmp(const void *s1, const void *s2, size_t n);
int		path_error(t_pipex *pipex);
int		open_file(char *file, char status);
int		ft_verif_n(char *str);
int		ft_strcmp(char *s1, char *s2);
int		add_end_path(t_pipex *pipex);
int		get_path_env(t_pipex *pipex, char **envp);
int		init_pid_and_pipe(t_pipex *pipex, int ac);
int		add_end_path(t_pipex *pipex);
int		malloc_pipe(t_pipex *pipex);
int		init_here_doc(t_pipex *pipex);
int		check_error_line(t_pipex *pipex);
int		if_here_doc(t_pipex *pipex, char **av);
int		first_pipe(t_pipex *pipex, char **av, char **envp);
int		middle_pipe(t_pipex *pipex, char **av, char **envp, int ac);
int		init_middle_pipe(t_pipex *pipex);
int		last_pipe(t_pipex *pipex, char **av, char **envp);
int		first_pipe(t_pipex *pipex, char **av, char **envp);
int		init_no_here_doc(t_pipex *pipex, char **av, int ac);
int		init_file_here_doc(t_pipex *pipex, char **av, int ac);

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*get_next_line(int fd);

char	**ft_split(char *s, char c);

void	exec_command(t_pipex *pipex, char **av, char **envp);
void	close_fds(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	if_command_not_found(t_pipex *pipex);
void	if_arg(t_pipex *pipex);
void	execute_command(t_pipex *pipex, char **envp, char *path_exec);
void	ft_process_bonus(char **av, char **envp, t_pipex *pipex, int ac);
void	free_tab(char **tab);
void	ft_putstr(char *str);
void	error1_pipe(t_pipex *pipex);
void	error2_pipe(t_pipex *pipex);
void	error_here_doc(t_pipex *pipex);
void	error_first_pipe(t_pipex *pipex);
void	error_middle_pipe(t_pipex *pipex);
void	error_last_pipe(t_pipex *pipex);

#endif