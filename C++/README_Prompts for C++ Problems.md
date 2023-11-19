
## Doodlebug Class

The goal for this Project is to create a simple two-dimensional predator-prey
simulation. In this simulation the prey are ants and the predators are doodlebugs.
These critters live in a world composed of a 20 × 20 grid of cells. Only one critter
may occupy a cell at a time. The grid is enclosed, so a critter is not allowed to move
off the edges of the world. Time is simulated in time steps. Each critter performs
some action every time step.


The ants behave according to the following model:

**Move**: Every time step, randomly try to move up, down, left, or right. If the neighboring cell in the
selected direction is occupied or would move the ant off the grid, then the ant stays in the
current cell.

**Breed**: If an ant survives for three time steps, then at the end of the time step (that is; after
moving) the ant will breed. This is simulated by creating a new ant in an adjacent (up, down, left,
or right) cell that is empty. If there is no empty cell available, then no breeding occurs. Once an
off-spring is produced, an ant cannot produce an offspring until three more time steps have
elapsed.


The doodlebugs behave according to the following model:

**Move**: Every time step, if there is an adjacent ant (up, down, left, or right), then the doodlebug
will move to that cell and eat the ant. Otherwise, the doodlebug moves according to the same
rules as the ant. Note that a doodlebug cannot eat other doodlebugs.

**Breed**: If a doodlebug survives for eight time steps, then at the end of the time step it will spawn
off a new doodlebug in the same manner as the ant.

**Starve**: If a doodlebug has not eaten an ant within the last three time steps, then at the end of
the third time step it will starve and die. The doodlebug should then be removed from the grid of
cells.


During one turn, all the doodlebugs should move before the ants do.

Write a program to implement this simulation and draw the world using ASCII characters of “o”
for an ant and “X” for a doodlebug or "-" for an empty space. Create a class named Organism
that encapsulates basic data common to both ants and doodlebugs. This class should have a
virtual function named move that is defined in the derived classes of Ant and Doodlebug. You
may need additional data structures to keep track of which critters have moved.

**Your task**: Initialize the world with 5 doodlebugs and 100 ants. After each time step, prompt the
user to press Enter to move to the next time step. You should see a cyclical pattern between the
population of predators and prey, although random perturbations may lead to the elimination of
one or both species. Please submit a single .cpp; do NOT separate this into multiple .h files.
The .cpp should contain all classes and structures needed so that it can execute when running
the main function.

An example of a program timestep output is given below.

<img width="310" alt="image" src="https://github.com/ZijiePang/zijie_pang_portfolio/assets/60828911/f6f1fd26-ffef-4adb-abf3-b9b26068570b">



## Linked Lists & File Reading
Imagine a group of friends went out to dinner together. When the bill comes they all give
different amounts to contribute to the total, but after wish to balance everything out equally so
that each person pays the same amount. Knowing how much each person is supposed to pay is
simple enough, just add up all the amounts paid and divide by the number of people; but that
doesn’t tell anyone how to go about distributing the payments, who should give what amount to
whom?

Write a program that will print out a step by step list of instructions of how to reimburse
everyone given the name of the person and amount of money they paid. This program should
prompt the user to enter a file name associated with the info, which will then be read in. All
information from the external file should be read into a linked list. An example is provided below:

**Input**: 

<img width="304" alt="image" src="https://github.com/ZijiePang/zijie_pang_portfolio/assets/60828911/029b9bfe-f837-46b8-ae4f-98eac43d97e3">


**Output**:

<img width="451" alt="image" src="https://github.com/ZijiePang/zijie_pang_portfolio/assets/60828911/09b9a8fc-d15e-4171-83e7-dc42d7ca5a05">




**A few things to note:**

- Amounts and names are separated by a space (“ “), not tab.
- You should design your own linked list and node classes for this. The node classes
would essentially be representing people, and you can choose whatever attributes you
like for it, but might be helpful to store name and amount paid (from the input file), as
well amount owed, which can be initialized to 0 and then altered later upon calculating
the balances
- You must be able to read in full names, accounting for both 2 and 3 part names
- The information should be read into a linked list, but after that you can handle it in
whatever format you find convenient
- You can assume the data file will have at least 2 entries with both names and amounts
on it; we will not try to break it upon testing with empty files or bad formatting
- The program should not alter anything in the input file, you simply are reading it in


## Red-Black Tree
This project includes code for insertions in a Red-Black tree.
