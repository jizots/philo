/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:55:09 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/16 12:25:45 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	philo_free(t_param *param, t_monitor *monitor, int status)
{
	if (param->forks)
		philo_destory_mutex(param->forks, param->num_of_philo);
	pthread_mutex_destroy(&(param->print_mutex));
	pthread_mutex_destroy(&(param->full));
	pthread_mutex_destroy(&(param->get_time));
	if (param->thread)
		free(param->thread);
	if (monitor)
		free(monitor);
	return (status);
}

int	str_cmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (philo_print_with_errno(GETTIMEOFDAY, -1));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_time_usec(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (philo_print_with_errno(GETTIMEOFDAY, -1));
	return (time.tv_sec * 1000000 + time.tv_usec);
}
