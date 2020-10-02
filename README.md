# Semapphore-Counting-Semaphore-Example
Its work on Linux also You can run it via Cyawin64 terminal on Windows
Semaphore was proposed by Dijkstra in 1965 which is a very significant technique to manage concurrent processes by using a simple integer value, which is known as a semaphore. Semaphore is simply a variable which is non-negative and shared between threads. This variable is used to solve the critical section problem and to achieve process synchronization in the multiprocessing environment.

Semaphores are of two types:

Binary Semaphore – This is also known as mutex lock. It can have only two values – 0 and 1. Its value is initialized to 1. It is used to implement the solution of critical section problem with multiple processes.
Counting Semaphore – Its value can range over an unrestricted domain. It is used to control access to a resource that has multiple instances.