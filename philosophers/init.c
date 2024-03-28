#include "philo.h"

bool init_args(t_args *args, char **av, int ac)
{
    if (ac < 5 || ac > 6)
        return (exit_error("Usage: ./philo [args]"));
    if (!is_digit(av))
        return (exit_error("Arguments must be digits"));
    args->philos_num = _atoi(av[1]);
    if (args->philos_num > PHILOS_MAX)
        return (exit_error("Too many philosophers"));
    if (args->philos_num < 1)
        return (exit_error("Not enough philosophers"));
    args->time_to_die = _atoi(av[2]);
    args->time_to_eat = _atoi(av[3]);
    args->time_to_sleep = _atoi(av[4]);
    if (av[5])
        args->philos_eat_times = _atoi(av[5]);
    else
        args->philos_eat_times = -1;
    return (true);
}

void init_forks(pthread_mutex_t *forks, t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos->philos_num)
        pthread_mutex_init(&forks[i++], NULL);
}

bool init_philos(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while (i < args->philos_num)
    {
        philos[i].id = i + 1;
        philos[i].eating = 0;
        philos[i].meals_eaten = 0;
        philos[i].last_meal = 0;
        philos[i].phil_death_time = args->time_to_die;
        philos[i].phil_eat_time = args->time_to_eat;
        philos[i].phil_sleep_time = args->time_to_sleep;
        philos[i].start_time = get_time();
        philos[i].eat_times = args->philos_eat_times;
        philos[i].philos_num = args->philos_num;
        philos[i].dead = 0;
        philos[i].l_fork = &forks[i];
        if (i == 0)
            philos[i].r_fork = &forks[args->philos_num - 1];
        else
            philos[i].r_fork = &forks[i - 1];
        if (pthread_create(&philos[i].thread, NULL, (void *)philo_life, &philos[i]) != 0)
            return (exit_error("Error creating thread"));
        i++;
    }
    i = 0;
    while (pthread_join(philos[i].thread, NULL) != 0)
        i++;

    return (true);
}

