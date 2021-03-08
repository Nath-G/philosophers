/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:39:18 by nagresl           #+#    #+#             */
/*   Updated: 2021/03/05 17:19:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	clean_philo(t_prog_dt *data)
{
	int			i;

	i = 0;
	while (i < data->n_philo)
	{
		if (data->philo[i].name)
			free(data->philo[i].name);
		if (data->philo[i].time_last_meal)
			free(data->philo[i].time_last_meal);
		pthread_mutex_destroy(&data->philo[i].left_fork);
		pthread_mutex_destroy(data->philo[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(&data->died);
	pthread_mutex_destroy(&data->meals);
	if (data->time_start)
		free(data->time_start);
	if (data->philo)
		free(data->philo);
}
