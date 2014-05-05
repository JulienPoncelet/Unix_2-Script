/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponcele <jponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 14:29:23 by jponcele          #+#    #+#             */
/*   Updated: 2014/05/02 15:27:32 by jponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include <fcntl.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/mman.h>
# include <unistd.h>
# include <libft.h>

# define PTYM_PREFIX		"/dev/pty"
# define PTYS_PREFIX		"/dev/tty"
# define PTY_PREFIX_LEN		(sizeof(PTYM_PREFIX) - 1)
# define PTY_NAME_LEN		(PTY_PREFIX_LEN + sizeof("XY"))
# define X_RANGE			"pqrstuvwxyzabcde"
# define Y_RANGE			"0123456789abcdef"
# define MAX_SNAME			1000
# define BUFF_SIZE			32
# define MAP_FLAG			PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE

enum						e_flag
{
	F_A, F_K, F_Q, F_T
};

typedef struct				s_env
{
	char					shell[255];
	unsigned char			opt[4];
	int						time;
	char					file_name[255];
	int						fd_file;
	struct winsize			ws;
	struct termios			old_term;
	struct termios			new_term;
}							t_env;

/*
**							ft_script.c
*/

void						exec_cmd(t_env *env, char **av, char **e);
int							ft_script_select(t_env *env, int fd_master);
void						start_script(t_env *env, char **av, char **e);
int							main(int ac, char **av, char **e);

/*
**							ft_script_init.c
*/

void						open_log(t_env *env);
char						**get_option(char **av, t_env *env);
char						**morph_av(char **av, char *shell);

/*
**							ft_script_err.c
*/

void						err_usage(unsigned char c);
void						err_exit(char *msg, t_env *env);

/*
**							ft_script_term.c
*/

void						ft_set_old_term(t_env *env);
void						ft_get_termios(t_env *env);
int							ft_script_select_stdout(t_env *env, int fd_master);
int							ft_script_select_stdin(t_env *env, int fd_master);

/*
**							ptyfork.c
*/

void						ptyfork_verif_fd_slave(char *slname);
pid_t						ptyfork(int *fd_ma, char *sl_name, size_t sln_len);

/*
**							ptyopen.c
*/

int							pty_master_open(char *slave_name, size_t sln_len);

/*
**							get_shell.c
*/

char						*get_shell(char **env);
char						*ft_getenv(char **env, char *name);
char						*check_cmd(char **env, char *cmd);
char						*cat_all(char **env);

#endif
