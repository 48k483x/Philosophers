#include "philo.h"

bool	init_args(t_args *args, char **av, int ac)
{
	if (ac < 5 || ac > 6)
		return (error());
	if (!is_digit(av))
		return (exit_error("Arguments must be digits || Positive nums"));
	args->philos_num = _atoi(av[1]);
	if (args->philos_num > PHILOS_MAX)
		return (exit_error("Too many philosophers"));
	if (args->philos_num < 1)
		return (exit_error("Not enough philosophers"));
	args->time_to_die = _atoi(av[2]);
	args->time_to_eat = _atoi(av[3]);
	args->time_to_sleep = _atoi(av[4]);
	if (args->time_to_die < 1)
		return (exit_error("Time to die must be greater than 0"));
	if (args->time_to_eat < 1)
		return (exit_error("Time to eat must be greater than 0"));
	if (args->time_to_sleep < 1)
		return (exit_error("Time to sleep must be greater than 0"));
	if (av[5])
		args->philos_eat_times = _atoi(av[5]);
	else
		args->philos_eat_times = -1;
	return (true);
}

void	init_forks(pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->philos_num)
		pthread_mutex_init(&forks[i++], NULL);
}

void	helper(int i, t_philo *philos, t_args *args, pthread_mutex_t *forks)
{
	philos[i].eating_count = 0;
	if (i == 0)
		philos[i].r_fork = &forks[args->philos_num - 1];
	else
		philos[i].r_fork = &forks[i - 1];
}

bool	init_philos(t_args *args, t_philo *philos,
					t_prog *prog, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	init_prog(philos, prog);
	while (++i < args->philos_num)
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].phil_death_time = args->time_to_die;
		philos[i].phil_eat_time = args->time_to_eat;
		philos[i].phil_sleep_time = args->time_to_sleep;
		philos[i].start_time = get_time();
		philos[i].last_meal = get_time();
		philos[i].eat_times = args->philos_eat_times;
		philos[i].philos_num = args->philos_num;
		philos[i].write_lock = &prog->write_lock;
		philos[i].dead_lock = &prog->dead_lock;
		philos[i].meal_lock = &prog->meal_lock;
		philos[i].dead = &prog->death_flag;
		philos[i].l_fork = &forks[i];
		helper(i, philos, args, forks);
	}
	return (true);
}

// int	init_thread(t_philo *philos, pthread_mutex_t *forks, t_prog *prog)
// {
// 	pthread_t	thread;
// 	int			i;

// 	if (pthread_create(&thread, NULL, &monitor, prog->philo) != 0)
// 		destroy_all("Error creating thread", prog, forks, philos);
// 	i = -1;
// 	while (++i < philos->philos_num)
// 	{
// 		if (pthread_create(&philos[i].thread, NULL,
// 				&philo_life, &philos[i]) != 0)
// 			destroy_all("Error creating thread", prog, forks, philos);
// 	}
// 	if (pthread_join(thread, NULL) != 0)
// 		destroy_all("Error joining thread", prog, forks, philos);
// 	i = -1;
// 	while (++i < philos->philos_num && prog->death_flag != 1)
// 	{
// 		if (pthread_join(philos[i].thread, NULL) != 0)
// 			destroy_all("Error joining thread", prog, forks, philos);
// 	}
// 	return (0);
// }
int init_thread(t_philo *philos, pthread_mutex_t *forks, t_prog *prog)
{
    pthread_t monitor_thread;
    int i;

    // Create monitor thread
    if (pthread_create(&monitor_thread, NULL, &monitor, prog->philo) != 0)
        destroy_all("Error creating monitor thread", prog, forks, philos);

    // Create philosopher threads
    for (i = 0; i < philos->philos_num; i++)
    {
        if (pthread_create(&philos[i].thread, NULL, &philo_life, &philos[i]) != 0)
            destroy_all("Error creating philosopher thread", prog, forks, philos);
    }

    // Join monitor thread (when necessary)
    // You may not need to join the monitor thread if it runs indefinitely
    // Otherwise, join it before destroying resources
    // if (pthread_join(monitor_thread, NULL) != 0)
    //     destroy_all("Error joining monitor thread", prog, forks, philos);

    // Join philosopher threads
    for (i = 0; i < philos->philos_num; i++)
    {
        if (pthread_join(philos[i].thread, NULL) != 0)
            destroy_all("Error joining philosopher thread", prog, forks, philos);
    }

    // Join monitor thread before exiting if necessary
    if (pthread_join(monitor_thread, NULL) != 0)
        destroy_all("Error joining monitor thread", prog, forks, philos);

    return 0;
}
