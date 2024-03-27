#include "philo.h"

bool init_args(t_args *args, char **av, int ac)
{
    if (ac < 5 || ac > 6)
        return (exit_error("Usage: ./philo [args]"));
    if (!is_digit(av))
        return (exit_error("Arguments must be digits"));
    args->philos_num = _atoi(av[1]);
    args->philos_eat_time = _atoi(av[2]);
    args->philos_sleep_time = _atoi(av[3]);
    args->philos_die_time = _atoi(av[4]);
    if (av[5])
        args->philos_eat_times = _atoi(av[5]);
    else
        args->philos_eat_times = -1;
    return (true);
}

void init_forks(t_args *args, t_philo *philos)
{
    int i;

    i = 0;
    while (i < args->philos_num)
        pthread_mutex_init(&(philos[i++].l_fork), NULL);
    i = 0;
    while (i < args->philos_num)
    {
        if (i == args->philos_num - 1)
            philos[i].r_fork = philos[0].l_fork;
        else
            philos[i].r_fork = philos[i + 1].l_fork;
        i++;
    }
}

bool init_philos(t_args *args, t_philo *philos)
{
    int i;

    i = 0;
    while (i < args->philos_num)
    {
        philos[i].id = i + 1;
        philos[i].eating = 0;
        philos[i].meals_eaten = 0;
        philos[i].last_meal = 0;
        philos[i].phil_death_time = args->philos_die_time;
        philos[i].phil_eat_time = args->philos_eat_time;
        philos[i].phil_sleep_time = args->philos_sleep_time;
        philos[i].start_time = get_time();
        philos[i].eat_times = args->philos_eat_times;
        philos[i].philos_num = args->philos_num;
        philos[i].dead = 0;
        if (pthread_create(&philos[i].thread, NULL, (void *)philo_life, &philos[i]) != 0)
            return (exit_error("Error creating thread"));
        i++;
    }
    init_forks(args, philos);
    // for (int i = 0; i < args->philos_num; i++)
    //     printf("Philosopher %d: l_fork = %p, r_fork = %p\n", i, (void *)&philos[i].l_fork, (void *)&philos[i].r_fork);
    i = 0;
    while (pthread_join(philos[i].thread, NULL) != 0)
        i++;

    return (true);
}

// void init_forks(t_args *args, t_philo *philos)
// {
//     int i;

//     i = 0;
//     while (i < args->philos_num)
//     {
//         pthread_mutex_init(&philos[i].r_fork, NULL);
//         pthread_mutex_init(&philos[i].l_fork, NULL);
//         pthread_mutex_init(&philos[i].write_lock, NULL);
//         pthread_mutex_init(&philos[i].dead_lock, NULL);
//         pthread_cond_init(&philos[i].meal_lock, NULL);
//         i++;
//     }
// }