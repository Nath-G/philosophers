/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:08:21 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/10 19:05:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

# define ARG_NB_ERROR -1
# define ARG_FORMAT_ERROR -2
# define ARG_VALUE_ERROR -3
# define PTHREAD_ERROR -4
# define MALLOC_ERROR -5
# define MUTEX_ERROR -6

typedef enum e_status
{
	SLEEPING,
	EATING,
	THINKING
}			t_status;


typedef struct		s_fork
{
	pthread_mutex_t	fork;
	size_t			nb_last;
}					t_fork;


typedef struct s_philo_dt
{
	char			*name;
	size_t			id;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t *lock_last_meal;
	struct timeval	*time_last_meal;
//	void			*next;	
}				t_philo_dt;

typedef struct s_prog_dt
{
	int				n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				n_meals;
	t_philo_dt		*philo;
}				t_prog_dt;


typedef struct s_param
{

	t_prog_dt			*data;
	t_philo_dt		*philo_dt;
}				t_param;

/* init */
int		init_prog(int ac, char **av, t_prog_dt *data);
int		init_philo(t_prog_dt *data);
/* log */
int	ft_display_error_msg(int error_nb);

/* */
void	launch_philo(t_prog_dt *data);

/* utils */
int		ft_strlen(char *str);
int		ft_write_err_msg(char *err_msg, int ret);
int		ft_atoui(char *str, unsigned int *nb);
int		ft_atoi(char *str, int *nb);
void	fill_nbr(size_t nbr, char *ptr);
void	ft_bzero(void *s, size_t n);

#endif