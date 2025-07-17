/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:19:09 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/17 16:33:27 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_data *data, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&data->print_mutex);
	timestamp = get_time_in_ms() - data->start_time;
	if (!data->philo_is_dead)
	printf("%ld %d %s\n", timestamp, data->philo->id, msg);
	pthread_mutex_unlock(&data->print_mutex);
}

long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (int)1000) + (time.tv_usec / 1000));
}
