/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubourge <hubourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:12:42 by hubourge          #+#    #+#             */
/*   Updated: 2025/01/23 15:03:18 by hubourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define ALLOCATION_SIZE 128
#define NUM_THREADS 5

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
	
	pthread_mutex_lock(&g_mutex);
    ft_printf("Thread %d: démarré\n", thread_id);
	pthread_mutex_unlock(&g_mutex);

    char* ptr = malloc(ALLOCATION_SIZE);
    if (!ptr)
	{
		pthread_mutex_lock(&g_mutex);
        ft_printf("Thread %d: malloc a échoué\n", thread_id);
		pthread_mutex_unlock(&g_mutex);
        return (NULL); // removed pthread_exit
    }
	
	pthread_mutex_lock(&g_mutex);
    ft_printf("Thread %d: mémoire allouée à l'adresse %p\n", thread_id, (void*)ptr);
	pthread_mutex_unlock(&g_mutex);

    // Build the string manually
    const char* prefix = "Thread ";
    int idx = 0;
    for (int i = 0; prefix[i] != '\0' && idx < ALLOCATION_SIZE - 1; i++) {
        ptr[idx++] = prefix[i];
    }
	
    // Convert thread_id to characters
    {
        int temp = thread_id, revIdx = 0;
        char revBuf[16]; // enough for digits
        if (temp == 0)
            revBuf[revIdx++] = '0';
        else 
		{
            while (temp > 0 && revIdx < 15) 
			{
                revBuf[revIdx++] = (char)('0' + (temp % 10));
                temp /= 10;
            }
        }
        // Copy reversed digits
        while (revIdx > 0 && idx < ALLOCATION_SIZE - 1) {
            ptr[idx++] = revBuf[--revIdx];
        }
    }
	
    const char* suffix = " test";
    for (int i = 0; suffix[i] != '\0' && idx < ALLOCATION_SIZE - 1; i++)
        ptr[idx++] = suffix[i];
    ptr[idx] = '\0';
	
	pthread_mutex_lock(&g_mutex);
    ft_printf("Thread %d: mémoire initialisée avec contenu : %s\n", thread_id, ptr);
	ft_printf("Thread %d: ptr = %p\n", thread_id, ptr);
	pthread_mutex_unlock(&g_mutex);
	
    free(ptr);
	
	pthread_mutex_lock(&g_mutex);
    ft_printf("Thread %d: mémoire libérée\n", thread_id);
	pthread_mutex_unlock(&g_mutex);

    return (NULL);
}

void test_thread()
{
	ft_printf("--> TEST : thread\n");
	
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
	{
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0)
		{
            ft_printf("Erreur lors de la création du thread %d\n", i);
            return;
        }
    }
	for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
			
    ft_printf("Tous les threads ont terminé.\n");

    return;
}
