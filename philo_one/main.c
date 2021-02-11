/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/10 19:03:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>//A ENLEVER

void	*my_philo_process(void *data_philo)
{
	int 		i;
	t_philo_dt	*phi;

	phi = (t_philo_dt *)data_philo;
	i = 0;
	
	pthread_mutex_lock(&phi->left_fork->fork);
	sleep(1);
	while (i < 5)
	{

		printf("philo  %s : statut %d\n", phi->name, i);
		sleep(1);
		i++;
	}
	//				if ( i == 2)
			pthread_mutex_unlock(&phi->left_fork->fork);
	//pthread_mutex_unlock (&data->philo[i].left_fork->fork);
	pthread_exit(0);
}

void	launch_philo(t_prog_dt *data)
{
	int		i;
	//void	*ret;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&(data->philo[i].thread), NULL, my_philo_process, &data->philo[i]) < 0)
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
	int		err_nb;
	t_prog_dt		data;
	//t_philo_dt		philo;
//	t_param			param;
	int	i;

	i = 0;
	if (init_prog(ac, av, &data))
		exit(1);
	printf("n_philo = %u\n", data.n_philo);
	printf("n_time to die = %u\n", data.time_to_die);
	printf("time to eat = %u\n", data.time_to_eat);
	printf("time_to sleep = %u\n", data.time_to_sleep);
	printf("n_meals= %d\n", data.n_meals);
	if ((err_nb = init_philo(&data)))
	{
		ft_display_error_msg(err_nb);
		//ft_clean(&phi);
		exit(1);
	}
	launch_philo(&data);
	// i = 0;
	// while (i < data.n_philo)
	// {
	// 	pthread_join(data.philo[i].thread,NULL);
	// 	i++;
	// }
	
	// pthread_join(data.philo[1].thread, NULL);
	// pthread_join(data.philo[2].thread, NULL);
	// pthread_join(data.philo[3].thread, NULL);
	// pthread_join(data.philo[4].thread, NULL);	
	return (0);
}
