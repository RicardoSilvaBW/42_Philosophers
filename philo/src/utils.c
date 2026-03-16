#include "philo.h"

int sim_ended(t_data *data)
{
    int status;

    pthread_mutex_lock(&data->death_mutex);
    status = !(data->sim_running);
    pthread_mutex_unlock(&data->death_mutex);
    return status;
}

void    print_status(t_philo *philo, char *status)
{
    long    timestamp;

    pthread_mutex_lock(&philo->data->print_mutex);
    if (philo->data->sim_running)
    {
        timestamp = get_time_ms() - philo->data->start_time;
        printf("%ld %d %s\n", timestamp, philo->id, status);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}
