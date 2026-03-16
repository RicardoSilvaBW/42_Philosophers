#include "philo.h"

long    get_time_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    precise_sleep(long ms, t_data *data)
{
    long    start;

    start = get_time_ms();
    while ((get_time_ms() - start) < ms)
    {
        if (sim_ended(data))
            break ;
        usleep(100);
    }
}
