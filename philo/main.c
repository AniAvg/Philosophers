/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:34:54 by anavagya          #+#    #+#             */
/*   Updated: 2025/08/12 12:47:59 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	joining_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			printf("Error joining thread %d\n", i);
			return ;
		}
		i++;
	}
	if (pthread_join(data->philo_is_dead, NULL) != 0)
	{
		printf("Error creating death thread\n");
		return ;
	}
}

void	creating_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_in_ms() + 100;
	while (i < data->philo_num)
	{
		data->philo[i].last_meal = data->start_time;
		if (pthread_create(&data->philo[i].thread, NULL,
				philosopher, &data->philo[i]) != 0)
		{
			printf("Error creating thread %d\n", i);
			return ;
		}
		i++;
	}
	if (pthread_create(&data->philo_is_dead, NULL, if_sb_is_dead, data) != 0)
	{
		printf("Error creating death thread\n");
		return ;
	}
	joining_threads(data);
}

void	*one_philo(t_philo *philo)
{
	philo->data->start_time = get_time_in_ms();
	pthread_mutex_lock(&(philo->meal_lock));
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&(philo->meal_lock));
	pthread_mutex_lock(&(philo->data->forks[0]));
	pthread_mutex_lock(&(philo->data->print_mutex));
	printf("%ld %d has taken a fork\n",
		get_time_in_ms() - philo->data->start_time, philo[0].id + 1);
	pthread_mutex_unlock(&(philo->data->print_mutex));
	pthread_mutex_unlock(&(philo->data->forks[0]));
	pthread_mutex_lock(&(philo->data->death_mutex));
	if (philo->data->somebody_died)
	{
		pthread_mutex_unlock(&(philo->data->death_mutex));
		return (NULL);
	}
	pthread_mutex_unlock(&(philo->data->death_mutex));
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!validation(argc, argv))
	{
		free(data);
		write(2, "Error\n", 6);
		return (1);
	}
	init(data, argv);
	creating_threads(data);
	cleanup(data);
	free(data);
	return (0);
}
