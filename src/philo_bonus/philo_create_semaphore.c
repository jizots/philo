/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_semaphore.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:23:56 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/16 17:11:47 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

static int	num_restrict(int num_of_philo)
{
	if (num_of_philo % 2 == 0)
		return (num_of_philo / 2);
	else
		return (num_of_philo / 2 + 1);
}

static int	create_forks(t_param *param)
{
	param->forks = sem_open("forks", 
			O_CREAT, S_IRUSR | S_IWUSR, param->num_of_philo);
	if (param->forks == SEM_FAILED)
		return (philo_print_basic_error(SEM_ERROR));
	return (0);
}

static int	create_cordinator_and_printer(t_param *param)
{
	param->cordinator = sem_open("cordinator",
			O_CREAT, S_IRUSR | S_IWUSR, num_restrict(param->num_of_philo));
	if (param->cordinator == SEM_FAILED)
	{
		sem_close_and_unlink(param->forks, "forks");
		return (philo_print_basic_error(SEM_ERROR));
	}
	param->print_sem = sem_open("print_sem", 
			O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (param->print_sem == SEM_FAILED)
	{
		sem_close_and_unlink(param->forks, "forks");
		sem_close_and_unlink(param->cordinator, "cordinator");
		return (philo_print_basic_error(SEM_ERROR));
	}
	return (0);
}

static int	create_gettime_and_timeeat(t_param *param)
{
	param->get_time = sem_open("gettime_sem", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (param->get_time == SEM_FAILED)
	{
		sem_close_and_unlink(param->forks, "forks");
		sem_close_and_unlink(param->cordinator, "cordinator");
		sem_close_and_unlink(param->cordinator, "print_sem");
		return (philo_print_basic_error(SEM_ERROR));
	}
	param->times_eat = sem_open("timeeat_sem", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (param->get_time == SEM_FAILED)
	{
		sem_close_and_unlink(param->forks, "forks");
		sem_close_and_unlink(param->cordinator, "cordinator");
		sem_close_and_unlink(param->cordinator, "print_sem");
		sem_close_and_unlink(param->cordinator, "gettime_sem");
		return (philo_print_basic_error(SEM_ERROR));
	}
	return (0);
}

int	philo_create_semaphore(t_param *param)
{
	if (create_forks(param) == 0)
	{
		if (create_cordinator_and_printer(param) == 0)
		{
			if (create_gettime_and_timeeat(param) == 0)
				return (0);
		}
	}
	return (1);
}
