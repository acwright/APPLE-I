APPLE-I
=======

This is a collection of my Apple I assembly language programs.

## Building Programs

Each program directory contains its own Makefile. To build a program, navigate to its directory and use `make`.

### Available Targets

- `make` or `make all` - Build the program
- `make view` - Display hexdump of the built program
- `make woz` - Convert the output to Wozmon compatible format
- `make clean` - Remove build artifacts

### Example 

```bash
cd <directory-name>
make        # Build the program
make view   # View the hexdump
make woz    # Convert the output to Wozmon compatible format
```

