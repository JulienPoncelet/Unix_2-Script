/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptyopen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponcele <jponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 13:16:31 by jponcele          #+#    #+#             */
/*   Updated: 2014/05/02 13:16:33 by jponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_script.h>

int					pty_master_open(char *slave_name, size_t sln_len)
{
	int				masterfd;
	char			*x;
	char			*y;
	char			master_name[PTY_NAME_LEN];

	ft_memset(master_name, 0, PTY_NAME_LEN);
	ft_strncpy(master_name, PTYM_PREFIX, PTY_PREFIX_LEN);
	x = X_RANGE;
	while (x)
	{
		master_name[PTY_PREFIX_LEN] = *x;
		y = Y_RANGE;
		while (y)
		{
			master_name[PTY_PREFIX_LEN + 1] = *y;
			slave_name = ft_strncpy(slave_name, master_name, sln_len);
			slave_name = ft_strncpy(slave_name, PTYS_PREFIX, PTY_PREFIX_LEN);
			if ((masterfd = open(master_name, O_RDWR)) > 0)
				return (masterfd);
			y++;
		}
		x++;
	}
	slave_name = NULL;
	return (-1);
}
