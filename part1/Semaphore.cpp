#include "Semaphore.hpp"

Semaphore::Semaphore() : queue_size(0) {
    init_semaphore();
}

Semaphore::Semaphore(unsigned val) : queue_size(val) {
    init_semaphore();
}

Semaphore::~Semaphore() {
    pthread_mutex_destroy(&this->lock);
    pthread_cond_destroy(&this->cond);

}
void Semaphore::down() {
    pthread_mutex_lock(&this->lock);

    while (this->queue_size == 0) {
        pthread_cond_wait(&this->cond, &this->lock);
    }
    this->queue_size--;

    pthread_mutex_unlock(&lock);
}

void Semaphore::up() {
    pthread_mutex_lock(&this->lock);

    this->queue_size++;
    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&lock);
}

void Semaphore::init_semaphore() {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);

    pthread_mutex_t error_check_mutex;
    pthread_mutex_init(&error_check_mutex, &attr);
    this->lock = error_check_mutex;

    pthread_mutexattr_destroy(&attr);

    pthread_cond_init(&this->cond, NULL);
}