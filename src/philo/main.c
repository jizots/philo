/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:46:36 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/16 12:23:39 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_params(t_param *param, t_monitor **mnt)
{
	param->forks = NULL;
	param->print_mutex = (pthread_mutex_t){0};
	param->full = (pthread_mutex_t){0};
	param->get_time = (pthread_mutex_t){0};
	param->thread = NULL;
	*mnt = NULL;
}

int	main(int ac, char *av[])
{
	t_param		param;
	t_philo		*philo;
	t_monitor	*mnt;
	int			status;

	init_params(&param, &mnt);
	status = philo_analys_argv(ac, av, &param);
	if (status != 0)
		return (status);
	status = philo_create_mutex(&param, mnt);
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

// __attribute__((destructor))
// static void	destructor(void)
// {
// 	system("leaks -q philo");
// }