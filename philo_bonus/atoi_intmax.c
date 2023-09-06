/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_intmax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:07:12 by tchoquet          #+#    #+#             */
/*   Updated: 2023/09/05 18:35:48 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int	find_first_index(const char *str)
{
	unsigned int	i;

	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	return (i);
}

static int	ft_long_atoi(const char *str)
{
	char			signe;
	long			nbr;
	unsigned int	i;

	signe = 1;
	nbr = 0;
	i = find_first_index(str);
	if (str[i] == '-')
		signe *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((nbr > INT_MAX / 10)
			|| (nbr == INT_MAX / 10 && str[i] - '0' > INT_MAX % 10))
		{
			if (signe == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return ((int)(signe * nbr));
}

int	atoi_intmax(const char *str)
{
	return (ft_long_atoi(str));
}
