/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/05 19:27:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>//A ENLEVER

// void	*my_thread_process(void *arg)
// {
// 	int j;

// 	j = 0;
// 	while (j< 5)
// 	{
// 		printf("(*p) philo %d: état j= %d\n", (char*)arg, j);
// 		sleep(1);
// 		j++;
// 	}
// 	pthread_exit(0);
// }

void	*my_philo_process(void *arg)
{
	int i;

	i = 0;
	while (i < 5)
	{
		printf("philo %s : état %d\n",  (char*)arg, i);
		sleep(0);
		i++;
	}
	pthread_exit(0);
}

int	main(int ac, char **av)
{
	void		*ret;
	int		err_nb;
	t_prog_dt		data;
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
		printf("name philo 1  =  %s\n", data.philo[0].name);
	//printf("fork =  %p\n", data.philo[0].right_fork->fork);
	while (i < data.n_philo)
	{
		printf("test name %s\n", data.philo[i].name);
		if (pthread_create(&data.philo[i].thread, NULL, my_philo_process, data.philo[i].name) < 0)
			ft_display_error_msg(PTHREAD_ERROR);
		
		i++;
	}
	i = 0;
	while (i < data.n_philo)
	{
		(void)pthread_join(data.philo[i].thread, &ret);
		i++;
	}

	return (0);
}
