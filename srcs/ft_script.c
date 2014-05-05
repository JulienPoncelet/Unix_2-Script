/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponcele <jponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 13:12:13 by jponcele          #+#    #+#             */
/*   Updated: 2014/05/02 15:27:24 by jponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_script.h>

void					exec_cmd(t_env *env, char **av, char **e)
{
	pid_t				pid;
	int					masterfd;
	char				slave_name[MAX_SNAME];

	ft_get_termios(env);
	if ((pid = ptyfork(&masterfd, slave_name, MAX_SNAME)) < 0)
		err_exit("ptyfork", env);
	if (!pid)
	{
		execve(env->shell, av, e);
		err_exit("execve", env);
	}
	while (42)
	{
		if (ft_script_select(env, masterfd) < 0)
			return ;
	}
}

int						ft_script_select(t_env *env, int fd_master)
{
	fd_set				fds;

	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	FD_SET(fd_master, &fds);
	if (select(fd_master + 1, &fds, NULL, NULL, NULL) < 0)
		err_exit("select", env);
	if (FD_ISSET(STDIN_FILENO, &fds))
	{
		if (ft_script_select_stdout(env, fd_master) < 0)
			return (-1);
	}
	if (FD_ISSET(fd_master, &fds))
	{
		if (ft_script_select_stdin(env, fd_master) < 0)
			return (-1);
	}
	return (0);
}

void					start_script(t_env *env, char **av, char **e)
{
	struct timeval		t;
	time_t				time;

	open_log(env);
	gettimeofday(&t, NULL);
	time = (time_t)t.tv_sec;
	if (!env->opt[F_Q])
	{
		ft_putstr("Script started, output file is ");
		ft_putendl(env->file_name);
		write(env->fd_file, "Script started on ", 18);
		write(env->fd_file, ctime(&time), ft_strlen(ctime(&time)));
	}
	exec_cmd(env, av, e);
	ft_set_old_term(env);
	if (!env->opt[F_Q])
	{
		write(env->fd_file, "Script done on ", 15);
		write(env->fd_file, ctime(&time), ft_strlen(ctime(&time)));
		close(env->fd_file);
		ft_putstr("Script done, output file is ");
		ft_putendl(env->file_name);
	}
}

int						main(int ac, char **av, char **e)
{
	static t_env		env;

	ac--;
	av++;
	ft_strcpy(env.shell, get_shell(e));
	av = get_option(av, &env);
	av = morph_av(av, env.shell);
	start_script(&env, av, e);
	return (0);
}
