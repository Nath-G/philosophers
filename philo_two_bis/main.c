/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/05/03 11:30:10 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	*philo_life(void *param)
{
	int			i;
	t_philo_dt	*phi;
	t_param		*tmp;
	t_prog_dt	*data;

	tmp = (t_param *)param;
	data = tmp->data;
	phi = tmp->philo_dt;
	i = 0;
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
	int			i;
	t_philo_dt	*phi;
	t_param		*tmp;
	t_prog_dt	*data;

	tmp = (t_param *)param;
	data = tmp->data;
	phi = tmp->philo_dt;
	i = 0;
	while (!data->is_finish)
	{
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
		philo_eats(phi, data);
	}
	return (NULL);
}

static int	create_philo(t_param *param, void(*ft_liffe)(void*))
{
	// if (gettimeofday(param->data->time_start, NULL))
	// 	return (ft_display_msg(TIME_ERROR));
	// param->philo_dt->time_last_meal->tv_sec = param->data->time_start->tv_sec;
	// param->philo_dt->time_last_meal->tv_usec = param->data->time_start->tv_usec;
	// ft_get_time(param->philo_dt->time_last_meal);
	//if (!param->philo_dt->is_start_sleeping)
		if (pthread_create(&(param->philo_dt->thread), NULL, (void*)ft_liffe,
				param) < 0)
			return (ft_display_msg(PTHREAD_ERROR));
	//if (param->philo_dt->is_start_sleeping)
		//if (pthread_create(&(param->philo_dt->thread), NULL, philo_life_bis,
			// 	param) < 0)
			// return (ft_display_msg(PTHREAD_ERROR));
	// if (pthread_create(&(param->philo_dt->death_thread), NULL, death_checker,
	// 		param) < 0)
	// 	return (ft_display_msg(PTHREAD_ERROR));
	return (0);
}

static int	launch_philo(t_prog_dt *data, t_param *param)
{
	int	i;
	void(*pf);
	void(*pf2);
	pf = &philo_life;
	pf2 = &philo_life_bis;

	i = -1;
	if (gettimeofday(data->time_start, NULL))
		return (ft_display_msg(TIME_ERROR));
	while (++i < data->n_philo)
	{
		param[i].data = data;
		param[i].philo_dt = &data->philo[i];
		param[i].philo_dt->time_last_meal->tv_sec =
			data->time_start->tv_sec;
		param[i].philo_dt->time_last_meal->tv_usec =
		data->time_start->tv_usec;
		// ft_get_time(param[i].philo_dt->time_last_meal);
	//	i = -1;
	//	while (++i < data->n_philo)
	//	{
			if (!(param[i].philo_dt->is_start_sleeping))
				create_philo(&param[i], pf);
			else
				create_philo(&param[i], pf2);
		}
			
		// if (!param->philo_dt->is_start_sleeping)
		// 	if (pthread_create(&(param[i].philo_dt->thread), NULL, philo_life,
		// 			&(param[i])) < 0)
		// 		return (ft_display_msg(PTHREAD_ERROR));
		// if (param->philo_dt->is_start_sleeping)
		// 	if (pthread_create(&(param[i].philo_dt->thread), NULL, philo_life_bis,
		// 		&(param[i])) < 0)
		// 		return (ft_display_msg(PTHREAD_ERROR));
	//}
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
		return (clean_philo(&data, param));
	if (data.n_meals != -1)
		if (pthread_create((&data.eats_thread), NULL, eats_checker, &data) < 0)
			return (ft_display_msg(PTHREAD_ERROR));
	if (pthread_create((&data.deaths_thread), NULL, death_checker, &data) < 0)
		return (ft_display_msg(PTHREAD_ERROR));
	launch_philo(&data, param);
	if (sem_wait(data.end_lock))
		return (1);
	clean_philo(&data, param);
	return (0);
}
