/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start_party.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:27:44 by hotph             #+#    #+#             */
/*   Updated: 2023/09/16 12:48:26 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pick_up_fork(int id_philo, pthread_mutex_t *fork_first,
	pthread_mutex_t *fork_second, pthread_mutex_t *print_mutex)
{
	int	status;

	status = pthread_mutex_lock(fork_first);
	if (status != 0)
		return (philo_print_with_errno(MUTEX_LOCK, status));
	status = philo_print_state(print_mutex, id_philo, PICK_UP);
	if (status != 0)
		return (status);
	status = pthread_mutex_lock(fork_second);
	if (status != 0)
		return (philo_print_with_errno(MUTEX_LOCK, status));
	return (status);
}

static int	p_eat(t_philo *philo)
{
	int	status;

	if (philo->id_philo % 2 == 0)
		status = pick_up_fork(philo->id_philo, philo->fork_left,
				philo->fork_right, philo->print_mutex);
	else
		status = pick_up_fork(philo->id_philo, philo->fork_right,
				philo->fork_left, philo->print_mutex);
	pthread_mutex_lock(philo->get_time);
	philo->monitor->last_time_eat = get_time();
	pthread_mutex_unlock(philo->get_time);
	if (status != 0)
		return (status);
	status = philo_print_state(philo->print_mutex, philo->id_philo, EAT);
	return (status);
}

static int	p_sleep(pthread_mutex_t *fork_left, pthread_mutex_t *fork_right,
	t_philo *philo)
{
	pthread_mutex_unlock(fork_left);
	pthread_mutex_unlock(fork_right);
	if (philo_print_state(philo->print_mutex, philo->id_philo, SLEEP) != 0)
		return (1);
	return (0);
}

int	philo_start_party(t_philo *philo)
{
	pthread_mutex_lock(philo->get_time);
	philo->monitor->last_time_eat = get_time();
	pthread_mutex_unlock(philo->get_time);
	while (1)
	{
		if (p_eat(philo) != 0)
			return (1);
		usleep_precisely(philo->time_to_eat * 1000);
		philo->monitor->num_of_eat += 1;
		if (p_sleep(philo->fork_left, philo->fork_right, philo) != 0)
			return (1);
		pthread_mutex_lock(philo->full);
		if (philo->monitor->num_of_eat == philo->num_of_must_eat)
			get_num_full(false);
		pthread_mutex_unlock(philo->full);
		usleep_precisely(philo->time_to_sleep * 1000);
		if (philo_print_state(philo->print_mutex, philo->id_philo, THINK) != 0)
			return (1);
		is_teetime(philo->time_to_eat, philo->time_to_sleep);
	}
	return (0);
}
