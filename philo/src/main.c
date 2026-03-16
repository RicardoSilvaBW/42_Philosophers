#include "philo.h"

static int  start_simulation(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL,
                    philo_routine, &data->philos[i]) != 0)
        {
            pthread_mutex_lock(&data->death_mutex);
            data->sim_running = 0;
            pthread_mutex_unlock(&data->death_mutex);
            return (0);
        }
        i++;
    }
    if (pthread_create(&data->monitor, NULL, monitor_routine, data) != 0)
    {
        pthread_mutex_lock(&data->death_mutex);
        data->sim_running = 0;
        pthread_mutex_unlock(&data->death_mutex);
        return (0);
    }
    return (1);
}

static void stop_simulation(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
    pthread_join(data->monitor, NULL);
}

int main(int argc, char **argv)
{
    t_data  data;

    memset(&data, 0, sizeof(t_data));
    if (!parse_args(&data, argc, argv))
        return (1);
    if (!init_data(&data))
    {
        printf("Error: initialization failed\n");
        return (1);
    }
    if (!start_simulation(&data))
    {
        stop_simulation(&data);
        cleanup(&data);
        return (1);
    }
    stop_simulation(&data);
    cleanup(&data);
    return (0);
}
