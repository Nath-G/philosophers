/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:39:18 by nagresl           #+#    #+#             */
/*   Updated: 2021/04/16 14:09:23 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	ft_clean_sem_phi(char *sem_name, int phi, t_prog_dt *data)
{
	sem_close(data->philo[phi].meal_time);
	sem_unlink(sem_name);
}

void		ft_post_sem(t_prog_dt *dt)
{
	int i;

	i = 0;
	while (i < (dt->n_philo / 2 + 1))
	{
		sem_post(dt->fork);
		i++;
	}
	if (dt->n_meals != -1)
	{
		i = 0;
		while (i < dt->n_philo)
		{
			if (dt->philo[i].meals_ate < dt->n_meals)
				sem_post(dt->finish_eaten);
			i++;
		}
	}
}

void		ft_clean_sem(t_prog_dt *data)
{
	int i;

	i = 0;
	while (i < data->n_philo)
	{
		ft_clean_sem_phi("/meal_time", i, data);
		i++;
	}
	sem_close(data->fork);
	sem_close(data->finish_eaten);
	sem_close(data->msg);
	sem_unlink("/fork");
	sem_unlink("/finish_eaten");
	sem_unlink("/msg");
}

void		philo_killer(t_prog_dt *data)
{
	int	i;
	int	nb;

	nb = data->n_philo;
	if (data->n_meals != -1)
		pthread_join(data->eats_thread, NULL);
	i = 0;
	while (i < nb)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

void		clean_philo(t_prog_dt *data, t_param *param)
{
	int	i;

	i = 0;
	philo_killer(data);
	ft_clean_sem(data);
	if (param)
		free(param);
	while (i < data->n_philo)
	{
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
