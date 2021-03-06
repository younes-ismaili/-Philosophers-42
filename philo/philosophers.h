/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:52:48 by yismaili          #+#    #+#             */
/*   Updated: 2022/06/05 14:08:20 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	int				st;
	int				eaten;
	unsigned int	get_t;
	pthread_mutex_t	mut_write;
}	t_data;

typedef struct s_philo
{
	int				philo_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	fork;
	pthread_t		th_philo;
	t_data			*data;
	int				count_eat;
	unsigned int	time_to_kill;
}	t_philo;

int				ft_atoi(const char *str);
void			init_args(t_data	*data, t_philo *philo);
void			init_philo(t_philo *philo, t_data *data);
void			take_forks(t_philo *philo);
void			get_message(char *s, int id, t_data *data, char *clor);
unsigned int	get_time(void);
void			philo_activities(t_philo *philo);
void			*check_died(void *ptr);
void			philo_activities(t_philo *philo);
void			*routine(void *ptr);
void			create_thread(t_philo *philo, t_data *data);
void			init_data(t_data *data, char **av, int ac);
int				ft_die(char *str);
void			print_error(char *s, t_data *data);
void			ft_usleep(long time);
void			ft_free(t_philo *philo, t_data *data);
#endif
