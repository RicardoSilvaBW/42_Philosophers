#include "philo.h"

static void announce_death(t_philo *philo)
{
    long    timestamp;

    pthread_mutex_lock(&philo->data->print_mutex);
    pthread_mutex_lock(&philo->data->death_mutex);
    philo->data->sim_running = 0;
    pthread_mutex_unlock(&philo->data->death_mutex);
    timestamp = get_time_ms() - philo->data->start_time;
    printf("%ld %d %s\n", timestamp, philo->id, DIED);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

static int  check_death(t_philo *philo)
{
    long    time_since_meal;

    pthread_mutex_lock(&philo->philo_mutex);
    time_since_meal = get_time_ms() - philo->last_meal_time;
    pthread_mutex_unlock(&philo->philo_mutex);
    if (time_since_meal > philo->data->time_to_die)
    {
        announce_death(philo);
        return (1);
    }
    return (0);
}

static int  check_all_eaten(t_data *data)
{
    int i;
    int all_eaten;

    if (data->max_meals == -1)
        return (0);
    all_eaten = 1;
    i = 0;
    while (i < data->nb_philos)
    {
        pthread_mutex_lock(&data->philos[i].philo_mutex);
        if (data->philos[i].meals_eaten < data->max_meals)
            all_eaten = 0;
        pthread_mutex_unlock(&data->philos[i].philo_mutex);
        i++;
    }
    if (all_eaten)
    {
        pthread_mutex_lock(&data->death_mutex);
        data->sim_running = 0;
        pthread_mutex_unlock(&data->death_mutex);
    }
    return (all_eaten);
}

void    *monitor_routine(void *arg)
{
    t_data  *data;
    int     i;

    data = (t_data *)arg;
    while (1)
    {
        i = 0;
        while (i < data->nb_philos)
        {
            if (check_death(&data->philos[i]))
                return (NULL);
            i++;
        }
        if (check_all_eaten(data))
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}
