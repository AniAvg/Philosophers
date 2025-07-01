/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:34:54 by anavagya          #+#    #+#             */
/*   Updated: 2025/07/01 17:38:19 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv)
{
	char	*num_arr;

	if (argc == 4 || argc == 5)
	{
		num_arr = validation(argc, argv);
		if (!num_arr);
			return (0);
	}
	return (0);
}
