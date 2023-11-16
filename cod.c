#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t delivery_sem;
int cash_on_delivery = 0;

void *delivery_thread(void *arg) {
    printf("Delivery thread: Package delivered.\n");
    sem_post(&delivery_sem);  // Signal that package is delivered
    pthread_exit(NULL);
}

void *payment_thread(void *arg) {
    sem_wait(&delivery_sem);  // Wait for package to be delivered
    printf("Payment thread: Collect cash on delivery.\n");
    
    // Simulate the possibility of not receiving cash on delivery
    if (rand() % 2 == 0) {
        cash_on_delivery = 1;  // Set cash_on_delivery flag
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t delivery_tid, payment_tid;
    sem_init(&delivery_sem, 0, 0);
    pthread_create(&delivery_tid, NULL, delivery_thread, NULL);
    pthread_create(&payment_tid, NULL, payment_thread, NULL);

    pthread_join(delivery_tid, NULL);
    pthread_join(payment_tid, NULL);

    sem_destroy(&delivery_sem);

    if (cash_on_delivery) {
        printf("Cash on delivery received. Transaction complete.\n");
    } else {
        printf("No cash on delivery received or payment failed.\n");
    }

    return 0;
}
