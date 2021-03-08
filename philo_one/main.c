/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/08 12:27:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>//A ENLEVER

//essayer de protéger les données ate et time_last_meal
//reprendre le clean et les massage d'erreur

static void	*philo_life(void *data_philo)
{
	int 		i;
	t_philo_dt	*phi;
	t_param		*tmp;
	t_prog_dt	*data;

	tmp = (t_param *)data_philo;
	data = tmp->data;
	phi = tmp->philo_dt;
	i = 0;
	while (data->is_last_meal_eaten != 1 && data->is_one_philo_dead != 1)
	{
		philo_eats(phi, data);
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
		i++;
	}
	return(0);
}

static int	launch_philo(t_prog_dt *data, t_param *param)
{
	int		i;

	i = 0;
	while (i < data->n_philo)
	{
		ft_get_time(data->philo[i].time_last_meal);
		*data->philo[i].time_start = *data->philo[i].time_last_meal;
		printf("start time%ld\n", data->philo[i].time_start->tv_sec);
		param[i].data = data;
		param[i].philo_dt = &data->philo[i];
		if (pthread_create(&(data->philo[i].thread), NULL, philo_life, &param[i]) < 0)
		{
			clean_philo(data);
			if (param)
				free(param);
			ft_display_msg(PTHREAD_ERROR);
			return (1);
		}
		i++;
	}
	monitor(data);
	// i = 0;
	// while (i < data->n_philo)
	// {
	// 	pthread_join(data->philo[i].thread,NULL);
	// 	i++;
	// }
	//clean
	return (0);
}

int	main(int ac, char **av)
{
	t_prog_dt		data;
	t_param			*param;
	int				i;

	i = 0;
	if (init_prog(ac, av, &data))
		return(1);
	if (init_philo(&data))
	{
		clean_philo(&data);
		return(1);
	}
	if (!(param = (t_param *)malloc(sizeof(t_param) * data.n_philo)))
	{
		clean_philo(&data);
		return (ft_display_msg(MALLOC_ERROR));
		return(1);
	}
	launch_philo(&data, param);
	clean_philo(&data);
	if (param)
		free(param);
	return (0);
}
