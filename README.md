# Computer Science Large Practical

# Included Libraries
## CuTest
http://cutest.sourceforge.net/
The testing library has been included from the following place:
I have embeded it into my project, as this makes building easier.

## WhiteDb
http://whitedb.org
This provides me with an in-memory Graph-Database.
Note, in order to run this on OS X, the following needs to be run on the machine:

    sudo sysctl -w kern.sysv.shmmax=1073741824
    sudo sysctl -w kern.sysv.shmall=262144

In relation to running the `unite.sh` script, you will need to install `gnu-sed`.

    brew install gnu-sed --with-default-names

with everything now setup, you can just run:

    ./unite.sh

This should just work on DICE.
