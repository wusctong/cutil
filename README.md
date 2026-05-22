# Class Utility

Utilities for classrooms.


## Dependencies

`make` - Build tool.

`raylib` - Graphics library.


## Requirements

`font.ttf` - A Chinese font for text rendering,
put it under the same directory as the executable
(or where you run the executable from).
**Required for building, replace it in the Makefile.**

`names.txt` - A name list (optional).
One name for each line. Set to my class's by default.

`config.txt` - A configuration file (optional).
Only reads the first line of the file as the scale value now.
More functionality will be implemented.


## Building

To build the project for mac & linux, run the following command:

``` bash
make build
```

For windows, run the following command:

``` bash
make build-win
```

To disable console window for windows, run the following command:

``` bash
make build-win-release
```

To clean up the build directory, run the following command:

``` bash
make clean
```


## Usage

Run the executable file, it's a GUI application.


---

**©wusctong26**
