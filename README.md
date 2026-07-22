# pic32-timer-sound-generator
Sound generation project developed in MPIDE on a PIC32-based development board, using timer registers and counters to control sound frequency, duration and pause intervals.

# PIC32 Timer-Based Sound Generator

A university embedded systems project developed in MPLAB X using a PIC32-based development board.

## About the project

The project generates a sound sequence with an increasing number of beeps.

The frequency, duration and pause between sounds are controlled using the PIC32 Timer registers and software counters.

The project involved:

- configuring the PIC32 microcontroller;
- configuring and using hardware timers;
- generating sound signals with controlled frequency;
- controlling the duration of each beep;
- controlling the pause between consecutive beeps;
- increasing the number of generated beeps;
- testing the application on the development board.

## Technologies used

- PIC32 microcontroller
- MPLAB X IDE
- Embedded C
- Hardware timers
- Counters
- Embedded systems
- Hardware testing

## Project structure

- `proiect.c` – main source code;
- `Pic32Mx3Conf.h` – microcontroller and board configuration;
- `nbproject/` – MPLAB X project configuration;
- `Makefile` – project build configuration;
- `.gitignore` – excludes generated and compiled files.

## Project requirement

Generate a sound sequence with an increasing number of beeps. The sound frequency, duration and pause interval must be determined using Timer register values and counters.

## Notes

The folders generated automatically during compilation, such as `build`, `dist`, `debug` and `.generated_files`, are excluded from the repository.

## Author

**Flaviu Mariș**  
ETTI graduate – Technical University of Cluj-Napoca
