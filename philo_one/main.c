/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/04/30 14:07:08 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*philo_life(void *param)
{
	t_philo_dt	*phi;
	t_param		*tmp;
	t_prog_dt	*data;

	tmp = (t_param *)param;
	data = tmp->data;
	phi = tmp->philo_dt;
	while (!data->is_finish)
	{
		philo_eats(phi, data);
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
	}
	return (NULL);
}

static void	*philo_life_bis(void *param)
{
	t_philo_dt	*phi;
	t_param		*tmp;
	t_prog_dt	*data;

	tmp = (t_param *)param;
	data = tmp->data;
	phi = tmp->philo_dt;
	while (!data->is_finish)
	{
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
		philo_eats(phi, data);
	}
	return (NULL);
}

static int	launch_philo(t_prog_dt *data, t_param *param)
{
	int	i;

	if (gettimeofday(data->time_start, NULL))
		return (ft_display_msg(TIME_ERROR));
	i = -1;
	while (++i < data->n_philo && param && data)
	{
		param[i].data = data;
		param[i].philo_dt = &data->philo[i];
		param[i].philo_dt->time_last_meal->tv_sec = data->time_start->tv_sec;
		param[i].philo_dt->time_last_meal->tv_usec = data->time_start->tv_usec;
		// ft_get_time(data->philo[i].time_last_meal);
		if (!data->philo[i].is_start_sleeping)
			if (pthread_create(&(data->philo[i].thread), NULL, philo_life,
				&param[i]) < 0)
				return (ft_display_msg(PTHREAD_ERROR));
		if (data->philo[i].is_start_sleeping)
			if (pthread_create(&(data->philo[i].thread), NULL, philo_life_bis,
				&param[i]) < 0)
				return (ft_display_msg(PTHREAD_ERROR));
		if (pthread_create(&(data->philo[i].death_thread), NULL, death_checker,
				&param[i]) < 0)
			ft_display_msg(PTHREAD_ERROR);
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_prog_dt	data;
	t_param		*param;

	if (init_prog(ac, av, &data))
		return (1);
	if (!(param = (t_param *)malloc(sizeof(t_param) * data.n_philo)))
	{
		clean_philo(&data, param);
		return (ft_display_msg(MALLOC_ERROR));
	}
	if (init_philo(&data))
	{
		clean_philo(&data, param);
		return (1);
	}
	if (data.n_meals != -1)
		if (pthread_create((&data.eats_thread), NULL, eats_checker, &data) < 0)
			return (ft_display_msg(PTHREAD_ERROR));
	launch_philo(&data, param);
	pthread_mutex_lock(&(data.finish_lock));
	if (data.n_meals != -1)
		ft_unlock_mutex(&data);
	clean_philo(&data, param);
	return (0);
}
