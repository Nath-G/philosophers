/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/23 19:16:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>//A ENLEVER

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
	//faut il faire le clean de la structure param ici???
	//printf("dans launch  data i = %d dans init id = %d et name = %s \n", i, phi->id, data->phi.name);
	//printf("dans launch param i = %d dans init id = %d et name = %s \n", i, ph->id, param[i].philo_dt->name);
	sleep(1);
	while (i < 2 || i < data->n_meals)
	{
		philo_eats(phi, data);
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
		//	printf("timestamp_in_ms %s is sleeping %d\n", phi->name, i);
		//	printf("timestamp_in_ms name = %s id = %d is thinking i = %d\n", phi->name, phi->id, i);
		//sleep(1);
		i++;
	}
	pthread_exit(0);
}

static int	launch_philo(t_prog_dt *data, t_param *param)
{
	int		i;


	// data->philo[i].id = i + 1;
	// fill_nbr(data->philo[i].id, data->philo[i].name);
	// printf("i = %d dans init id = %d et name = %s \n", i, data->philo[i].id, data->philo[i].name);

	i = 0;
	while (i < data->n_philo)
	{

		param[i].data = data;
		param[i].philo_dt = &data->philo[i];
		if (pthread_create(&(data->philo[i].thread), NULL, philo_life, &param[i]) < 0)
		{
			//free clean
			ft_display_msg(PTHREAD_ERROR);
			exit (1);
		}
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->philo[i].thread,NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_prog_dt		data;
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
		return (ft_display_msg(MALLOC_ERROR));
		exit(1);
	}
	launch_philo(&data, param);
	// pthread_join(data.philo[1].thread, NULL);
	// pthread_join(data.philo[2].thread, NULL);
	// pthread_join(data.philo[3].thread, NULL);
	// pthread_join(data.philo[4].thread, NULL);	
	return (0);
}
