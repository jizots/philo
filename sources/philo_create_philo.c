/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_philo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:07:06 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/03 16:54:32 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allocate_thread_and_param_each(t_param *param, t_param **copy_param)
{
	*copy_param = malloc(sizeof(t_param) * param->num_of_philo);
	if (*copy_param == NULL)
		return (philo_print_init_error(MALLOC_ERROR));
	param->thread = malloc(sizeof(pthread_t) * param->num_of_philo);
	if (param->thread == NULL)
		return (philo_print_init_error(MALLOC_ERROR));
	return (0);
}

static void	set_param_each(t_param *param, t_param **copy_param, int i)
{
	(*copy_param)[i] = *param;
	(*copy_param)[i].no_philo = i + 1;
	(*copy_param)[i].fork_left = &((param->forks)[i]);
	(*copy_param)[i].fork_right = &((param->forks)[(i + 1) % param->num_of_philo]);
}

static int	destroy_at_create_thread(t_param *param, t_param **copy_param)
{

	free (*copy_param);
	philo_destory_mutex(param->forks, param->num_of_philo);
	free (param->thread);
	return (philo_print_init_error(THREAD_ERROR));
}

int		philo_create_philo(t_param *param, t_param **copy_param)
{
	int		i;
	int		status;

	status = allocate_thread_and_param_each(param, copy_param);
	if (status != 0)
		return (status);
	i = 0;
	while (i < param->num_of_philo)
	{
		set_param_each(param, copy_param, i);
		status = pthread_create(&((param->thread)[i]), NULL, 
				(void *)philo_start_party, (void *)&((*copy_param)[i]));
		if (status != 0)
			return (destroy_at_create_thread(param, copy_param));
		i++;
	}
	return (0);
}
