/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_philo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:07:06 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/05 14:18:41 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_philo_each(t_param *param, t_philo **philo, t_monitor **mnt)
{
	int	i;

	i = 0;
	while (i < param->num_of_philo)
	{
		(*philo)[i].id_philo = i + 1;
		(*philo)[i].time_to_eat = param->time_to_eat;
		(*philo)[i].time_to_sleep = param->time_to_sleep;
		(*philo)[i].num_of_must_eat = param->num_of_must_eat;
		(*philo)[i].fork_left = &((param->forks)[i]);
		(*philo)[i].fork_right = &((param->forks)[(i + 1) % param->num_of_philo]);
		(*philo)[i].print_mutex = &(param->print_mutex);
		(*philo)[i].monitor = &((*mnt)[i]);
		i++;
	}
}

static int	allocate_thread_and_data(t_param *param, t_philo **philo, t_monitor **mnt)
{
	int	i;

	param->thread = malloc(sizeof(pthread_t) * param->num_of_philo);
	if (param->thread == NULL)
		return (philo_print_init_error(MALLOC_ERROR));
	*philo = malloc(sizeof(t_philo) * param->num_of_philo);
	if (*philo == NULL)
		return (philo_print_init_error(MALLOC_ERROR));
	*mnt = malloc (sizeof(t_monitor) * param->num_of_philo);
	if (*mnt == NULL)
		return (philo_print_init_error(MALLOC_ERROR));
	i = 0;
	while (i < param->num_of_philo)
	{
		(*mnt)[i].id_philo = i + 1;
		i++;
	}
	return (0);
}

static int	destroy_at_create_thread(t_param *param, t_philo **philo)
{
	free (*philo);
	philo_destory_mutex(param->forks, param->num_of_philo);
	free (param->thread);
	return (philo_print_init_error(THREAD_ERROR));
}

int		philo_create_philo(t_param *param, t_philo **philo, t_monitor **mnt)
{
	int		i;
	int		status;

	status = allocate_thread_and_data(param, philo, mnt);
	if (status != 0)
		return (status);
	set_philo_each(param, philo, mnt);
	i = 0;
	while (i < param->num_of_philo)
	{
		status = pthread_create(&((param->thread)[i]), NULL, 
				(void *)philo_start_party, (void *)&((*philo)[i]));
		if (status != 0)
			return (destroy_at_create_thread(param, philo));
		i++;
	}
	usleep(50 * 1000);
	return (0);
}
