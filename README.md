# Computer Science Large Practical

# Included Libraries
## CuTest
http://cutest.sourceforge.net/
The testing library has been included from the following place:
I have embeded it into my project, as this makes building easier.

# Implementation Details

## Config Parsing
I have set default values to some config settings, and I have also converted several values,
i.e (stopTime) so that it can more easily be worked with. There is a potential issue with this though, that of it possibly running over max overflow in seconds.


# Testing

I have written some basic testing, that covers the basic parsing of config files with different layouts.
I elected to exit the program on an invalid config file parse. This does mean that I won't be able to test it.
possibly I should look into how to complete parsing the config file, and what to do then.

The testing at the moment is fairly rudimentary, as there is little else happening other than the parsing of the config file.
