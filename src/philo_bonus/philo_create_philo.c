/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_philo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:31:40 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/06 16:13:30 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

static int	allocate_philo_data(t_monitor **mnt, pid_t **pid, int num_of_philo)
{
	*mnt = malloc(sizeof(t_monitor) * num_of_philo);
	if (*mnt != NULL)
	{
		*pid = malloc(sizeof(pid_t) * num_of_philo);
		if (*pid != NULL)
			return (0);
	}
	return (philo_print_basic_error(MALLOC_ERROR));
}

static void	init_mnt(t_param *param, t_monitor *mnt, int i)
{
	mnt->id_philo = i + 1;
	mnt->last_time_eat = get_time_usec();
	mnt->num_of_eat = 0;
	mnt->num_of_must_eat = param->num_of_must_eat;
}

int	philo_create_philo(t_param *param, t_monitor **mnt)
{
	int		i;
	int		status;

	if (allocate_philo_data(mnt, &(param->pid), param->num_of_philo) != 0)
		return (1);
	i = 0;
	while (i < param->num_of_philo)
	{
		init_mnt(param, &((*mnt)[i]), i);
		param->pid[i] = fork();
		if (param->pid[i] < 0)
		{
			free_philo_data(param->pid, *mnt);
			return (philo_print_basic_error(FORK_ERROR));
		}
		else if (param->pid[i] == 0)
			philo_start_party(param, &((*mnt)[i]));
		else
			wait_at_pairent(param, &((*mnt)[i]), i);
		i++;
	}
	return (0);
}
