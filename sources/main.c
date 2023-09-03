/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:46:36 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/03 16:55:45 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_param			param;
	t_param			*copy_param;
	int				status;

	status = philo_analys_argv(ac, av, &param);
	if (status != 0)
		return (status);
	status = philo_create_mutex(&param);
	if (status != 0)
		return (status);
	status = philo_create_philo(&param, &copy_param);
	if (status != 0)
		return (status);
	status = philo_monitor(&param);
	if (status != 0)
		return (status);
	printf("end\n");
	return (0);
}
