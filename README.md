# cxx-eda

## Description

This is a simple Event-Driven Architecture (EDA) project implemented in C++. It uses CMake for building. 

## Event-Driven Architecture

Event-Driven Architecture (EDA) is a software design pattern that promotes the production, detection, consumption of, and reaction to events. 

**An event** can be defined as a significant change in state. In EDA, components of the software system perform their tasks in response to receiving one or more **event notifications**, rather than as a result of a hierarchical method call. 

This architecture is particularly useful in systems where certain events can occur at any time and the system needs to be ready to handle them.

The project consists of the following components:

- `EventBroker`: This class sits between event publishers and event subscribers.
- `EventProducer`: This class is responsible for producing events.
- `EventConsumer`: This class is an event consumer that listens for events from producers.

## Building the Project

```sh
# create `build` directory
mkdir build 
cd build

# configure cmake with your build environment(gcc, clang, cl...)
cmake ..

# for gcc, build with make
make

# run the executable
./cxx-eda
```

I used `g++-mingw32(ucrt64)` in my Windows 10 desktop. Some of compilation flags in `CMakesLists.txt` won't work if you are using `cl.exe`(MSVC).

