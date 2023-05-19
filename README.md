# The Dining Philosophers Problem


Description

This program is a multithreaded simulation based on the classic concurrency problem known as the "Dining Philosophers". It depicts philosophers who spend their lives thinking, eating, and sleeping. The simulation takes into account the challenge that arises due to the requirement of the philosophers needing two forks to eat and the fact that they share these forks with their neighbors.

Features

The program:

Is written in C and uses mutexes and threads to ensure there are no data races.
Takes command-line arguments to customize the simulation (number of philosophers, time parameters, etc.).
Allows the user to define the number of times each philosopher must eat before ending the simulation.
Installation and Usage

## Installation

1. Clone the repository:
    ```bash
    git clone git@github.com:maxstocklin/philosophers.git philosophers
    ```

2. Navigate to the cloned repository:
    ```bash
    cd philosophers
    ```

3. Compile the program using the provided Makefile:
    ```bash
    make
    ```
## Usage

### Program Parameters

The program accepts the following command-line arguments:

- **number_of_philosophers**: The number of philosophers and also the number of forks.
- **time_to_die** (in milliseconds): If a philosopher doesn’t start eating time_to_die milliseconds after the start of their last meal or the beginning of the simulation, they die.
- **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- **time_to_sleep** (in milliseconds): The time a philosopher will spend sleeping.
- **number_of_times_each_philosopher_must_eat** (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

Here is an example:

    ./philosophers 5 8000 2000 2000 7

## Contributing

Philosophers is an open-source project, and contributions are always welcome! If you have any bug reports, feature requests, or questions, please open an issue on this GitHub repository.

