# PIDcontroller
This is a very simple library, implementation of a iterative digital PID controller. This code could easily be copy pasted and used, this implementation here just provides a modularity reuse of same code.

## Setup instructions

**Download source code :**
 * `git clone https://github.com/RohanVDvivedi/PIDcontroller.git`

**Build from source :**
 * `cd PIDcontroller`
 * `make clean all`

**Install from the build :**
 * `sudo make install`
 * ***Once you have installed from source, you may discard the build by*** `make clean`

## Using The library
 * add `-lpidcontroller -lm` linker flag, while compiling your application
 * do not forget to include appropriate public api headers as and when needed. this includes
   * `#include<pidcontroller/pid.h>`

## Instructions for uninstalling library

**Uninstall :**
 * `cd PIDcontroller`
 * `sudo make uninstall`
