Eric Markstein & Aaron Squire

How to compile and run the code: 
The makefile should compile everything necessary with the simple “make” command. 
After the executable is created, use the following command to run the simulation:

./Sim <input.txt> <seed>

*input.txt is the configuration file for variables
**seed is the seed for the random number generator

Errors that we are aware of:
When a vehicle is turning right and the light is yellow, it will not 
enter the intersection unless it will fully make it out PLUS one extra square
in between the vehicle and the intersection. Turning right takes one less time
tick than going straight to fully exit the intersection, and we did not
implement this difference. 

Design Decisions:
We created a file reader program (FileReader.cpp) and a simulation (Sim.cpp) and 
modified the given VehicleBase.cpp. The file reader reads the input file and parses 
the contents into key-value pairs which are assigned to variables in sim.cpp. 
We have variables and methods declared before the main which are then defined 
after the main. In the main, after the variables are assigned, it enters a for loop
for the max_time. In this loop, the first section controls the stop lights. Then, we
used 2 methods, one for north/south and the other for east/west. In these methods
there are calls to green_light, yellow_light, or red_light which move the vehicles up in
the road depending on what color the light is. These three methods use pass-
by-reference so we can control the vehicles in each of the 4 lanes without needing 4
different methods. Originally, we had a separate method for north, east, south, and west
for each of green_light, yellow_light, and red_light, and although the code worked perfectly,
it took up an excessive amount of lines and we knew we could do it in a more concise way.
After the vehicles are moved up, the add_vehicles method is called. We used 4 “head” road
vectors that we would place the vehicles in before they entered the visual simulation. 
After the vehicles were added, the animator was updated and the loop continued. 

Testing: 
Sim: 
We tested by changing the input file to watch what happens. For the probabilities/proportions, 
we tested all at 0, 1 and a number in between 0 and 1. We did a variety of these tests to cover 
as many unique scenarios as we could think of. We ran through the simulation for a reasonable 
number of ticks until we were confident there were no errors given any input file. 
FileReader:
We tested the file reader with many input files. If the file name is invalid, it will throw a 
runtime error. We tested with white space before the input variable, after the input variable 
but before the colon, after the colon and before the number, and after the number. We also tested 
with empty lines before any lines, between lines with text, and after all the lines. We also 
tested with necessary input variables missing or misspelled, which will both throw a run time 
error if problematic. Because the FileReader required different inputs for every test, we don’t 
have the original FileReader test code, which is why none exists in the tar file.
VehicleBase:
We tested the move constructor, move assignment operator, and other methods that we added to 
VehicleBase.cpp to make sure the expected behavior occurred. Our tests are in the folder.
