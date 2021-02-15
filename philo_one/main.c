/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/15 17:49:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>//A ENLEVER

void	taken_fork(t_philo_dt *phi)
{
	pthread_mutex_lock(&phi->left_fork);
	pthread_mutex_lock(&phi->right_fork);
	//start timestamp_in_ms;
	printf("timestamp_in_ms %s has taken a fork \n", phi->name);
	printf("timestamp_in_ms %s has taken a fork \n", phi->name);
	printf("timestamp_in_ms %s is eating\n", phi->name);
	// while (gettime - starttime < philo->time_to_eat)
	// 	usleep("1");
	sleep(5);
	pthread_mutex_unlock(&phi->left_fork);
	pthread_mutex_unlock(&phi->right_fork);
	//printf("")
}

void	*my_philo_process(void *data_philo)
{
	int 		i;
	t_philo_dt	*phi;
	t_param		*tmp;
	t_prog_dt	*data;

	tmp = (t_param *)data_philo;
	data = tmp->data;
	phi = tmp->philo_dt;

	i = 0;
	//faut il faire le clean de la structure param ici???
	printf("nb de repas : %d\n", data->n_meals);
	sleep(1);
	while (i < 5 && i < data->n_meals)
	{
		taken_fork(phi);
		printf("timestamp_in_ms %s is sleeping %d\n", phi->name, i);
		printf("timestamp_in_ms %s is thinking %d\n", phi->name, i);
		sleep(1);
		i++;
	}

	pthread_exit(0);
}

void	launch_philo(t_prog_dt *data, t_param *param)
{
	int		i;

	i = 0;
	while (i < data->n_philo)
	{
		
		param[i].data = data;
		param[i].philo_dt = &data->philo[i];
		if (pthread_create(&(data->philo[i].thread), NULL, my_philo_process, &param[i]) < 0)
			ft_display_error_msg(PTHREAD_ERROR);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->philo[i].thread,NULL);
		i++;
	}
	
}


int	main(int ac, char **av)
{
	//void		*ret;
//	int		err_nb;
	t_prog_dt		data;
//	t_philo_dt		*philo;
	t_param			*param;
	int	i;
	
	i = 0;
	if (init_prog(ac, av, &data))
		exit(1);
	if (init_philo(&data))
	{
		//ft_clean(&phi);
		exit(1);
	}
	if (!(param = (t_param *)malloc(sizeof(t_param) * data.n_philo)))
	{
		//ft_clean(&phi);
		return (ft_display_error_msg(MALLOC_ERROR));
		exit(1);
	}
	launch_philo(&data, param);
	// pthread_join(data.philo[1].thread, NULL);
	// pthread_join(data.philo[2].thread, NULL);
	// pthread_join(data.philo[3].thread, NULL);
	// pthread_join(data.philo[4].thread, NULL);	
	return (0);
}
