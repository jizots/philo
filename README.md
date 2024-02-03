# Project README: Philosophers
## Overview
The Philosophers project is a simulation of philosophers who eat, think, and sleep.  
The main focus is on learning threading in processes and discovering mutexes.  
Philosophers are implemented as threads (or processes in the bonus part), each requiring two forks to eat from a shared table of spaghetti.  
  
## Features
Simulates philosophers' actions (eating, thinking, sleeping).  
Implements thread management and synchronization using mutexes.  
Bonus part involves process implementation and semaphore usage.  
  
## Usage
To use the program:  
  
Compile with the provided Makefile.  
Execute the program with specified arguments: number of philosophers, time to die, time to eat, time to sleep, and optionally, the number of times each philosopher must eat.  
Like...  
```
git clone git@github.com:jizots/philo.git
```  
```
cd philo
```  
```
make
```  
```
./philo 5 810 200 200
```  
