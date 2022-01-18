# Philosophers (January 2022)
I’ve never thought philosophy would be so deadly.<br>
This is my solution for the philosophers project of 42 school.<br>
This is part of common core.<br>
<img src="readme_additions/philosophers_example.png" width="200"/><br>
<!-- <img src="readme_additions/result.png" width="200"/><br> -->

##Introduction
<img src="readme_additions/introduction.png"><br>
This is taken from the [subject.pdf](readme_additions/en.subject.pdf).<br>
To run the simulation a few variables are needed:<br>
1. number_of_philosophers: is the number of philosophers and also the number of forks.<br>
2. time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’milliseconds after starting their last meal or the beginning of the simulation,it dies.<br>
3. time_to_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time they will need to keep the two forks.<br>
4. time_to_sleep: is in milliseconds and is the time the philosopher will spend sleeping.<br>
5. number_of_times_each_philosopher_must_eat: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.<br>
