# Brief

Juno is a small and simple budget tracker for Windows and Linux. It's written in C++ and Qt, and uses SQLite for persistence.

## Why Desktop?

When using a cloud based service, the service provider will always be able to view your data. If you are storing our budget and expenses 
in the cloud, then they will be able to see what you are buying and analyze your behaviour (I'm not saying that they are in fact
doing this, only that it is a possibility - always read the license agreements of any service you use).

However, with Juno all your data resides in a local database. The application will not collect any kind of telemetry or
send your data anywhere. If you don't want it anymore, just delete the database file and all is gone - no need to wonder if 
your data is still there in a backup somewhere.

If you still want a cloud based application, you can always put the database file in a Google Drive or OneDrive :) 

# Installation

## AppImage

For Linux user and AppImage image is provided on github.

## Windows

I don't know at the moment how the application will be distributed on Windows. It could either be a "raw" exe file
or some kind of installer. We'll see!

## Build From Source

To build Juno on Linux, you will need:

- Qt framework (Juno is developed on version 6.7)
- GCC or clang
- CMake

Currently, Juno is known to compile on Ubuntu Linux using GCC or Clang. MSVC also works on Windows if `CMAKE_PREFIX_PATH` is set properly. 

The long-term goal is to support all three compilers, however that is not an immediate objective. 