/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:14:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/29 20:52:16 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		philo_print_incorrect_argv(int flag)
{
	if (flag == NOT_ENOUGH_AV)
		printf("Error: Not enough arguments\n");
	else if (flag == TOO_MANY_AV)
		printf("Error: Too many arguments\n");
	else if (flag == INVALID_MATRIX || flag == INCLUDE_MINUS)
		printf("Error: Number's must with in 0 to 2147483647\n");
	return (flag);
}