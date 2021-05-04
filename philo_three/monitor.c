/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:18:40 by nagresel          #+#    #+#             */
/*   Updated: 2021/05/04 12:12:30 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	ft_death(t_prog_dt *dt, char *phi_name, struct timeval cur_time,
				unsigned long int time_stamp)
{
	sem_wait(dt->death_lock);
	dt->one_is_died = 1;
	time_stamp = ft_get_time_diff(&cur_time, dt->time_start);
	ft_display_log((time_stamp / 1000), phi_name, " died\n", dt);
	dt->is_finish = 1;
	sem_wait(dt->log_lock);
	sem_post(dt->end_lock);
}

void		*eats_checker(void *data_philo)
{
	int					i;
	t_prog_dt			*data;
	struct timeval		cur_time;
	unsigned long int	time_stamp;

	data = (t_prog_dt *)data_philo;
	i = 0;
	while (i < data->n_phi && !data->is_finish)
	{
		sem_wait(data->finish_eaten);
		++i;
		if ((i == data->n_phi) && !data->one_is_died)
		{
			ft_get_time(&cur_time);
			time_stamp = ft_get_time_diff(&cur_time, data->time_start);
			ft_display_log((time_stamp / ONE_MLSEC), "all philos",
				" have eaten\n", data);
			data->is_finish = 1;
			sem_wait(data->log_lock);
			sem_post(data->end_lock);
		}
	}
	return (NULL);
}

void		*death_checker(void *param)
{
	t_philo_dt			*phi;
	unsigned long int	time_stamp;
	struct timeval		cur_time;
	t_prog_dt			*dt;

	phi = ((t_param *)param)->philo;
	dt = ((t_param *)param)->data;
	while (!dt->is_finish)
	{
		sem_wait(phi->meal_time);
		ft_get_time(&cur_time);
		time_stamp = ft_get_time_diff(&cur_time, phi->time_last_meal);
		if ((time_stamp) > dt->time_to_die)
		{
			ft_death(dt, phi->name, cur_time, time_stamp);
			break ;
		}
		sem_post(phi->meal_time);
		usleep(1);
	}
	return (NULL);
}

int			meal_nb_monitor(t_prog_dt *data)
{
	data->eats_thread = 0;
	if (data->n_meals != -1)
	{
		if ((pthread_create(&(data->eats_thread), NULL, eats_checker,
				data) < 0))
			return (ft_display_msg(PTHREAD_ERROR));
	}
	return (0);
}
