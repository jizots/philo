/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:52:19 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/05 20:12:14 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_B_H
# define PHILO_B_H

/*-------includes-------*/
/*memset, printf, malloc, free, write, fork, kill, exit, 
pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, 
waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink*/
// # include <string.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <sys/time.h>
// # include <pthread.h>
// # include <limits.h>
// # include <errno.h>
// # include <stdbool.h>

/*-------define-------*/
/*don't use global variables*/
# define NOT_ENOUGH_AV 1
# define TOO_MANY_AV 2
# define INVALID_MATRIX 3
# define INCLUDE_MINUS 4
# define ZERO_PHILO 5
# define MALLOC_ERROR 1
# define THREAD_ERROR 3
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
}	t_param;

typedef struct s_philo
{
	int				id_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	t_monitor		*monitor;
}	t_philo;

/*-------prototype-------*/
//analys_argv
int		philo_analys_argv(int ac, char *av[], t_param *param);
int		ft_isdigit(int c);
int		atoi_intmax(const char *str);
//create_philo
//simulate
//print_state
//monitor
//utils

#endif