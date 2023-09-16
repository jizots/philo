/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_mutex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:07:30 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/16 12:28:36 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_forks(pthread_mutex_t **forks, int num_of_philo)
{
	int	i;

	*forks = malloc (sizeof(pthread_mutex_t) * num_of_philo);
	if (*forks == NULL)
		return (philo_print_init_error(MALLOC_ERROR));
	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_mutex_init(&((*forks)[i]), NULL) != 0)
		{
			philo_destory_mutex(*forks, i);
			return (philo_print_init_error(MUTEX_ERROR));
		}
		i++;
	}
	return (0);
}

static int	init_mutex_etc(t_param *param)
{
	if (pthread_mutex_init(&(param->print_mutex), NULL) != 0)
		return (philo_print_init_error(MUTEX_ERROR));
	if (pthread_mutex_init(&(param->full), NULL) != 0)
		return (philo_print_init_error(MUTEX_ERROR));
	if (pthread_mutex_init(&(param->get_time), NULL) != 0)
		return (philo_print_init_error(MUTEX_ERROR));
	return (0);
}

int	philo_create_mutex(t_param *param, t_monitor *monitor)
{
	int	status;

	status = create_forks(&(param->forks), param->num_of_philo);
	if (status == 0)
	{
		status = init_mutex_etc(param);
		if (status == 0)
			return (0);
	}
	return (philo_free(param, monitor, status));
}
