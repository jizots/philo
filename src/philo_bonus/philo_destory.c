/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:16:37 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/06 16:17:00 by sotanaka         ###   ########.fr       */
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

void	free_philo_data(pid_t *pid, t_monitor *mnt)
{
	free(pid);
	free(mnt);
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
