# Operating Systems Project

This repository contains several C++ programs that implement different algorithms and techniques used in operating systems. Each file represents a specific aspect of memory management and CPU scheduling, ranging from partition schemes to complex scheduling algorithms. These programs were developed for academic learning purposes as part of the Operating Systems course at IPN ESIME Culhuacán.

## Description

This project is a collection of scripts that emulate the internal behavior of operating systems, including implementations of the mutual exclusion algorithm "semaphore" as well as CPU scheduling algorithms such as FCFS, SJF, Priority Scheduling, and Round Robin. These algorithms are commonly found in modern multitasking operating systems.

## Files Overview

### 1. Partition Scheme (`1.- Esquema de particiones.cpp`)
This program simulates different memory partitioning schemes, including first-fit, best-fit, and worst-fit algorithms. It manages memory allocation for tasks and displays the memory table.

### 2. Simple Paging (`2.- Paginación simple.cpp`)
This file implements a simple paging system, managing memory through page tables and handling basic memory allocation. It also simulates the translation of logical addresses to physical addresses.

### 3. Demand Paging (`3.- Paginacion por demanda (MMT, JT y PMT).cpp`)
This program simulates demand paging, including the management of memory with page tables (MMT, JT, and PMT) and implementing LRU or FIFO page replacement strategies.

### 4. Swapping with FIFO and LRU (`4.- Swapping FIFO y LRU.cpp`)
This file implements a swapping mechanism using both FIFO and LRU page replacement algorithms. It simulates task execution and memory management under different swapping conditions.

### 5. CPU Schedulers (`5.- Planificadores de CPU (FCFS, SJF, Prioridades, Round Robin).cpp`)
This program simulates various CPU scheduling algorithms, including First-Come, First-Serve (FCFS), Shortest Job First (SJF), Priority Scheduling, and Round Robin. It allows for the comparison of these scheduling methods.

### 6. Final Project (`6.- Proyecto FInal.cpp`)
The final project combines multiple aspects of memory management and CPU scheduling into a comprehensive simulation. It showcases the interaction between different system components and their performance under various conditions.

## How to Use

To use the programs in this repository, follow these steps:

1. **Download the Files:** Clone the repository to your local machine using the following command:

   ```bash
   git clone <repository_url>
   ```

   Replace `<repository_url>` with the actual URL of your GitHub repository.

2. **Navigate to the Directory:** Change your directory to the folder containing the files:

   ```bash
   cd <repository_folder>
   ```

   Replace `<repository_folder>` with the name of the cloned repository folder.

3. **Compilation:**
   Each C++ file can be compiled using a C++ compiler like `g++`. For each file, use the following command structure:

   ```bash
   g++ -o <output_filename> "<input_filename>"
   ```

   - For example, to compile the Partition Scheme program, run:

     ```bash
     g++ -o partition_scheme "1.- Esquema de particiones.cpp"
     ```

   - Similarly, compile the other programs by replacing `<input_filename>` with the appropriate file name, such as `"2.- Paginación simple.cpp"`, `"3.- Paginacion por demanda (MMT, JT y PMT).cpp"`, etc.

4. **Execution:**
   After compilation, run the executable generated in the previous step. For example:

   ```bash
   ./partition_scheme
   ```

   Replace `partition_scheme` with the name of the compiled executable for other programs.

5. **User Interaction:**
   Each program will prompt you to provide various inputs based on the simulation, such as:
   - The number of tasks.
   - Memory size.
   - The type of scheduling algorithm to be used.

6. **Output:**
   The programs will display the results of the simulations, including memory tables, task schedules, CPU cycle counts, and other relevant data.

## Purpose

These programs were created with academic intentions, aimed at enhancing the understanding of fundamental concepts in memory management and CPU scheduling within the context of operating systems. They serve as practical tools for learning how different algorithms perform and how they impact system efficiency.

## Credits

- **Final Project (`6.- Proyecto FInal.cpp`)**: This comprehensive project was developed by **Edgar Diego Piña Vargas** and **Víctor Alfonso Sandoval Núñez**.
- **All Other Programs**: Developed solely by **Edgar Diego Piña Vargas**.

This repository is a part of the academic work submitted for the Operating Systems course at **IPN ESIME Culhuacán**.
