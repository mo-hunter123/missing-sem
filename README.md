# Missing Semester - Acceptance Test 

## Introduction 
This is an implementation of the acceptance test, for integrating the missing semester cohort

## A picture is worth a thousand words 
![Model](https://res.cloudinary.com/drmmqpbsw/image/upload/v1692113484/Screenshot_from_2023-08-15_16-26-47_fgyfuw.png)

This is a code architecture of how we access the /proc file system. 
By following the grasp patterns we are implementing a `Machine` class that will be an entry point of the different objects.

`MachineProcesses` is a class that will manage the current processes 

`MachineMemory` will manage the memory side 

`proc_service` is a set of functions responsible for accessing the `/proc` filesystem to get the different metrics 

## How to use this project 

First of all this project is a C++ project, where its main goal is to retrieve differnt metrics from 
the hosted Linux machine (The gathered data are in the Verfication section). 
To use the project
run the following to clone the project : 

```
git clone https://github.com/mo-hunter123/missing-sem.git
```

then build the sources, by running : 
```
make compile 
```

then start the application, by running : 
```
make start
```

And if you want to wrap terminal lines, just run : 
(you need to give needed permissions to the `nowrap.sh` script)
```
make start | ./nowrap.sh
```

To execute implemented tests, run : 
```
make test
```

## Screen 

![Screen shot](https://res.cloudinary.com/drmmqpbsw/image/upload/v1692113939/Screenshot_from_2023-08-15_16-34-45_yzkynb.png)

### Verification


- [ ] `README.md` with build instructions
- [x] Builds on Linux / Linux VM
- [x] Used one of the allowed programming languages (C, C++, Rust, Zig, Golang)
- [x] Monitor CPU
	- [x] Current total usage
	- [x] Current usage per application
	- [x] Current free
- [x] Monitor Memory
	- [x] Current total usage
	- [x] Current total free
	- [x] Current usage per application
- [ ] Monitor Disk
	- [ ] Available devices
	- [ ] Available partitions
	- [ ] Read rate per application
	- [ ] Write rate per application
- [x] Real-time stats collection
- [ ] UI (check any or both)
	- [x] Terminal-based UI
	- [ ] Prometheus + Grafana