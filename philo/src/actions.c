#include "philo.h"

static void take_forks(t_philo *philo)
{
    t_data  *data;

    data = philo->data;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&data->forks[philo->right_fork]);
        print_status(philo, FORK);
        pthread_mutex_lock(&data->forks[philo->left_fork]);
        print_status(philo, FORK);
    }
    else 
    {
        pthread_mutex_lock(&data->forks[philo->left_fork]);
        print_status(philo, FORK);
        pthread_mutex_lock(&data->forks[philo->right_fork]);
        print_status(philo, FORK);
    }
}

static void put_down_forks(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    pthread_mutex_unlock(&data->forks[philo->left_fork]);
    pthread_mutex_lock(&data->forks[philo->right_fork]);
}

static void update_meal(t_philo *philo)
{
    pthread_mutex_lock(&philo->philo_mutex);
    philo->last_meal_time = get_time_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->philo_mutex);
}

void    philo_eat(t_philo *philo)
{
    take_forks(philo);
    print_status(philo, EATING);
    update_meal(philo);
    precise_sleep(philo->data->time_to_eat, philo->data);
    put_down_forks(philo);
}

void    philo_sleep(t_philo *philo)
{
    print_status(philo, SLEEPING);
    precise_sleep(philo->data->time_to_sleep, philo->data);
}

void    philo_think(t_philo *philo)
{
    long    think_time;

    print_status(philo, THINKING);
    think_time = philo->data->time_to_die
        - philo->data->time_to_eat
        - philo->data->time_to_sleep;
    if (think_time > 0)
        precise_sleep(think_time / 2, philo->data);
}
