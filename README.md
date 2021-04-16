README
Program 4 Candy Factory
CS 570
Erik Morua, Nathan Azoulay

File Manifest:
      CandyFactory.h
      consumer.h
      io.h
      parse.h
      producer.h
      production.h
      resource.h
      CandyFactory.cpp
      consumer.cpp
      io.cpp
      main.cpp
      Parse.cpp
      producer.cpp
      makefile

Compile Instructions:
      make
      ./mizzo -f 5 -e 15 -E 35 -L 20

Operating Instructions:
      Required inputs:
           One or more Producer threads with a time delay, and one or more Consumer threads with time delays.
           the first two inputs will be the producers followed by a delay in ms for each one. The second two
           arguments will be two consumers each followed by a time delay.
      Output:
            A printed simulation/representation of a factory belt. The belt will run until 100 items
            have been created by producers, and 100 items have been consumed by both consumers. Using POSIX Threads
            , the producer threads will be cut once 100 items produced, and consumer threads will be finished once
            the belt is empty.
            
List/description of novel/significant design decisions:
      Utilized POSIX Threads and semaphores to help with critical sections.
      A Queue data structure used to simulate the belt made this task easier 
      than other methods explored.
     
List/description of known deficiencies or bugs:
      An off by one error caused by the beginning consumption in the consumer
      thread. Formatting is not as optimized as possible and can be difficult to read
      depending on the testing environment.
      
Lessons Learned:
      Learned in detail the importance of threads and semaphores and how to implement them
      to avoid deadlocks during execution. This gave us an opporunity to use c++ and utilize
      the class functions that are not available in C. Utilizing structures using threads, queues and objects
      gave experience that will be useful in other work moving forward.
