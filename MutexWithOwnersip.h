//
// Created by pbeerken on 7/27/17.
//

#ifndef LIBUTILS_MUTEXWITHOWNERSIP_H
#define LIBUTILS_MUTEXWITHOWNERSIP_H

#include <thread>

class MutexWithOwnership :
        public std::mutex
{
public:
#ifndef NDEBUG

    void lock()
    {
        std::mutex::lock();
        owningThreadId_ = std::this_thread::get_id();
    }

    void unlock()
    {
        owningThreadId_ = std::thread::id();
        std::mutex::unlock();
    }

    bool owned() const
    {
        return owningThreadId_ == std::this_thread::get_id();
    }

private:

    std::thread::id owningThreadId_;
#endif // #ifndef NDEBUG
};

#endif //LIBUTILS_MUTEXWITHOWNERSIP_H
