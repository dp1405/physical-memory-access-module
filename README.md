# Character Device Driver for Linux Systems

This basic character device driver implements read and write system calls on it. It provides necessary files to communicate with hardware devices (in `/sys/class/` and `/dev/` directories).

## How to make the driver

Make sure you have building essentials installed in your linux system. For ubuntu distributions, it can be installed using following commands:

```console
sudo apt update
sudo apt upgrade
sudo apt install build-essential kmod linux-headers-$(uname -r)
```

After installing dependencies, clone the repository first:

```console
git clone https://github.com/dp1405/physical-memory-access-module.git
```

Switch to the directory and make the device driver using following commands:
```console
cd physical-memory-access-module
make
```

Alternately, run the the script `setup.sh` to do these operations automatically.

Further, to clean all the generated files, use:
```console
make clean
```

After building the driver, load it to the kernel using:
```console
sudo insmod pmad.ko
```

To check if the module has been added successfully or not, use:
```console
lsmod | grep pmad
```

To see the messages written to the kernel buffer, use:
```console
sudo dmesg
```

To execute read and write operations from the terminal, use following commands:
```console
echo "Message to write" | sudo tee /dev/pmad0           # write to file
sudo cat /dev/pmad0                                     # read from file
```

