# cmdset
Simple commandline tool to buffer a set of characters to execute

## Build

It should be a simple `make clean && make`

## Running

Currently, the following is a simple example of how to use this:

1. Find the window ID you would like to livecode in, be sure `AllowSendevents` is enabled:
```
xdotool getactivewindow
```
2. Run cmdset as follows:
For example:
```
./cmdset -w WINDOW_ID -t DELAY_TIME -i INPUT_SCRIPT -o OUTPUT_SCRIPT
```

For example:
```
./cmdset -w 41943074 -t 50 -i examples/script -o examples/output
```
3. Run `./output`

## Notes:
Might be a little insecure because of the send events thing. Not sure.

## TODO:
Variable text speed depending on which line of the script is being executed
