/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_mutex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:07:30 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/08 09:12:08 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_forks(pthread_mutex_t **forks, int num_of_mutex)
{
	int	i;

	*forks = malloc (sizeof(pthread_mutex_t) * num_of_mutex);
	if (*forks == NULL)
		return (philo_print_init_error(MALLOC_ERROR));
	i = 0;
	while (i < num_of_mutex)
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

static int	create_printer(pthread_mutex_t *print_mutex)
{
	if (pthread_mutex_init(print_mutex, NULL) != 0)
		return (philo_print_init_error(MUTEX_ERROR));
	return (0);
}

int	philo_create_mutex(t_param *param)
{
	int	status;

	status = create_forks(&(param->forks), param->num_of_philo);
	if (status == 0)
	{
		status = create_printer(&(param->print_mutex));
		if (status != 0)
			philo_destory_mutex(param->forks, param->num_of_philo);
	}
	return (status);
}
