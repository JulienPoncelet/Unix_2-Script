/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponcele <jponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 13:16:15 by jponcele          #+#    #+#             */
/*   Updated: 2014/05/02 15:29:57 by jponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_script.h>

void				open_log(t_env *env)
{
	int				oflag;

	oflag = O_CREAT | O_RDWR | (env->opt[F_A] ? O_APPEND : O_TRUNC);
	if ((env->fd_file = open(env->file_name, oflag, 0666)) <= 0)
	{
		ft_putstr("./ft_script: ");
		ft_putstr(env->file_name);
		ft_putendl("open error");
		_exit(EXIT_FAILURE);
	}
}

char				**get_option(char **av, t_env *env)
{
	int				i;

	while (*av)
	{
		i = 0;
		if ((*av)[i] == '-')
			while ((*av)[++i])
			{
				env->opt[F_A] = ((*av)[i] == 'a' ? 1 : env->opt[F_A]);
				env->opt[F_Q] = ((*av)[i] == 'q' ? 1 : env->opt[F_Q]);
				if (ft_strchr("aq", (*av)[i]) == NULL)
					err_usage((*av)[i]);
			}
		else if (!env->file_name[0])
		{
			ft_strcpy(env->file_name, *av++);
			break ;
		}
		else
			break ;
		av++;
	}
	if (!env->file_name[0])
		ft_strcpy(env->file_name, "typescript");
	return (av);
}

char				**morph_av(char **av, char *shell)
{
	int				len;
	int				flag;
	char			**ret;
	int				i;

	len = ft_ctablen(av);
	flag = (len) ? 1 : 0;
	len = len + 4;
	ret = (char **)mmap(0, sizeof(char *) * len, MAP_FLAG, -1, 0);
	i = 0;
	ret[i++] = ft_strdup(shell);
	if (flag)
	{
		ret[i++] = ft_strdup("-c");
		ret[i++] = ft_strdup("--");
		ret[i++] = cat_all(av);
	}
	ret[i] = 0;
	return (ret);
}

char				*cat_all(char **av)
{
	char			*cat;
	int				i;
	int				len;

	len = 0;
	i = 0;
	while (av[i])
	{
		len = len + ft_strlen(av[i]) + 1;
		i++;
	}
	cat = (char *)mmap(0, sizeof(char) * len, MAP_FLAG, -1, 0);
	i = 0;
	while (av[i])
	{
		cat = ft_strjoin(cat, av[i]);
		cat = ft_strjoin(cat, " ");
		i++;
	}
	return (cat);
}
