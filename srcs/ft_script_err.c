/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponcele <jponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 13:16:09 by jponcele          #+#    #+#             */
/*   Updated: 2014/05/02 13:24:11 by jponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_script.h>

void				err_usage(unsigned char c)
{
	ft_putstr("./ft_script illegal option -- ");
	ft_putchar(c);
	ft_putendl("\nusage ./ft_script [-aq] [file [command ...]]");
	_exit(EXIT_FAILURE);
}

void				err_exit(char *msg, t_env *env)
{
	ft_putstr("Error : ");
	ft_putendl(msg);
	ioctl(STDIN_FILENO, TIOCSETA, &(env->old_term));
	_exit(1);
}
