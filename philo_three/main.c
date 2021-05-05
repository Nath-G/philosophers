/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagresel <nagresel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:18:35 by nagresel          #+#    #+#             */
/*   Updated: 2021/05/05 16:41:25 by nagresel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	philo_life(t_param *param, t_philo_dt *phi)
{
	t_prog_dt	*data;

	data = param->data;
	while (!data->is_finish)
	{
		philo_eats(phi, data);
		philo_sleeps(phi, data);
		philo_thinks(phi, data);
	}
	return (0);
}

static int	launch_philo(t_prog_dt *data, t_param *param)
{
	int		i;
	pid_t	child_pid;

	if (gettimeofday(data->time_start, NULL))
		return (ft_display_msg(TIME_ERROR));
	i = 0;
	param->data = data;
	while (i < data->n_phi && !data->is_finish)
	{
		param->philo = &(data->philo[i]);
		if (ft_get_time(param->philo->time_last_meal))
			return (ft_display_msg(TIME_ERROR));
		param->philo->pid = fork();
		if (!(child_pid = param->philo->pid))
		{
			pthread_create(&(param->philo->death_thread), NULL,
				(void*)death_checker, (void*)param);
			philo_life(param, param->philo);
		}
		else if (child_pid < 0)
			return (ft_display_msg(FORK_ERROR));
		i++;
	}
	free(param);
	return (0);
}

int			main(int ac, char **av)
{
	t_prog_dt	data;
	t_param		*param;

	if (init_prog(ac, av, &data))
		return (1);
	if (!(param = (t_param *)malloc(sizeof(t_param) * data.n_phi)))
	{
		clean_phi(&data);
		return (ft_display_msg(MALLOC_ERROR));
	}
	if (init_philo(&data))
		return (clean_phi(&data));
	meal_nb_monitor(&data);
	launch_philo(&data, param);
	sem_wait(data.end_lock);
	clean_phi(&data);
	return (0);
}
