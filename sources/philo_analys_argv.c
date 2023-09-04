/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_analys_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:11:03 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/04 19:51:24 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	str_isdigit(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

static int	with_in_atoi(char *str)
{
	int	num;

	if (str_isdigit(str) != 0)
		return (1);
	num = atoi_intmax(str);
	if (num == INT_MAX || num == INT_MIN)
	{
		if (str_cmp(str, "2147483647") == 0)
			return (0);
		if (str_cmp(str, "-2147483648") == 0)
			return (0);
		return (1);
	}
	return (0);
}

static bool	is_matrix_valid(int num_of_line, char *matrix[], void *f(char *))
{
	int	i;

	i = 1;
	while (i < num_of_line)
	{
		if ((f)(matrix[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}

static int	import_criteria(int ac, t_param *param, char *av[])
{
	param->num_of_philo = atoi_intmax(av[1]);
	if (param->num_of_philo == 0)
		return (philo_print_incorrect_argv(ZERO_PHILO));
	param->time_to_die = atoi_intmax(av[2]);
	param->time_to_eat = atoi_intmax(av[3]);
	param->time_to_sleep = atoi_intmax(av[4]);
	if (av[5])
		param->num_of_must_eat = atoi_intmax(av[5]);
	else
		param->num_of_must_eat = -1;
	if (param->num_of_philo < 0 || param->time_to_die < 0
		|| param->time_to_eat < 0 || param->time_to_sleep < 0)
		return (philo_print_incorrect_argv(INCLUDE_MINUS));
	if (ac == 6 && param->num_of_must_eat < 0)
		return (philo_print_incorrect_argv(INCLUDE_MINUS));
	return (0);
}

int		philo_analys_argv(int ac, char *av[], t_param *param)
{
	if (ac < 5)
		return (philo_print_incorrect_argv(NOT_ENOUGH_AV));
	else if (ac > 6)
		return (philo_print_incorrect_argv(TOO_MANY_AV));
	else if (is_matrix_valid(ac, av, (void *)with_in_atoi) == false)
		return (philo_print_incorrect_argv(INVALID_MATRIX));
	else if (import_criteria(ac, param, av) != 0)
		return (1);
	else
		return (0);
}
