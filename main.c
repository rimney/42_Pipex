/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:14:59 by rimney            #+#    #+#             */
/*   Updated: 2022/01/06 18:38:17 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_apply_input(int *fd, char **argv, char **env)
{
	char	*cmd1;
	char	**cmd_parser;
	int		input;
	char	**cmd_path;

	input = open(argv[1], O_RDONLY);
	cmd_path = ft_locate_env(env);
	cmd1 = ft_check_command(cmd_path, argv[2]);
	cmd_parser = ft_split(argv[2], ' ');
	if (input == -1)
	{
		perror(argv[0]);
		exit(2);
	}
	dup2(fd[1], 1);
	close(fd[1]);
	dup2(input, 0);
	if ((execve(cmd1, cmd_parser, 0) == -1))
	{
		perror(argv[0]);
		exit(127);
	}
}

void	ft_apply_output(int *fd, char **argv, char **env)
{
	int		output;
	char	**cmd_path;
	char	*cmd2;
	char	**cmd_parser;

	output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmd_path = ft_locate_env(env);
	cmd2 = ft_check_command(cmd_path, argv[3]);
	cmd_parser = ft_split(argv[3], ' ');
	dup2(fd[0], 0);
	dup2(output, 1);
	close(fd[1]);
	if ((execve(cmd2, cmd_parser, 0) == -1))
	{
		perror(argv[0]);
		exit(127);
	}
}

int	ft_check_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_pipex(char **argv, char **env)
{
	int	fd[2];
	int	p1;
	int	p2;

	if (pipe(fd) == -1)
		perror(argv[0]);
	p1 = fork();
	if (p1 == -1)
		perror(argv[0]);
	if (p1 == 0)
		ft_apply_input(fd, argv, env);
	p2 = fork();
	if (p2 == -1)
		perror(argv[0]);
	if (p2 == 0)
		ft_apply_output(fd, argv, env);
	close(fd[0]);
	close(fd[1]);
	waitpid(p1, 0, 0);
	waitpid(p2, 0, 0);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		ft_putstr_fd("pipex : Wrong number of arguments \n", 2);
		exit(1);
	}
	if (!ft_check_path(env))
	{
		ft_putstr_fd("pipex : Path not found !\n", 2);
		exit(1);
	}
	ft_pipex(argv, env);
	return (0);
}
