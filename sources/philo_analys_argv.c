/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_analys_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:11:03 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/02 18:28:10 by sotanaka         ###   ########.fr       */
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

static int	is_matrix_valid(int ac, char *av[], void *f(char *))
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if ((f)(av[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	import_criteria(int ac, t_param *param, char *av[])
{
	param->num_of_philo = atoi_intmax(av[1]);
	param->time_to_die = atoi_intmax(av[2]);
	param->time_to_eat = atoi_intmax(av[3]);
	param->time_to_sleep = atoi_intmax(av[4]);
	if (av[5])
		param->num_of_must_eat = atoi_intmax(av[5]);
	else
		param->num_of_must_eat = -1;
	if (param->num_of_philo < 0 || param->time_to_die < 0
		|| param->time_to_eat < 0 || param->time_to_sleep < 0)
		return (1);
	if (ac == 6 && param->num_of_must_eat < 0)
		return (1);
	return (0);
}

int		philo_analys_argv(int ac, char *av[], t_param *param)
{
	if (ac < 5)
		return (philo_print_incorrect_argv(NOT_ENOUGH_AV));
	else if (ac > 6)
		return (philo_print_incorrect_argv(TOO_MANY_AV));
	else if (is_matrix_valid(ac, av, (void *)with_in_atoi) != 0)
		return (philo_print_incorrect_argv(INVALID_MATRIX));
	else if (import_criteria(ac, param, av) != 0)
		return (philo_print_incorrect_argv(INCLUDE_MINUS));
	else
		return (0);
}

// int main(int ac, char *av[])
// {
// 	t_param	param;
// 	if (philo_analys_argv(ac, av, &param) != 0)
// 		;
// 	else
// 		printf("OK\n");
// }