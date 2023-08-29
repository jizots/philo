/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:52:19 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/29 18:24:44 by sotanaka         ###   ########.fr       */
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

/*-------define-------*/
/*don't use global variables*/

/*-------typedef-------*/
/*-------prototype-------*/
int		philo_analys_argv();
int		philo_set_criteria();
int		philo_run_program();
int		philo_create_philo();
int		philo_get_fork();
int		philo_print_state();
int		philo_destroy();

#endif