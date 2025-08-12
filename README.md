# Philosophers – Dining Philosophers Problem 🧠🍝

The **Philosophers** project is an implementation of the classic problem **Dining Philosophers**.  
It focuses on **multithreading**, **mutex synchronization**, and **avoiding race conditions** in C. 

## 👀 Overview

- One or more philosophers sit at a round table.  
- There is a large bowl of spaghetti in the middle of the table.  
- The philosophers take turns **eating**, **thinking**, and **sleeping**.  
  - While eating, they are not thinking or sleeping.  
  - While thinking, they are not eating or sleeping.  
  - While sleeping, they are not eating or thinking.  
- There are as many forks as philosophers on the table.  
- Eating spaghetti with just one fork is impractical, so a philosopher must pick up **both the fork to their right and the fork to their left** before eating.  
- After finishing eating, the philosopher puts their forks back and starts sleeping. Once awake, they start thinking again.  
- The simulation stops when a philosopher dies of starvation (fails to eat in time).


---

## 📜 Program Arguments

The program takes the following arguments:

1. **`number_of_philosophers`** – Number of philosophers and also the number of forks.  
2. **`time_to_die`** *(milliseconds)* – If a philosopher has not started eating within this time since their last meal (or the simulation start), they die.  
3. **`time_to_eat`** *(milliseconds)* – Time it takes for a philosopher to eat. They must hold two forks during this time.  
4. **`time_to_sleep`** *(milliseconds)* – Time a philosopher spends sleeping.  
5. **`number_of_times_each_philosopher_must_eat`** *(optional)* – If all philosophers have eaten at least this many times, the simulation ends.  

---

## 🛠 Implementation Details

- Each philosopher is represented by a **separate thread**.  
- There is **one fork between each pair** of philosophers:
  - A philosopher has one fork on their left and one on their right.  
  - If there is only **one philosopher**, they have access to only one fork.  
- To prevent multiple philosophers from picking up the same fork simultaneously, **each fork’s state is protected with a mutex**.

---

## 📏 Output Format

Any state change of a philosopher is printed in the following format: 
- timestamp_in_ms X has taken a fork 🍴
- timestamp_in_ms X is eating 🍝
- timestamp_in_ms X is sleeping 😪💤
- timestamp_in_ms X is thinking 🤔💭
- timestamp_in_ms X died 💀🪦

Where:
- `timestamp_in_ms` – Time since the start of the simulation in milliseconds.  
- `X` – Philosopher’s ID (starting from 1).

---
