/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:39:18 by nagresl           #+#    #+#             */
/*   Updated: 2021/05/04 16:34:43 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	philo_killer(t_prog_dt *data)
{
	int	i;
	int	nb;

	i = 0;
	nb = data->n_philo;
	if (data->n_meals != -1)
		pthread_join(data->eats_thread, NULL);
	pthread_join(data->deaths_thread, NULL);
	while (i < nb)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

void		ft_unlock_mutex(t_prog_dt *dt)
{
	int i;

	i = 0;
	while (i < dt->n_philo)
	{
		if (dt->philo[i].meals_ate < dt->n_meals)
			pthread_mutex_unlock(&(dt->philo[i].finish_eaten));
		i++;
	}
}

void		clean_philo(t_prog_dt *data, t_param *param)
{
	int	i;

	i = 0;
	if (data->n_meals != -1)
		ft_unlock_mutex(data);
	philo_killer(data);
	if (param)
		free(param);
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&(data->philo[i].left_fork));
		pthread_mutex_destroy(&(data->philo[i].finish_eaten));
		pthread_mutex_destroy(&(data->philo[i].meal_time));
		if (data->philo[i].name)
			free(data->philo[i].name);
		if (data->philo[i].time_last_meal)
			free(data->philo[i].time_last_meal);
		i++;
	}
	pthread_mutex_destroy(&(data->output_protection));
	pthread_mutex_destroy(&(data->finish_lock));
	if (data->time_start)
		free(data->time_start);
	if (data->philo)
		free(data->philo);
}
