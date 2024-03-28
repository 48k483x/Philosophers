#include "philo.h"

bool is_dead(t_philo *philo)
{
    printf("start time: %ld\n", get_time() - philo->start_time);
    printf("last meal: %ld\n",philo->last_meal);
    if (philo->eating)
    {
        if (philo->phil_eat_time > philo->phil_death_time)
        {
            usleep(philo->phil_death_time * 1000);
            printf("%ld %d died\n", get_time() - philo->start_time, philo->id);
            return (false);
        }
        else if ((get_time() - philo->start_time) - philo->last_meal > philo->phil_death_time)
        {
            printf("%ld %d died\n", get_time() - philo->start_time, philo->id);
            return (false);
        }
    }

    return (true);
}

bool eating(t_philo *philo)
{
    philo->eating = 1;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->r_fork);
        printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
        pthread_mutex_lock(philo->l_fork);
        if (philo->philos_num == 1)
            pthread_mutex_unlock(philo->r_fork);
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
        if (philo->philos_num == 1)
        {
            usleep(philo->phil_eat_time * 1000);
            is_dead(philo);
            pthread_mutex_unlock(philo->r_fork);
        }
        pthread_mutex_lock(philo->r_fork);
    }
    printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
    printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
    if (!is_dead(philo))
        return (false);
    usleep(philo->phil_eat_time * 1000);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    philo->last_meal = get_time() - philo->start_time;
    if (philo->eat_times != -1 && philo->meals_eaten == philo->eat_times )
        philo->eat_times = 0;
    return (true );
}

void sleeping(t_philo *philo)
{
    printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id);
    philo->eating = 0;
    usleep(philo->phil_sleep_time * 1000);
}

void thinking(t_philo *philo)
{
    printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id);
}

void *philo_life(void *philo)
{
    t_philo *p = (t_philo *)philo;

    while (1 && eating(p))
    {
        eating(p);
        sleeping(p);
        thinking(p);
        if (p->eat_times == 0)
            break;
    }
    return (NULL);
}