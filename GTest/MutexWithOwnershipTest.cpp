//
// Created by pbeerken on 7/27/17.
//

#include <gtest/gtest.h>
#include <mutex>
#include <future>
#include "../MutexWithOwnersip.h"

TEST(MutexWithOwnershiptTest, SameThread)
{
    MutexWithOwnership mutexWOS;
    std::lock_guard<MutexWithOwnership> guard(mutexWOS);
    EXPECT_TRUE (mutexWOS.owned());
}

TEST (MutexWithOwnershiptTest, NoThread)
{
    MutexWithOwnership mutexWOS;
    EXPECT_FALSE (mutexWOS.owned());

    {
        std::lock_guard<MutexWithOwnership> guard(mutexWOS);
        EXPECT_TRUE (mutexWOS.owned());
    }
    EXPECT_FALSE (mutexWOS.owned());
}

TEST (MutexWithOwnershiptTest, DifferentThreads)
{
    MutexWithOwnership mutexWOS;
    std::promise<void> promiseSetWhenMutexIsheld;
    std::promise<void> promiseSetWhenTestIsDone;

    std::thread t([&]() {
        std::lock_guard<MutexWithOwnership> guard(mutexWOS);
        //let the test know that another thread has taken the mutex
        promiseSetWhenMutexIsheld.set_value();
        EXPECT_TRUE (mutexWOS.owned());

        //wait till the test is done
        promiseSetWhenTestIsDone.get_future().wait();
    });



    //wait till the other thread has taken the mutex.
    promiseSetWhenMutexIsheld.get_future().wait();

    EXPECT_FALSE (mutexWOS.owned());
    promiseSetWhenTestIsDone.set_value();
    t.join(); //wait for the thread to really die

}