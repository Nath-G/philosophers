/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:18:40 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/08 12:51:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_killer(t_prog_dt *data)
{
	int	i;
	int	nb;

	i = 0;
	nb = data->n_philo;
	while (i < nb)
	{
		pthread_join(data->philo[i].thread,NULL);
		i++;
	}
}

int	meals_checker(t_prog_dt *data)
{
	int		i;
	int		nb;

	i = 0;
	nb = data->n_meals;
	//printf("ouououou\n");
	while (i < data->n_philo)
	{
		while (data->philo[i].meals_ate < nb)
		{
			pthread_mutex_lock(&data->philo[i].meals);
			if (data->philo[i].meals_ate < nb)
			{
				pthread_mutex_unlock(&data->philo[i].meals);
				usleep(100);
			}
		//	pthread_mutex_lock(&data->philo[i].meals);
		}
		// while (data->philo[i].meals_ate < nb)// && pthread_mutex_lock(&data->philo[i].meals))
		// {
		// //	printf("ouououou\n");
		// 	pthread_mutex_unlock(&data->philo[i].meals);
		// 	usleep(100);
		// //	i++;
		// }
		i++;
	}
	data->is_last_meal_eaten = 1;
	return (0);
}



int	death_checker(t_prog_dt *data)
{
	int		i;
	int		nb;

	i = 0;
	nb = data->n_philo;
	while (i < nb && !data->is_one_philo_dead)
	{
		pthread_mutex_lock(&data->died);
		if (data->philo[i].is_dead)
			data->is_one_philo_dead = 1;
		//annoncer sa mort???
		pthread_mutex_unlock(&data->died);
			
	//	pthread_mutex_unlock(&data->died);
		// if (data->philo[i].is_dead)
		// 	return(1);
		i++;
		if (i == nb)
			i = 0;
	}
	return (0);
}

void	monitor_meals(t_prog_dt *data)
{
	int		i;
	int		nb;

	i = 0;
	nb = data->n_meals;
	while (!data->is_last_meal_eaten) && !data->is_one_philo_dead)
	{
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->philo[i].meals);
			while (data->philo[i].meals_ate < nb)
			{
				pthread_mutex_unlock(&data->philo[i].meals);
				usleep(100);
				if (data->philo[i].meals_ate < nb)
					pthread_mutex_lock(&data->philo[i].meals);
			}
		i++;
	}
	data->is_last_meal_eaten = 1;
	//	meals_checker(data);
	//	death_checker(data);
	//}
	//if (data->is_last_meal_eaten)
	printf("meals are striked ! \n");//est-ce que je met un message d'erreur?
	//if (data->is_one_philo_dead)
	//	printf("one is dead! \n");
	philo_killer(data);
}

int	monitor_life(t_prog_dt *data)
{
	int	i;
	// struct timeval	cur_time;
	// long unsigned	time_stamp;
	// int	nb;

	i = 0;
	//nb = data->n_philo;
	while (!data->is_one_philo_dead)
	{
		death_checker(data);
		//	if (param->philo_dt[i].is_dead == 1)
	// 		if (data->philo[i].is_dead == 1)
	// 		{
	// 			data->x_is_dead = i;
	// 			ft_get_time(&cur_time);
	// 			time_stamp = (cur_time.tv_sec - data->time_start->tv_sec) * 1000000
	// 				+ (cur_time.tv_usec - data->time_start->tv_usec);
	// 			ft_display_log((time_stamp / 1000), data->philo[i].name, " is dead\n");
	// 			data->is_one_philo_dead = 1;
	// 			philo_killer(data);
	// 			return (1);
	// 		}		
	// 		i++;
	// 		if (i == nb)
	// 			i = 0;
	}
	philo_killer(data);
	return (0);
}

void	monitor(t_prog_dt *data)
{
	int i;
	i = 0;

	if (data->n_meals != -1)
		monitor_meals(data);
	else
		death_checker(data);
}
