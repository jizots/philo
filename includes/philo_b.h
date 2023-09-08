/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:52:19 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/08 14:22:03 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_B_H
# define PHILO_B_H

/*-------includes-------*/
/*memset, printf, malloc, free, write, fork, kill, exit, 
pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, 
waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink*/
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
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
# define SEM_ERROR 1
# define MALLOC_ERROR 2
# define FORK_ERROR 3
# define THREAD_ERROR 4
# define KILL_ERROR 5
# define WAIT_ERROR 6
# define GETTIMEOFDAY -1
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4
# define PICK_UP 5
# define FULL 6

/*-------typedef-------*/

typedef struct s_monitor
{
	int			id_philo;
	int			time_to_die;
	long		last_time_eat;
	int			num_of_eat;
	int			num_of_must_eat;
	sem_t		*forks;
	sem_t		*cordinator;
	sem_t		*print_sem;
	pthread_t	monitor_death;
}	t_monitor;

typedef struct s_param
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_must_eat;
	sem_t	*forks;
	sem_t	*cordinator;
	sem_t	*print_sem;
	pid_t	*pid;
}	t_param;

/*-------prototype-------*/
//analys_argv
int		philo_analys_argv(int ac, char *av[], t_param *param);
int		ft_isdigit(int c);
int		atoi_intmax(const char *str);
//create_philo
int		philo_create_semaphore(t_param *param);
int		philo_create_philo(t_param *param);
//simulate
int		philo_start_party(t_param *param, int id_philo);
//print_state
int		philo_print_incorrect_argv(int flag);
int		philo_print_basic_error(int flag);
int		philo_print_with_errno(int flag, int error_no);
int		philo_print_state(sem_t *print, int id_philo, int flag);
//monitor
int		philo_create_monitor_thread(t_monitor *mnt);
//utils
int		str_cmp(const char *s1, const char *s2);
long	get_time(void);
long	get_time_usec(void);
void	usleep_precisely(int microseconds);
//destory
void	philo_destory_mutex(pthread_mutex_t *forks, int num_of_mutex);
int		sem_close_and_unlink(sem_t *sem, char *name);
int		philo_destroy_semaphore(t_param *param);
int		kill_remain_philo(pid_t *pid, int num_of_philo);
//fork_handling
int		philo_drop_forks(sem_t *forks, sem_t *cordinator);

#endif