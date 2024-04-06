#include "philo.h"

bool is_dead(t_philo *philo)
{
    if (philo->philos_num == 1)
    {
            usleep(philo->phil_death_time * 1000);
            print(philo, "died");
            return (true);
    }
    if (philo->eating)
    {
        if (philo->phil_eat_time > philo->phil_death_time)
        {
            usleep(philo->phil_death_time * 1000);
            print(philo, "died");
            return (true);
        }
        else if ((get_time() - philo->start_time) - philo->last_meal > philo->phil_death_time)
        {
            usleep(philo->phil_death_time * 1000);
            print(philo, "died");
            return (true);
        }
    }

    return (false);
}

int eating(t_philo *philo)
{
    philo->eating = 1;
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->r_fork);
        print(philo, "has taken a fork");
        pthread_mutex_lock(philo->l_fork);
        if (philo->philos_num == 1)
            pthread_mutex_unlock(philo->r_fork);
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        print(philo, "has taken a fork");
        if (philo->philos_num == 1)
        {
            is_dead(philo);
            pthread_mutex_unlock(philo->r_fork);
            return (0);
        }
        pthread_mutex_lock(philo->r_fork);
    }
    print(philo, "has taken a fork");
    print(philo, "is eating");
    usleep(philo->phil_eat_time * 1000);
    philo->meals_eaten++;
    philo->last_meal = get_time() - philo->start_time;
    if (is_dead(philo))
	{
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        return (0);
	}
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    if (philo->eat_times != -1 && philo->meals_eaten == philo->eat_times )
        philo->eat_times = 0;
    return (1);
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

    while (1)
    {
        if (!eating(p))
        {
            detach_all(p);
            break ;
        }
        sleeping(p);
        thinking(p);
        if (p->eat_times == 0)
            break;
    }
    return (NULL);
}