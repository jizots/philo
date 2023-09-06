/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:52:19 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/06 13:58:03 by sotanaka         ###   ########.fr       */
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
# include <stdbool.h>

/*-------define-------*/
/*don't use global variables*/
# define NOT_ENOUGH_AV 1
# define TOO_MANY_AV 2
# define INVALID_MATRIX 3
# define INCLUDE_MINUS 4
# define ZERO_PHILO 5
# define MALLOC_ERROR 1
# define MUTEX_ERROR 2
# define THREAD_ERROR 3
# define MUTEX_LOCK 4
# define MUTEX_UNLOCK 5
# define GETTIMEOFDAY -1
# define THREAD_JOIN 11
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4
# define PICK_UP 5
# define FULL 6

/*-------typedef-------*/

typedef struct s_monitor
{
	int		id_philo;
	long	last_time_eat;
	int		num_of_eat;
}	t_monitor;

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
}	t_param;

typedef struct s_philo
{
	int				id_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*print_mutex;
	t_monitor		*monitor;
}	t_philo;

/*-------prototype-------*/
//analys_argv
int		philo_analys_argv(int ac, char *av[], t_param *param);
int		ft_isdigit(int c);
int		atoi_intmax(const char *str);
//create_philo
int		philo_create_mutex(t_param *param);
int		philo_create_philo(t_param *param, t_philo **philo, t_monitor **mnt);
//simulate
int		philo_start_party(t_philo *philo);
//print_state
int		philo_print_incorrect_argv(int flag);
int		philo_print_basic_error(int flag);
int		philo_print_with_errno(int flag, int error_no);
int		philo_print_state(pthread_mutex_t *print, int id_philo, int flag);
//monitor
int		get_num_full(bool which);
int		philo_monitor(t_param *param, t_monitor *monitor);
//utils
int		str_cmp(const char *s1, const char *s2);
long	get_time(void);
long	get_time_usec(void);
void	philo_destory_mutex(pthread_mutex_t *forks, int num_of_mutex);
int		philo_free(t_param *param, t_monitor *monitor, int status);

#endif