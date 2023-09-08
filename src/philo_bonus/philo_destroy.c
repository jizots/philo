/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:16:37 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/08 14:21:56 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	philo_destory_mutex(pthread_mutex_t *forks, int num_of_mutex)
{
	int	i;

	i = 0;
	while (i < num_of_mutex)
	{
		pthread_mutex_destroy(&(forks[i]));
		i++;
	}
	free (forks);
}

int	sem_close_and_unlink(sem_t *sem, char *name)
{
	int	status;

	status = sem_close(sem);
	if (status == -1)
		return (philo_print_basic_error(SEM_ERROR));
	status = sem_unlink(name);
	if (status == -1)
		return (philo_print_basic_error(SEM_ERROR));
	return (0);
}

int	philo_destroy_semaphore(t_param *param)
{
	int	status;

	status = sem_close_and_unlink(param->forks, "forks");
	if (status != 0)
		return (status);
	status = sem_close_and_unlink(param->cordinator, "cordinator");
	if (status != 0)
		return (status);
	status = sem_close_and_unlink(param->print_sem, "print_sem");
	if (status != 0)
		return (status);
	return (0);
}

int	kill_remain_philo(pid_t *pid, int num_of_philo)
{
	int		i;

	i = 0;
	while (i < num_of_philo)
	{
		if (pid[i] != 0)
		{
			if (kill(pid[i], SIGKILL) != 0)
				return (philo_print_basic_error(KILL_ERROR));
		}
		i++;
	}
	return (1);
}
