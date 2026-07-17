README.md

Embedded Sensor Data Processor

A C program that reads and analyses binary ADC sensor data, producing statistical summaries, fault detection results and a formatted output report.

Features

Reads ADC sensor data from a binary file.
Converts raw ADC values into voltages and calculates per-channel statistics.
Detects overvoltage, undervoltage and sensor faults, checks sequence integrity, and writes the results to results.txt.

Build from Source

Using CLion

Open the project folder in CLion.
Allow CMake to load the project.
Build the project using Build → Build Project (or Ctrl + F9).
Run the programmingFE configuration (Shift + F10).

Using GCC

Compile the project with:

gcc -std=c99 -Wall -Wextra -o programmingFE main.c adc.c io.c stats.c -lm

Run the program:

Windows

programmingFE.exe

Linux/macOS

./programmingFE

Ensure that adc_sensor_log.bin is located in the same directory as the executable before running the program.