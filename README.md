The purpose of this assignment is to design and implement an interrupt driven program that allows a user to interact with a simple monitor. The program is to run on the Texas Instruments Tiva Microcontroller running an ARM Cortex M4 CPU and interaction will between the user and the monitor will be accomplished using puTTY.
The monitor is to allow the user to enter commands to set the time-of-day, query the time-of-day and run a stopwatch. A cursor will be used to indicate the next input character position and the screen must scroll when it reaches the bottom.
The assignment was to be completed in either C or C++. I chose to use C++ to take advantage of some of its built-in libraries and object-oriented approach though some C-style code was used as well – mainly in using provided code samples for UART and Systick.
To simplify both design and testing the program was written in modules and then combined to work together. Breaking the project into ‘bite-sized’ pieces rather than trying to figure out how everything would interact right out of the gate made it much easier to progress through the assignment. This approach also allows me to import specific modules from this assignment into another with minimal effort should the need arise in the future.

Upon completion of the assignment a user should be able to type commands and have the monitor react accordingly. Below is a list of the supported commands and their required behavior:

1 – ‘TIME’
	- Display current time-of-day in the format HH:MM:SS.t.

2 – ‘SET HH:MM:SS’
	- Sets the current time-of-day to the value specified in the input string.

3 – ‘Go’
	- Starts the stopwatch from 00:00:00:0. Upon receiving any input while the stopwatch is running it should stop and its value remain on the screen. Time-of-day must continue updating even though not displayed while stopwatch is running.

4 – *ANYTHING ELSE*
- Displays diagnostic error message.

Through extensive testing the monitor submitted (see Appendix A: Code) has been verified fully functional and an overall success. The assignment goals have been met and then some as more useful diagnostic messages and string printing via UART was implemented to improve