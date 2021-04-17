/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:18:40 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/16 20:39:42 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	ft_death(t_prog_dt *dt, char *phi_name, struct timeval cur_time,
				unsigned long int time_stamp)
{
	dt->is_finish = 1;
	dt->one_is_died = 1;
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	ft_display_log((time_stamp / ONE_MLSEC), phi_name, " died\n",
		&(dt->output_protection));
}

void		*eats_checker(void *data_philo)
{
	int					i;
	t_prog_dt			*data;
	struct timeval		cur_time;
	unsigned long int	time_stamp;

	data = (t_prog_dt *)data_philo;
	i = 0;
	while (i < data->n_philo && !data->one_is_died)
	{
		pthread_mutex_lock(&data->philo[i].finish_eaten);
		++i;
	}
	data->is_finish = 1;
	if (!data->one_is_died)
	{
		ft_get_time(&cur_time);
		time_stamp = ft_get_time_diff(&cur_time, data->time_start);
		usleep(5);
		ft_display_log((time_stamp / ONE_MLSEC), "all philos", " have eaten\n",
		&(data->output_protection));
		//printf("%lu All philosophers almost ate %d times!\n", time_stamp,
		//	data->n_meals);
	}
	return (NULL);
}

void		death_checker(t_prog_dt *dt)
{
	int					i;
	t_philo_dt			*phi;
	unsigned long int	time_stamp;
	struct timeval		cur_time;

	i = 0;
	phi = dt->philo;
	while (!dt->is_finish)
	{
		pthread_mutex_lock(&(phi[i].meal_time));
		ft_get_time(&cur_time);
		time_stamp = ft_get_time_diff(&cur_time, phi[i].time_last_meal);
		if ((time_stamp) > dt->time_to_die)
			ft_death(dt, phi[i].name, cur_time, time_stamp);
		pthread_mutex_unlock(&(phi[i].meal_time));
		++i;
		if (i == dt->n_philo)
			i = 0;
	}
	if (dt->n_meals != -1)
		ft_unlock_mutex(dt);
}
