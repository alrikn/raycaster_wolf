# wolf3d

a mini wolfenstein look alike

## Build

To compile the binary:

    make
    # or
    make re

The compiled binary will be called:

    wolf3d

## Usage

To run the program:

    ./wolf3d

To show the help message:

    ./wolf3d -h

## Description

- The player moves in a 2d array
- You cannot go outside the map
- You can change how big the map is in struct.h
- every map is randomly generated but there are only 10 enemies at any time. (you can change this in struct.h)
- the metadata is kept in the file called stats and save_file

## Disclaimer

You need to have the csfml library installed to run this.
