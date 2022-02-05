/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:14:44 by rimney            #+#    #+#             */
/*   Updated: 2022/01/06 18:25:01 by rimney           ###   ########.fr       */
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

char	**ft_split(char const *s, char c);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_locate_env(char **env);
char	*ft_strdup(char *src);
int		ft_is_space(char *str);
char	*ft_filter_command(char *command);
char	*ft_check_command(char **env, char *command);
void	ft_apply_input(int *fd, char **argv, char **env);
void	ft_apply_output(int *fd, char **argv, char **env);
void	ft_putstr_fd(char *str, int fd);
#endif