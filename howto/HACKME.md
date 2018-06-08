## Installing SocketCAN on Linux

1. Install SocketCAN a.k.a. the `can-utils` package

There are two ways to install the `can-utils`: The first one is to install the package via the package manager, the second one is to compile the latest version by your own. Both methods are descriped here:

* Install the default `can-utils` package provided by most Debian/Ubuntu based distributions with:
```
sudo apt install can-utils
```
**OR**

* Build the package by your own:

    1. Clone the following repository with: `git clone https://github.com/linux-can/can-utils.git`
    2. Enter the directory via bash and run the following commands:

```sh
./autogen.sh
./configure
make
sudo make install
```

For further details and troubleshooting consider the [can-utils README](https://github.com/linux-can/can-utils/blob/master/README.md) and the [eLinux Wiki](http://elinux.org/Can-utils).


2. Load the Kernel modules

Since you probably have no real hardware CAN device, we use the virtual CAN interface for this guide. Therefore we have to load the Kernel module and set up the connection with:

    sudo modprobe vcan
    sudo ip link add dev vcan0 type vcan
    sudo ip link set up vcan0


3. Test the connection

* Open a Terminal window and typ `candump vcan0`
* Open another new Terminal window and send an arbitrary CAN message with
  `cansend vcan0 123#1122334455667788`

The first Terminal window should now show something like:

    user@linux ~ $ candump vcan0
      vcan0  123   [8]  11 22 33 44 55 66 77 88

For further informations and troubleshooting see:

[Using can-utils](https://discuss.cantact.io/t/using-can-utils/24)  
[Bringing CAN interface up](http://elinux.org/Bringing_CAN_interface_up)  
[SocketCAN](https://en.wikipedia.org/wiki/SocketCAN)  


## Installing ISO-TP

1. Clone the following repository with: `git clone https://github.com/hartkopp/can-isotp.git`

2. Enter the directory of the cloned repository in the bash and type `make`. If the `make` command finish successfully: Lucky you! Go grab a beer, celebrate your victory and proceed further with step 3.

Otherwise, if there is an error and make mumbles something about `error: to few arguments to function 'can_rx_register'` than:

* Open the file `~/can-isotp/net/can/isotp.c`
* Go to line 1112 and edit `if LINIX_VERSION_CODE >= KERNEL_VERSION(4,9,11)` into something that matches your current Kernel version e.g. `if LINIX_VERSION_CODE >= KERNEL_VERSION(4,4,0)` (type `uname -r` in the bash to show your version).
* Save the changes and try again.

3. Install the modules with `sudo make modules_install`.

4. Use this command only once after the installation `sudo depmod`



After these steps, the usage of ISO-TP should be possible. In case the application prints an error like `Protocol not supported`, there went something wrong with the installation. See [can-isotp README](https://github.com/hartkopp/can-isotp) for further instructions and troubleshooting.


## Testing the ISO-TP connection

1. Set up the CAN connection with the following commands (like described before):
```
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
```
2. Open the receiver with `isotprecv -s 123 -d 321 -l vcan0`.

3. Open a new terminal window and transmit some test data thorough the sender via `echo 11 22 33 44 55 66 DE AD BE EF | isotpsend -s 321 -d 123 vcan0`.

4. Now, you should see how the first terminal window is receiving the data.

For further instructions and troubleshooting take a look into the [can-isotp README](https://github.com/hartkopp/can-isotp).

## Installing Lua on Linux

Install the `lua5.2`, `liblua5.2-0`, and `liblua5.2-dev` packages with:

    sudo apt install lua5.2 liblua5.2-0 liblua5.2-dev

Include Lua support in the C++ file with:

```cpp
#include <lua.hpp>
```

The access from the C++ code to the Lua scripts is done via Selene. See the [_Selene_ GitHub Page](https://github.com/jeremyong/Selene) for a simple introduction.


## Install Unit-Tests

Install the following CppUnitTest packages with:

    sudo apt install libcppunit-1.* libcppunit-dev

The build target according to the Makefile is `make test`.

## Using gcov and lcov with netbeans

1. configure your netbeans:
```
right click your project -> Properties -> Build -> C++ Compiler and Linker -> add "--coverage"
```
2. invoking gcov
```	
gcov [options] files
```
3. invoking lcov
```
lcov --capture --directory project-dir --output-file coverage.info
```
4. Generate HTML output
```
genhtml coverage.info --output-directory out
```
5. find the out folder and open it and find the index.html open it. Then you have the graphical view of your code coverage


## Set-Up an IDE

You can choose the easy way with the [NetBeans Set-Up](NetBeansSetUp.md) or the harder one with the [Eclipse Set-Up](EclipseSetUp.md)

_(Author's note: NetBeans is more comfortable in any way)_


## Set-Up on the Raspberry PI

ISO-TP has to be installed on the PI (see above). Connect to the PI via ssh and clone this repository. Then execute `resources/setup-can.sh` to set up the CAN link.

The lua config files go into the folder which is specified in `src/config.h` (by default this is `lua_config`). If you change the lua scripts you will have to restart the whole server.

Build the server with `make`. To start the server, execute one of the binarys in `dist` from the main directory of the repository. The first, and only, command line parameter specifies the device (vcan0 be default). E.g:
```
dist/Debug/GNU-Linux/amos-ss17-proj4 can0
```

To modify the build system best open the project in Netbeans (see above).

## Set-Up on Virtual Machine
If the simulator should be installed on a virtual linux machine just do the following steps to get the simulator running.

ISO-TP

As like in the Set-Up for the Raspberry PI, ISO-TP should be installed. If the CAN connection should be started while your system is starting, do the following steps.

1. Load the can modules into the modules.conf file. This file can be found in your systems root directory via this path `/etc/modules-load.d`

2. Open the file with the command `sudo nano modules.conf`

3. Insert 
```
vcan
isotp
```
Leave the nano terminal with ctrl + x, save with j and enter. Now open the file and check if the file was modified.

4. Next open the file rc.local in the root directory with `sudo nano /etc/rc.local`

5. Insert
```
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
```
Leave the nano terminal like in step 3.

6. Now restart the system.

Build and Start the Server

Build the server with `make` in the main directory. 

Create a directory named `lua_config` in the directory `dist/Debug/GNU-Linux/`. Copy the file `example.lua` from the directory `tests/test_config_dir/` into the lua_config directory.

To start the server, execute the binary in the directory `dist/Debug/GNU-Linux/`. The first, and only, command line parameter specifies the device (vcan0 be default). E.g:
```
sudo ./amos-ss17-proj4 vcan0
```

To modify the build system best open the project in Netbeans (see above).






