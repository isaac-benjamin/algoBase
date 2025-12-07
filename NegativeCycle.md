# Negative Weight Cycle

This algorithm just runs the belman ford algorithm except the main loop runs one extra time (n vs  n-1). Whether there was a change to the shortest distance is recorded in a variable. If there are no changes during an iteration, the loop ends early. Once out of the loop there is a check to see if iteration number equals vert number and whether there was a change made in the last iteration, if both are true then there is a negative weight cycle.

## Pseudocode and running time

This algorithm was discussed in class.
Running time is O(m*n)