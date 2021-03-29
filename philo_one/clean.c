/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:39:18 by nagresl           #+#    #+#             */
/*   Updated: 2021/03/26 10:17:56 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_killer(t_prog_dt *data)
{
	int	i;
	int	nb;

	i = 0;
	nb = data->n_philo;
	if (data->n_meals != -1)
		pthread_join(data->eats_thread, NULL);
	while (i < nb)
	{
		pthread_mutex_lock(&(data->philo[i].meal_time));
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

void	clean_philo(t_prog_dt *data, t_param *param)
{
	int			i;

	i = 0;
	philo_killer(data);
	if (param)
		free(param);
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philo[i].left_fork);
		pthread_mutex_destroy(&data->philo[i].finish_eaten);
		pthread_mutex_destroy(&data->philo[i].meal_time);
		if (data->philo[i].name)
			free(data->philo[i].name);
		if (data->philo[i].time_last_meal)
			free(data->philo[i].time_last_meal);
		i++;
	}
	if (data->time_start)
		free(data->time_start);
	if (data->philo)
		free(data->philo);
}
