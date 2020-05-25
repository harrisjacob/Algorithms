# Cycle Detection

## Description
Cycle Detection involves finding loops or redundancies in a sequence of data.  Cycle detection algorithms typically output where a cycle begins and the length of the cycle, but could alternatively provide information such as elements of the cycle.

For an in depth description and further information on cycle detection see the **Sources** section.


## Purpose
The purpose of this project was to experiment with the implementation of basic graphs and known cycle detection algorithms.


## Algorithms
* [Robert Floyd's Tortoise and Hare Algorithm](https://en.wikipedia.org/wiki/Cycle_detection#Floyd's_Tortoise_and_Hare "Floyd's Tortoise and Hare Algorithm")
* [Richard Brent's Algorithm](https://en.wikipedia.org/wiki/Cycle_detection#Brent's_algorithm "Brent's Algorithm")

## Algorithmic Analysis

|      | Time Complexity | Space Complexity     |
| :----:       |    :----:   |      :---: |
| Build Graph  |    O(n<sup>2</sup>)     | O(n)      |
| Floyd's Algorithm     | O(n)       | O(1)  |
| Brent's Algorithm  |    O(n)     | O(1)      |

## Sources
Wikipedia: [Cycle Detection](https://en.wikipedia.org/wiki/Cycle_detection "Cycle Detection")


## Use
The cycle detection program can be run by first compiling **findCycle.cpp** using the provided **Makefile**, then running `./findCycle -f [node data]` where [node data] is the properly formatted datafile (see **Datafile Information**) specifed by the -f flag.  If the data does not include a repeated value (i.e. all values are unique), the `-l[index]` flag and value is used to set the next pointer of the final value of data to be the [index] node of the graph thus creating a loop to a specified location. (Note: There should be no space between the -l flag and [index] as in "-l5" )

This feature is mainly used for algorithm testing purposes as specifying these values makes the output of the program trivial. Failing to specify a -l[index] value when using unique data will lead to unpredictable results.

For best use, specify a properly formatted datafile that contains at least one redundant integer.

The algorithm used to detect cycles can be specified using `-a [algorithm]` where algorithm is either "floyd" or "brent" (case insensitive). If the -a flag is not used, the program will default to using Floyd's algorithm.


## Datafile Information
* Datafiles should contain more than one value
* Entries in the datafile should be newline delimited
* Once a redudant value is read in, no more values will be read, and the loop will be simulated
* Datafile entries should be integers.  The Node class handles templated data storage, but the **findCycle** program only demonstrates the detection using integers.


## Example Build
*Datafile (ignoring newline characters): 0 1 2 3 4 5 6 3 4 5 6 3 ...*

This will create a graph where the above values appear as the data for each node. Each node points to the the node of the value to its right (e.g. 0 -> 1).  Because the second 3 is redudant, the node with value 6 will point to the node with value 3 (previously created), and every value after the 6 will not be read in (their contribution is included in the created loop).