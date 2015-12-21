# Computer Science Large Practical

# Note on Testing/Running

you will need to run a `make clean` between running tests and running the program (or vise-versa).
This is because the (intermediate) object files compile to a slightly different version as they have different flags set.

I have done this so that the event  stream isn't printed in testing. I'm generally doing unit testing, and don't want to see the event stream while trying to write/debug unit-tests.

running in done through calling ./cslp [input-file]
if run without an argument, it will run _./test/fs/input.in_, otherwise it will run the input file. 

the ./cslp file is actually a bash file that calls the executable living in _./bin/_.

# Included Libraries
## CuTest
http://cutest.sourceforge.net/
The testing library has been included from the following place:
I have embeded it into my project, as this makes building easier.

# Implementation Details

## Config Parsing
I have set default values to some config settings, and I have also converted several values,
i.e (stop-Time) so that it can more easily be worked with. There is a potential issue with this though, that of it possibly running over max overflow in seconds.

## Data Structures

### State
I have constructed the state `struct` to behave in an as 'immutable' form as possible.
This is in the hope that I can have an easily follow-able (singly-linked list). 
### Stats
This Struct is passed back to the upper levels, and contains the entire stsate list, and will also contain the experiment information.
In this way, I can pass in a Stats struct and print out the entire output of the program.
### Stops
Having considered several ways of implementing this, I went with a simple struct.
The contents I defined as having a no. (corresponding to it's position in the map),
an `adjacency` value, which is simply the number of adjacent stops to the current stop,
and an array of `edges`, corresponding to the numbers of the stops that are adjacent to the current stop.
Initially I had planned on using references to the actual stop structs, but I was getting serious issues with
persistence of addresses for some reason.
### IList
this is simply a linked-list of integers. useful when dealing with graphs that can grow to unknown sizes.

In actuality, the array of `edges` are structs, (`StopEdge`), that contain both a weight, source and destination
value. the weight being the cost of traveling that edge, and the source and destination values corresponding to
bus stops.

## Simulation Algorithm
The solution that I have come up with is a simple 2 method deep iteration loop.
I will simply call a `run_experiment` method, with an initial state passed in, and it will run the experiment accordingly. (I plan on doing all checks that need to be done beforehand, so that I don't need to deal with anything extraneous during the execution)
The `run_experiment` method will then loop on a `run_iteration` method, which also takes in a state, chooses relevant actions, and updates the state accordingly. I plan on the state objects becoming a singly linked list, that will let me walk back over my previous states, and extract data that I need.

I decided on using Dijkstra's algorithm for doing optimal path-finding. I had several ideas for refining it to increase efficiency. this included skipping buses that were at maximum capacity, or buses that exceeded the current minimum traveling time of a previous bus.
# Testing
I have written some basic testing, that covers the basic parsing of config files with different layouts.
I elected to exit the program on an invalid config file parse. This does mean that I won't be able to test it.
possibly I should look into how to complete parsing the config file, and what to do then.

The testing at the moment is fairly rudimentary, as there is little else happening other than the parsing of the config file.

I have tried to abstract away as much of the unnecessary code as possible, this reduces the chance of errors, and lets me focus on wilting tests.

