/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:27:08 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/23 16:59:35 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&(data->philo[i].meal_time_mutex), NULL) != 0
			|| pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return ;
		data->philo[i].id = i;
		data->philo[i].meal_count = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].left_fork = data->philo[i].id;
		if (data->philo[i].id == (data->philo_num - 1))
			data->philo[i].right_fork = 0;
		else
			data->philo[i].right_fork = data->philo[i].id + 1;
		data->philo[i].data = data;
		i++;
	}
}

void	init(t_data *data, char **argv)
{
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	data->philo = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->forks || !data->philo)
		return ;
	data->start_time = 0;
	data->somebody_died = 0;
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return ;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return ;
	init_philo(data);
}
