/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:34:54 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/24 14:47:01 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*if_sb_is_dead(void *arg)
{
	int		i;
	long	time;
	t_data	*data;

	data = (t_data *)arg;
	while (!data->somebody_died)
	{
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_lock(&data->philo[i].meal_time_mutex);
			time = get_time_in_ms() - data->philo[i].last_meal;
			if (time > data->time_to_die)
			{
				pthread_mutex_unlock(&data->philo[i].meal_time_mutex);
				pthread_mutex_lock(&data->print_mutex);
				data->somebody_died = 1;
				printf("%ld %d died\n", time, data->philo[i].id + 1);
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].meal_time_mutex);
			i++;
		}
		//usleep(500);
		pthread_mutex_lock(&data->death_mutex);
		if (data->somebody_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->death_mutex);
	}
	return (NULL);
}

void	pick_up_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		// print_status(philo, "is_thinking");
		usleep(500);
		// pthread_mutex_lock(&(data->forks[philo->right_fork]));
		// print_status(philo, "has taken a fork");
		// // if (!data->somebody_died)
		// // {
		// // 	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
		// // 	return ;
		// // }
		// pthread_mutex_lock(&(data->forks[philo->left_fork]));
		// print_status(philo, "has taken a fork");
	}
	else
	{

		pthread_mutex_lock(&(data->forks[philo->left_fork]));
		print_status(philo, "has taken a fork");
		// if (!data->somebody_died)
		// {
		// 	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
		// 	return ;
		// }
		pthread_mutex_lock(&(data->forks[philo->right_fork]));
		print_status(philo, "has taken a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&(philo->meal_time_mutex));
	philo->last_meal = get_time_in_ms();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->meal_time_mutex));
}

void	put_down_forks(t_philo *philo, t_data *data)//, long ms)
{
	//long	time;
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	//print_status(philo, "puts down forks");////////////////////////
	// time = get_time_in_ms();
	// while (get_time_in_ms() - time < ms)
		// usleep(100);
}

void	philo_sleep(t_philo *philo, long ms)
{
	long	time;

	time = get_time_in_ms();
	print_status(philo, "is sleeping");
	while (get_time_in_ms() - time < ms)
		usleep(100);
}

void	philo_think(t_philo *philo, long ms)
{
	long	time;

	print_status(philo, "is thinking");
	time = get_time_in_ms();
	while (get_time_in_ms() - time < ms)
		usleep(100);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time_in_ms() < philo->data->start_time)
		usleep(50);
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->somebody_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		pick_up_forks(philo, philo->data);
		philo_eat(philo);
		put_down_forks(philo, philo->data);//, data->time_to_sleep);
		philo_sleep(philo, philo->data->time_to_sleep);
		philo_think(philo, philo->data->time_to_die / 4);
	}
	return (NULL);
}

void	creating_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_in_ms() + 100;
	// while (i < data->philo_num)
	// {
	// 	data->philo[i].last_meal = data->start_time;
	// 	i++;
	// }
	// usleep(100);
	// i = 0;
	while (i < data->philo_num)
	{
		data->philo[i].last_meal = data->start_time;
		if (pthread_create(&data->philo[i].thread, NULL, philosopher, &data->philo[i]) != 0)
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

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!validation(argc, argv))
	{
		free(data);
		free(data->philo);
		write(2, "Error\n", 6);
		return (1);
	}
	init(data, argv);
	creating_threads(data);
	free(data->philo);
	free(data);
	return (0);
}
