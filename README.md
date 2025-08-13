# Philosophers

This project is a classic synchronization problem, also known as the dining philosophers problem. The goal is to learn about threads, mutexes, and how to handle concurrent processes without deadlocks or data races.

## The Problem

A number of philosophers are sitting around a circular table. There is a fork between each pair of adjacent philosophers. A philosopher can be in one of three states: thinking, hungry, or eating.

-   When a philosopher is thinking, they do not interact with their colleagues.
-   When a philosopher gets hungry, they try to pick up the two forks closest to them (the one on their left and the one on their right).
-   A philosopher can only eat if they have both forks.
-   After eating, a philosopher puts down both forks and starts thinking again.

The challenge is to design a solution that allows the philosophers to eat without causing a deadlock (where all philosophers are holding one fork and waiting for the other) or starvation (where a philosopher is perpetually denied access to forks).

## How to Compile

To compile the project, run the following command:

```bash
make
```

This will create an executable file named `philo`.

## How to Run

The program takes the following arguments:

-   `number_of_philosophers`: The number of philosophers (and forks).
-   `time_to_die`: The time in milliseconds a philosopher has to eat before they die.
-   `time_to_eat`: The time in milliseconds it takes for a philosopher to eat.
-   `time_to_sleep`: The time in milliseconds a philosopher spends sleeping.
-   `[number_of_times_each_philosopher_must_eat]`: (Optional) The number of times each philosopher must eat before the simulation stops. If not specified, the simulation runs until a philosopher dies.

Example:

```bash
./philo 5 800 200 200
```

## Contact

-   **42 Login:** ihhadjal
-   **Email:** ihhadjal@student.42nice.fr
