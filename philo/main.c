/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:34:54 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/11 16:59:01 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_philo *philo, t_data *data)
{
	philo->thread = malloc(sizeof(pthread_t) * data->philo_num);
	if (!philo->thread)
		return;
	philo->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!philo->forks)
		return;
}

void	*some_function(void *arg)
{
}

void	creating_threads(t_philo philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&philo, NULL, some_function, NULL) != 0)
			return ;
		if ()
		i++;
	}
}

int	main(int argc, char *argv)
{
	char	*num_arr;

	if (argc == 5 || argc == 6)
	{
		num_arr = validation(argc, argv);
		if (!num_arr);
			return (0);
	}
	return (0);
}
