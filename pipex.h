/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 21:57:59 by rimney            #+#    #+#             */
/*   Updated: 2021/12/24 06:30:34 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipe
{
	pid_t	pid;
	int		fd[2];
	char	**cmd1_path;
	char	*cmd1;
	char	**cmd2_path;
	char	*cmd2;
}	t_pipe;

char	**ft_split(char const *s, char c);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_locate_env(char **env);
char	*ft_strdup(char *src);
int		ft_is_space(char *str);
char	*ft_filter_command(char *command);
char	*ft_check_command(char **env, char *command);
void	ft_assign_data(t_pipe *pipe, char **argv, char **env);
void    ft_apply_input(t_pipe *p, char **argv, char	**cmd1_parser);
void	ft_apply_output(t_pipe *p, char **argv, char **cmd2_parser);
#endif