/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script_term.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponcele <jponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 13:16:21 by jponcele          #+#    #+#             */
/*   Updated: 2014/05/02 13:16:23 by jponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_script.h>

void				ft_set_old_term(t_env *env)
{
	ioctl(STDIN_FILENO, TIOCSETA, &(env->old_term));
}

void				ft_get_termios(t_env *env)
{
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &(env->ws)) < 0)
		err_exit("ioctl get winsize", env);
	if (ioctl(STDIN_FILENO, TIOCGETA, &(env->old_term)) < 0)
		err_exit("ioctl get old termios", env);
	env->new_term = env->old_term;
	env->new_term.c_lflag &= ~ECHO;
	env->new_term.c_lflag &= ~ICANON;
	if (ioctl(STDIN_FILENO, TIOCSETA, &(env->new_term)) < 0)
		err_exit("ioctl set new termios", env);
}

int					ft_script_select_stdout(t_env *env, int fd_master)
{
	int				ret;
	char			buf[BUFF_SIZE];

	if ((ret = read(STDIN_FILENO, buf, BUFF_SIZE)) < 0)
		err_exit("read STDIN_FILENO", env);
	if (ret == 0)
		return (-1);
	if (write(fd_master, buf, ret) != ret)
		err_exit("partial/failed write (masterFd)", env);
	return (0);
}

int					ft_script_select_stdin(t_env *env, int fd_master)
{
	int				ret;
	char			buf[BUFF_SIZE];

	if ((ret = read(fd_master, buf, BUFF_SIZE)) < 0)
		err_exit("read masterfd", env);
	if (ret == 0)
		return (-1);
	if (write(STDOUT_FILENO, buf, ret) != ret)
		err_exit("write STDOUT_FILENO", env);
	if (write(env->fd_file, buf, ret) != ret)
		err_exit("write file", env);
	return (0);
}
