/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 23:54:48 by yismaili          #+#    #+#             */
/*   Updated: 2022/04/16 23:54:55 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
// int x = 0;
// pthread_mutex_t mutex;
// void* routine()
// {
//     int i = 0;
//     while (i < 1000000)
//     {
//         pthread_mutex_lock(&mutex);
//          x++;
//         pthread_mutex_unlock(&mutex);
//          i++;
//     }
    
//     // printf("Test from threads\n");
//      //sleep(2);
//     // printf("Ending thread\n");
//      //printf("process id %d\n", getpid());
// }
// int main (int argc, char* argv[])
// {
//     pthread_t   th[4];
//     int i = 0;
//     pthread_mutex_init(&mutex, NULL);
//     while (i < 4)
//     {
//         pthread_create(&th[i], NULL, &routine, NULL);
//         pthread_join(th[i], NULL);
//         i++;
//     }
//      pthread_mutex_destroy(&mutex);
//      printf("value of x : %d\n", x);
//     return 0;
// }



int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg) {
    sleep(1);
    int index = *(int*)arg;
    int i = 0;
    int sum = 0;
    // while(i < 5)
    // {
    //     sum += primes[index + i];
    //     i++;
    // }
    printf("%d ", primes[index]);
    free(arg);
}

int main(int argc, char* argv[]) {
    pthread_t th[10];
    int i = 0;
    while (i < 10) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to created thread");
        }
        i++;
    } 
    i = 0;
    while (i < 10) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
        i++;
    }
    
    return 0;
}