/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:33:48 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/17 18:01:12 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (result);
}

int	validation(int argc, char *argv)
{
	int	i;

	i = 1;
	if (argc != 5 || argc != 6)
		return (0);
	// num_arr = (int *)malloc(sizeof(int) * (argc - 1));
	// if (!num_arr)
	// 	return (0);
	if (!is_digit(argc, argv))
		return (0);
	while (i < argc)
	{
		if (ft_atoi(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
