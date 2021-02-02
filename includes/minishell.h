/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:36:40 by oagrram           #+#    #+#             */
/*   Updated: 2020/03/04 15:36:41 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
#define PATH_MAX 1024

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

char				*ft_srch_in_list(t_env *p, char *found);
int					ft_cd(t_env **head, char **line);
void				ft_cd_dir(t_env **head, char *parm);
char				*ft_srch_in_list(t_env *p, char *found);
int					ft_check_acses(char *path);
int					ft_check_expans(char **parmlist, t_env *env);
int					ft_is_builtins(char *command);
int					ft_execut_builtins(char **line, t_env **head);
char				*ft_check_prog(t_env *head, char *command);
t_env				*ft_swith_data(char **env, int j);
void				ft_echo(char **line);
int					ft_env(t_env *head);
void				ft_setenv(t_env *p, char **line);
t_env				*ft_unsetenv(t_env **head, char **line);

#endif
