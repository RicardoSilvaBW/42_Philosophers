#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define FORK       "has taken a fork"
# define EATING     "is eating"
# define SLEEPING   "is sleeping"
# define THINKING   "is thinking"
# define DIED       "died"

typedef struct s_data   t_data;

typedef struct s_philo
{
    int             id;
    int             left_fork;
    int             right_fork;
    int             meals_eaten;
    long            last_meal_time;
    pthread_t       thread;
    pthread_mutex_t philo_mutex;
    t_data          *data;
}   t_philo;

struct s_data
{
    int             nb_philos;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             max_meals;
    int             sim_running;
    long            start_time;
    pthread_t       monitor;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t *forks;
    t_philo         *philos;
};

int     parse_args(t_data *data, int argc, char **argv);

long    get_time_ms(void);
void    precise_sleep(long ms, t_data *data);

void    cleanup(t_data *data);
int     init_data(t_data *data);

void    print_status(t_philo *philo, char *status);
int     sim_ended(t_data *data);

void    philo_eat(t_philo *philo);
void    philo_sleep(t_philo *philo);
void    philo_think(t_philo *philo);

void    *philo_routine(void *arg);

void    *monitor_routine(void *arg);

#endif
