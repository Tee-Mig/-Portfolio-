/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 20:28:14 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/03/16 20:42:39 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	int		pipefd[2];
	int		id1;
	int		id2;
	int		nb_arg_2;
	int		nb_arg_3;
	int		i;
	int		fd1;
	int		fd2;
	char	*tmp;
	char	*cmd1;
	char	**path;
	char	**pathcp;
	char	**commands1;
	char	**commands2;
}t_pipex;

int		ft_parsing(char **av);
int		find_nb_arg(char *str);
int		ft_strlen(char *str);
int		ft_strncmp(const void *s1, const void *s2, size_t n);
int		path_error(t_pipex *pipex);
int		get_path(char **av, char **envp, t_pipex *pipex);
int		get_path_error(t_pipex *pipex);
int		get_path2(t_pipex *pipex, char **av);
int		get_path_error2(t_pipex *pipex);
int		get_path3(t_pipex *pipex, char **av);
int		ft_open_pipe(t_pipex *pipex, char **av);
int		process_child1(t_pipex *pipex, char **envp);
int		process_child2(t_pipex *pipex, char **envp, char **av);
int		process2_child2(t_pipex *pipex, char **envp);
int		error_message(t_pipex *pipex);

void	ft_process(char **av, char **envp);
void	free_tab(char **tab);
void	ft_putstr(char *str);
void	free_end(t_pipex *pipex);
void	error_child1(t_pipex *pipex);
void	error_child2(t_pipex *pipex);
void	second_error_child2(t_pipex *pipex);
void	exec_command2(t_pipex *pipex, char **envp);
void	exec_command1(t_pipex *pipex, char **envp);

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);

char	**ft_split(char *s, char c);

#endif