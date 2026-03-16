#include "philo.h"

static int  init_forks(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
    if (!data->forks)
        return (0);
    i = 0;
    while (i < data->nb_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&data->forks[i]);
            free(data->forks);
            data->forks = NULL;
            return (0);
        }
        i++;
    }
    return (1);
}

static int  init_philos(t_data *data)
{
    int i;

    data->philos = malloc(sizeof(t_philo) * data->nb_philos);
    if (!data->philos)
        return (0);
    i = 0;
    while(i < data->nb_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = data->start_time;
        data->philos[i].left_fork = i;
        data->philos[i].right_fork = (i + 1) % data->nb_philos;
        data->philos[i].data = data;
        if (pthread_mutex_init(&data->philos[i].philo_mutex, NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&data->philos[i].philo_mutex);
            free(data->philos);
            data->philos = NULL;
            return (0);
        }
        i++;
    }
    return (1);
}

void    cleanup(t_data *data)
{
    int i;

    i = 0;
    if (data->philos)
    {
        while (i < data->nb_philos)
        {
            pthread_mutex_destroy(&data->philos[i].philo_mutex);
            i++;
        }
        free(data->philos);
        data->philos = NULL;
    }
    if (data->forks)
    {
        i = 0;
        while (i < data->nb_philos)
        {
            pthread_mutex_destroy(&data->forks[i]);
            i++;
        }
        free(data->forks);
        data->forks = NULL;
    }
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
}

int init_data(t_data *data)
{
    data->sim_running = 1;
    data->start_time = get_time_ms();
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
        return (0);
    if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
    {
        pthread_mutex_destroy(&data->print_mutex);
        return (0);
    }
    if (!init_forks(data))
    {
        pthread_mutex_destroy(&data->print_mutex);
        pthread_mutex_destroy(&data->death_mutex);
        return (0);
    }
    if (!init_philos(data))
    {
        cleanup(data);
        return (0);
    }
    return (1);
}
