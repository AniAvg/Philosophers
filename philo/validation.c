/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:33:48 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/01 17:37:16 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char * str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < argc)
	{
		while (j < ft_strlen(argv[i]))
		{
			if (argv[i][j] < 48 && argv[i][j] > 57)
				return (0);
			j++;
		}
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

char	*validation(int argc, char *argv)
{
	int	i;
	int	j;
	int	*num_arr;

	i = 0;
	j = 0;
	num_arr = (int *)malloc(sizeof(int) * (argc - 1));
	if (!num_arr)
		return (NULL);
	if (!is_digit(argc, argv))
		return (NULL);
	while (i < argc)
	{
			num_arr[i] = ft_atoi(argv[i]);
			if (num_arr[i] == 0)
				return (NULL);
			j++;
	}
	return (num_arr);
}

