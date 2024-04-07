#include "philo.h"

int philo_dead(t_philo *philo)
{
    pthread_mutex_lock(philo->meal_lock);
    if (get_time() - philo->last_meal >= philo->phil_death_time && !philo->eating)
        return ((pthread_mutex_unlock(philo->meal_lock)), 1);
    pthread_mutex_unlock(philo->meal_lock);
    return (0);
}

int check_death(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos->philos_num)
    {
        if (philo_dead(&philos[i]))
        {
            print(&philos[i], "died");
            pthread_mutex_lock(philos->dead_lock);
            *philos->dead = 1;
            pthread_mutex_unlock(philos->dead_lock);
            return (1);
        }
        i++;
    }
    return (0);
}