/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:01:48 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/10 19:03:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	check_argument_format(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if(av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	init_data(t_prog_dt *data)
{
	data->n_philo = 0;
	data-> time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->n_meals = -1;
}

int		init_philo(t_prog_dt *data)
{
	int			i;

	i = 0;

	if (!(data->philo = (t_philo_dt *)malloc(sizeof(t_philo_dt) * (data->n_philo))))
		return (MALLOC_ERROR);
	while (i < data->n_philo)
	{
		if (!(data->philo[i].name = malloc(sizeof(char) * 20))
			|| !(data->philo[i].right_fork = (t_fork *)malloc(sizeof(t_fork) * (data->n_philo)))
			|| !(data->philo[i].left_fork = (t_fork *)malloc(sizeof(t_fork) * (data->n_philo))))
			return (MALLOC_ERROR);
		i++;
	}
	i = 0;
	while(i < data->n_philo)
	{
		if (pthread_mutex_init(&data->philo[i].left_fork->fork, NULL)) //!(i = 0) && ...dans la condition
			return (MUTEX_ERROR);
		if (pthread_mutex_init(&data->philo[i].right_fork->fork, NULL)) //!(i = 0) && ...dans la condition
			return (MUTEX_ERROR);
		data->philo[i].id = (size_t)i + 1;
//		*data->philo[i].name = "";
		printf("size of %lu ok\n", sizeof(char) * 20);
		fill_nbr(data->philo[i].id, data->philo[i].name);
		printf("ok\n");
		i++;

	}
	//initialiser l'heure du repas comme si les philo venaient de manger
	return (0);
}

int		init_prog(int ac, char **av, t_prog_dt *data)
{

	init_data(data);
	if (ac != 5 && ac != 6)
		return (ft_display_error_msg(ARG_NB_ERROR));
	if (check_argument_format(av))
		return (ft_display_error_msg(ARG_FORMAT_ERROR));	
	if (ft_atoi(av[1], &data->n_philo))
		return (ft_display_error_msg(ARG_FORMAT_ERROR));
	if (data->n_philo < 2)
		return (ft_display_error_msg(ARG_VALUE_ERROR));
	ft_atoui(av[2], &data->time_to_die);
	ft_atoui(av[3], &data->time_to_eat);
	ft_atoui(av[4], &data->time_to_sleep);
	if (ac == 6)
	{
		if (ft_atoi(av[5], &data->n_meals))
			return (ft_display_error_msg(ARG_VALUE_ERROR));
	}
	init_philo(data);
	return (0);
}
