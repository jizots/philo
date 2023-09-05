/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:46:36 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/05 15:35:28 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_param(t_param *param)
{
	param->num_of_philo = 0;
	param->time_to_die = 0;
	param->time_to_eat = 0;
	param->time_to_sleep = 0;
	param->num_of_must_eat = 0;
	param->forks = NULL;
	param->print_mutex = (pthread_mutex_t){0};
	param->thread = NULL;
}

int	main(int ac, char *av[])
{
	t_param		param;
	t_philo		*philo;
	t_monitor	*mnt;
	int			status;

	init_param(&param);
	status = philo_analys_argv(ac, av, &param);
	if (status != 0)
		return (status);
	status = philo_create_mutex(&param);
	if (status != 0)
		return (status);
	status = philo_create_philo(&param, &philo, &mnt);
	if (status != 0)
		return (status);
	status = philo_monitor(&param, mnt);
	if (status != 0)
		return (status);
	return (0);
}

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q philo");
}
