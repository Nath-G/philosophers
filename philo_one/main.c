/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/03/22 18:35:24 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>//A ENLEVER

//essayer de protéger les données ate et time_last_meal
//reprendre le clean et les massage d'erreur


static void	*philo_life(void *param)
{
	int 		i;
	t_philo_dt	*phi;
	t_param		*tmp;
	t_prog_dt	*data;

	tmp = (t_param *)param;
	data = tmp->data;
	phi = tmp->philo_dt;
	i = 0;
	while (1)//data->is_last_meal_eaten != 1)// && data->is_one_philo_dead != 1)
	{
		philo_eats(phi, data);
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
	}
	return((void *)0);
}

static int	launch_philo(t_prog_dt *data, t_param *param)
{
	int		i;

	i = 0;
	if (pthread_create(&(data->deaths_thread), NULL, death_checker, data) < 0)
	{
	//	clean_philo(data);
		return(ft_display_msg(PTHREAD_ERROR));
	//	return(1);
	}
	while (i < data->n_philo)
	{
		ft_get_time(data->philo[i].time_last_meal);
		// *data->philo[i].time_start = *data->philo[i].time_last_meal;
		param[i].data = data;
		param[i].philo_dt = &data->philo[i];
		if (pthread_create(&(data->philo[i].thread), NULL, philo_life, &param[i]) < 0)
		{
		//	clean_philo(data);
		//	if (param)
		//		free(param);
			return(ft_display_msg(PTHREAD_ERROR));
		//	return (1);
		}
		i++;
	}

	printf("ok1\n");
//	pthread_mutex_lock(&data->finish);
	monitor(data);//creer un thread//c'est là qu'il attend
	
	printf("ok2\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_prog_dt		data;
	t_param			*param;
//	int				i;

//	i = 0;
	if (init_prog(ac, av, &data))
		return (1);
	if (init_philo(&data))
	{
		clean_philo(&data);
		return (1);
	}
	if (!(param = (t_param *)malloc(sizeof(t_param) * data.n_philo)))
	{
		clean_philo(&data);
		return (ft_display_msg(MALLOC_ERROR));
	//	return(1);
	}
	launch_philo(&data, param);
		printf("ok3\n");
//	monitor(&data);
// pthread_join(data.deaths_thread,NULL);
	if (param)
		free(param);
	clean_philo(&data);
	printf("ok4\n");
	return (0);
}
