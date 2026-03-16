#include "philo.h"

static void single_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
    print_status(philo, FORK);
    precise_sleep(philo->data->time_to_die, philo->data);
    pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

static void stagger_start(t_philo *philo)
{
    if (philo->id % 2 == 0)
        precise_sleep(philo->data->time_to_eat, philo->data);
}

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->data->nb_philos == 1)
    {
        single_philo(philo);
        return (NULL);
    }
    stagger_start(philo);
    while(!sim_ended(philo->data))
    {
        philo_eat(philo);
        if (sim_ended(philo->data))
            break ;
        philo_sleep(philo);
        if (sim_ended(philo->data))
            break ;
        philo_think(philo);
    }
    return (NULL);
}
