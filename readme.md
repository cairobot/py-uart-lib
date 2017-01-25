#cairo/py-uart-lib

##desc
A simple library for accessing serial unix devices via python. This library exclusively exposes a uart configuration of 8 data bits and 1 stop bit, since I'm lazy and the project didn't require a highly sufisticated library. Pyserial didn't like us, it would work and then again it wouldn't without any changes to the codebase (it worked for about 5% of the cases), thus, this library has been written.