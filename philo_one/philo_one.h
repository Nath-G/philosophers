/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:08:21 by nagresel          #+#    #+#             */
/*   Updated: 2021/02/26 16:12:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ONE_MILLISEC 1000
# define ARG_NB_ERROR -1
# define ARG_FORMAT_ERROR -2
# define ARG_VALUE_ERROR -3
# define MALLOC_ERROR -4
# define PTHREAD_ERROR -5
# define MUTEX_ERROR -6
# define TIME_ERROR -7
# define TIMESTAMP_INFO 10
# define FORK_INFO 11
# define EATING_INFO 12
# define THINKING_INFO 13
# define SLEEPING_INFO 14
// typedef enum e_status
// {
// 	SLEEPING,
// 	EATING,
// 	THINKING
// }			t_status;


// typedef struct		s_fork
// {
// 	pthread_mutex_t	fork;
// 	size_t			nb_last;
// }					t_fork;


typedef struct s_philo_dt
{
	char			*name;
	int				id;
	pthread_t		thread;
	pthread_mutex_t left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	*time_last_meal;	
}				t_philo_dt;

typedef struct s_prog_dt
{
	int				n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				n_meals;
	struct timeval 	*time_start;
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

/* clean*/
void	clean_philo(t_prog_dt *data);
/* log */
int		ft_display_msg(int msg_nb);
//int		ft_display_lunbr(long unsigned nbr);
int		ft_get_time(struct timeval *cur_time);
void	ft_display_log(long unsigned time_stamp, char *philo_name, char *msg);

/* */
//int		launch_philo(t_prog_dt *data, t_param *param);
int		philo_eats(t_philo_dt *phi, t_prog_dt *data);
int		philo_sleeps(t_philo_dt *phi, t_prog_dt *data);
int		philo_thinks(t_philo_dt *phi, t_prog_dt *data);

/* utils */
int		ft_strlen(const char *str);
int		ft_write_msg(char *msg, int ret);
int		ft_atoui(char *str, unsigned int *nb);
int		ft_atoi(char *str, int *nb);
void	fill_nbr(int nbr, char *ptr);
void	fill_lunbr(long unsigned nbr, char *ptr);
///void	ft_bzero(void *s, size_t n);
char	*ft_strjoinfree(char *s1, const char *s2);

#endif
