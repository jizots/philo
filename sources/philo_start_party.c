/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_party.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:27:44 by hotph             #+#    #+#             */
/*   Updated: 2023/09/04 19:12:56 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pick_up_fork(int id_philo, pthread_mutex_t *fork_first,
	pthread_mutex_t *fork_second, pthread_mutex_t *print_mutex)
{
	int	status;

	status = pthread_mutex_lock(fork_first);
	if (status != 0)
		return (philo_print_thread_error(MUTEX_LOCK, status));
	status = philo_print_state(print_mutex, id_philo, PICK_UP);
	if (status != 0)
		return (status);
	status = pthread_mutex_lock(fork_second);
	if (status != 0)
		return (philo_print_thread_error(MUTEX_LOCK, status));
	status = philo_print_state(print_mutex, id_philo, PICK_UP);
	return (status);
}

static int	pick_up_fork_wrap(t_philo *philo)
{
	int	status;

	if (philo->id_philo % 2 == 0)
		status = pick_up_fork(philo->id_philo, philo->fork_left,
				philo->fork_right, philo->print_mutex);
	else
		status = pick_up_fork(philo->id_philo, philo->fork_right,
				philo->fork_left, philo->print_mutex);
	return (status);
}

static int	drop_off_fork(pthread_mutex_t *fork_left, pthread_mutex_t *fork_right)
{
	int	status;

	status = pthread_mutex_unlock(fork_left);
	if (status != 0)
		return (philo_print_thread_error(MUTEX_UNLOCK, status));
	status = pthread_mutex_unlock(fork_right);
	if (status != 0)
		return (philo_print_thread_error(MUTEX_UNLOCK, status));
	return (0);
}

int	philo_start_party(t_philo *philo)
{
	int	status;

	philo->monitor->last_time_eat = get_time();
	if (philo->monitor->last_time_eat == -1)
		return (-1);
	while (1)
	{
		status = pick_up_fork_wrap(philo);
		if (status != 0)
			return (status);
		philo->monitor->last_time_eat = get_time();
		status = philo_print_state(philo->print_mutex, philo->id_philo, EAT);
		if (status != 0)
			return (status);
		usleep(philo->time_to_eat * 1000);
		status = drop_off_fork(philo->fork_left, philo->fork_right);
		if (status != 0)
			return (status);
		status = philo_print_state(philo->print_mutex, philo->id_philo, SLEEP);
		if (status != 0)
			return (status);
		usleep(philo->time_to_sleep * 1000);
		status = philo_print_state(philo->print_mutex, philo->id_philo, THINK);
		if (status != 0)
			return (status);
	}
	return (0);
}
