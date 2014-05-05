/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptyfork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponcele <jponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 13:16:26 by jponcele          #+#    #+#             */
/*   Updated: 2014/05/02 13:16:28 by jponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_script.h>

void			ptyfork_verif_fd_slave(char *slname)
{
	int			fd_slave;

	if (((fd_slave = open(slname, O_RDWR)) == -1)
			|| (ioctl(fd_slave, TIOCSCTTY, 0) == -1)
			|| (dup2(fd_slave, STDIN_FILENO) != STDIN_FILENO)
			|| (dup2(fd_slave, STDOUT_FILENO) != STDOUT_FILENO)
			|| (dup2(fd_slave, STDERR_FILENO) != STDERR_FILENO))
		_exit(1);
	if (fd_slave > STDERR_FILENO)
		close(fd_slave);
}

pid_t			ptyfork(int *fd_master, char *slave_name, size_t sln_len)
{
	pid_t		pid;
	char		slname[MAX_SNAME];

	if ((*fd_master = pty_master_open(slname, MAX_SNAME)) == -1)
		return (-1);
	if (slave_name != NULL)
	{
		if ((size_t)ft_strlen(slname) < sln_len)
			ft_strncpy(slave_name, slname, sln_len);
		else
			return (close(*fd_master) - 1);
	}
	pid = fork();
	if (pid == -1)
		return (close(*fd_master) - 1);
	if (pid != 0)
		return (pid);
	if (setsid() == -1)
		_exit(1);
	close(*fd_master);
	ptyfork_verif_fd_slave(slname);
	return (0);
}
