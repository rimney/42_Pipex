/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 19:08:04 by rimney            #+#    #+#             */
/*   Updated: 2021/12/24 06:31:14 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



void    ft_apply_input(t_pipe *p, char **argv, char	**cmd1_parser)
{
        int input;

        input = open(argv[1], O_RDONLY);
        if (input == -1)
                exit(0);
        dup2(p->fd[1], 1);
        close(p->fd[1]);
        dup2(input, 0);
       execve(p->cmd1, cmd1_parser, 0);
}

void    ft_apply_output(t_pipe *p, char **argv, char **cmd2_parser)
{
        int output;

        output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if(output == -1)
		{
			perror("no permesions");
                exit(1);
		}
        dup2(p->fd[0], 0);
        dup2(output, 1);
        close(p->fd[1]);
        execve(p->cmd2, cmd2_parser, 0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int i;

	i = 0;
	while(str[i])
		write (fd, &str[i++], 1);
}

int	ft_print_error(char *pname, char *command)
{
	ft_putstr_fd(pname, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void    ft_assign(t_pipe *p, char **argv, char **env)
{
        p->cmd1_path = ft_locate_env(env);
        p->cmd1 = ft_check_command(p->cmd1_path, argv[2]);
        p->cmd2_path = ft_locate_env(env);
        p->cmd2 = ft_check_command(p->cmd2_path, argv[3]);
}

int	ft_check_path(char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		if(ft_strncmp(env[i], "PATH=", 5) == 0)
			return(1);
		i++;
	}
	return(0);
}


int	main(int argc, char **argv, char **env)
{
	t_pipe p;

	if(!ft_check_path(env))
	{
		printf("Invalid path\n");
		exit(127);
	}
	if (argc == 5)
	{
		char	**cmd1_parser = ft_split(argv[2], ' ');
		char	**cmd2_parser = ft_split(argv[3], ' ');
		ft_assign(&p, argv, env);
		if (!p.cmd1)
		return (ft_print_error(argv[0], argv[2]));
			if (!p.cmd2)
				return (ft_print_error(argv[0], argv[3]));
		if(pipe(p.fd) == -1)
			return (0);
		p.pid = fork();
   	 	if (p.pid == -1)
			return (0);
		if (p.pid == 0)
			ft_apply_input(&p, argv, cmd1_parser);
	    waitpid(p.pid, NULL, 0);
    	ft_apply_output(&p, argv, cmd2_parser);
	}
	return(0);
}