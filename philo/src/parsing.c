#include "philo.h"

static int  ft_atoi_strict(char *str)
{
    long    result;
    int     i;

    result = 0;
    i = 0;
    if (!str || str[0] == '\0')
        return (-1);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        result = (result * 10) + (str[i] - '0');
        if (result > INT_MAX)
            return (-1);
        i++;
    }
    if (result == 0)
        return (-1);
    return ((int)result);
}

static int  is_valid_input(int argc, char **argv)
{
    int i;

    if (argc < 5 || argc > 6)
    {
        printf("Error: wrong number of arguments\n");
        return (0);
    }
    i = 1;
    while (i < argc)
    {
        if (ft_atoi_strict(argv[i]) == -1)
        {
            printf("Error: invalid arguments\n");
            return (0);
        }
        i++;
    }
    return (1);
}

int parse_args(t_data *data, int argc, char **argv)
{
    if (!is_valid_input(argc, argv))
        return (0);
    data->nb_philos = ft_atoi_strict(argv[1]);
    data->time_to_die = ft_atoi_strict(argv[2]);
    data->time_to_eat = ft_atoi_strict(argv[3]);
    data->time_to_sleep = ft_atoi_strict(argv[4]);
    data->max_meals = -1;
    if (argc == 6)
        data->max_meals = ft_atoi_strict(argv[6]);
    return (1);
}
