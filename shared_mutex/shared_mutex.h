/**
 * @file shared_mutex.h
 * @brief 封装读写锁
 * @author chxuan, 787280310@qq.com
 * @version 1.0.0
 * @date 2018-01-05
 */
#pragma once

#include <pthread.h>

class shared_mutex
{
public:
    shared_mutex()
    {
        pthread_rwlock_init(&mutex_, nullptr);
    }

    ~shared_mutex()
    {
        pthread_rwlock_destroy(&mutex_);
    }

    void lock_read()
    {
        pthread_rwlock_rdlock(&mutex_);
    }

    void lock_write()
    {
        pthread_rwlock_wrlock(&mutex_);
    }

    void unlock()
    {
        pthread_rwlock_unlock(&mutex_);
    }

private:
    pthread_rwlock_t mutex_;
};

class lock_shared
{
public:
    lock_shared(shared_mutex& mt, bool shared = false) 
        : mutex_(mt)
    { 
        if (shared)
        {
            mutex_.lock_read();
        }
        else
        {
            mutex_.lock_write();
        }
    }

    ~lock_shared()
    {
        mutex_.unlock();
    }

private:
    shared_mutex& mutex_;
};
