/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:52:19 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/03 16:58:48 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*-------includes-------*/
/*memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock*/
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <errno.h>

/*-------define-------*/
/*don't use global variables*/
# define NOT_ENOUGH_AV 1
# define TOO_MANY_AV 2
# define INVALID_MATRIX 3
# define INCLUDE_MINUS 4
# define MALLOC_ERROR 5
# define MUTEX_ERROR 6
# define THREAD_ERROR 7
# define MUTEX_LOCK 8
# define MUTEX_UNLOCK 9
# define GETTIMEOFDAY 10
# define THREAD_JOIN 11
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4
# define PICK_UP 5

/*-------typedef-------*/
typedef struct s_param
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_t		*thread;
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
	int				no_philo;
}	t_param;

/*-------prototype-------*/
//analys_argv
int		philo_analys_argv(int ac, char *av[], t_param *param);
int		ft_isdigit(int c);
int		atoi_intmax(const char *str);
int		str_cmp(const char *s1, const char *s2);
//create_philo
void	philo_destory_mutex(pthread_mutex_t *forks, int num_of_mutex);
int		philo_create_mutex(t_param *param);
int		philo_create_philo(t_param *param, t_param **copy_param);
int		philo_start_party(t_param *param);
int		philo_culc_time();
//print_state
int		philo_print_incorrect_argv(int flag);
int		philo_print_init_error(int flag);
int		philo_print_thread_error(int flag, int error_no);
int		philo_print_state(pthread_mutex_t *print, int no_philo, int flag);
//destroy
int		philo_monitor(t_param *param);
int		philo_destroy();

#endif