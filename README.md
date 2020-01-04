# Milestone-1
Advanced Programming 1

[Link to project's github repository](https://github.com/Idany95/Milestone-1)

This project is a code interpreter that allows us to remotely control a flight simulator

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

What things you need to install the software and how to install them

```
Flightgear - Download it from Ubuntu Software application. 
```
make sure to copy generic_smalls.xml to protocol folder, under the installation folder 
 
## Running the tests

1. You can use the default code in "fly.txt" or edit it as you wish (see "How to edit "fly.txt" section)
2. Compile the program with the following command (You could also use your favorite IDE):
```
g++ -std=c++14 */*.cpp *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```
3. Run it using the following command
```
./a.out "fly.txt"
```
4. Open "Flightgear" simulator, and hit "fly".
5. Wait couple of minutes and see the plane in action!

### How to edit "fly.txt"

Our interpreter supports the following commands:

Open Server Command
This command creates a local server for the simulator to connect to.
```
openDataServer(5400)
```

Connect Command
This commands allows us to connect to the simulator as a client, and send it data.
```
connectControlClient("127.0.0.1",5402)
```

Define Variable command:
```
var throttle -> sim("/controls/engines/current-engine/throttle")
```
"->" means that assignment in "fly.txt" will affect the simulator

"<-" means that the simulator will affect local Variables

Creating variables for local usage is also an option:
```
var h0 = heading
```

Set Variable Command:
```
throttle = 1
```

If command:
```
if alt >= 1000 {
 *DO WHATEVER'S IN HERE*
}
```

Loop Command
```
while autostart == 1 {
 *DO WHATEVER'S IN HERE*
}
```

Print Command
```
Print("Hello World") //Will print the string Hello World
```
or
```
Print(alt) //Will print the numerical value of the variable var
```

Sleep Command
```
Sleep(500) //Will make the program go to sleep for 500ms
```

And one last special feature:
All parameters can be assigned as arthmetical expression (besides strings like "127.0.0.1
"). For example:
```
Sleep((300 + 200) / 5)
warp = (alt + 1800) * 2
```

### Break down into end to end tests

We tested the program with different scenarios. For example:

Empty loops
```
while rpm <= 750 {
}
```

Variables that wasn't set as one of the 36 variables in small_generics.xml
```
var br -> sim("/controls/gear/brake-right")
br = 1
```

## Built With

* [Clion](https://www.jetbrains.com/clion/) - Our favorite IDE

## Authors

* **Nili Alfia* - [niliya96](https://github.com/niliya96)

* **Idan Yarchi* - [idany95](https://github.com/Idany95)

## Acknowledgments

* We'd like to thank our families and friends for supporting us during the making of this project.
