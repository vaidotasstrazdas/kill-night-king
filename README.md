# Kill the Night King Server

Game is started with the client as soon as channel is opened to the server by the client. The channel can be opened in the following way (e.g. using **telnet**):
`open 127.0.0.1 6666`
Of course, it is assumed server is running on your computer, and server listens to 6666 port.

### How to Lose?
It is pretty easy. Do nothing and you will lose, sinze zombies will reach the wall, and you will be turned into zombie. So, try not to lose.

### How to Win?
Kill specified amount of zombies by the server. Then, Night King will run away, and Westeros will be saved until the next winter.

### How to Kill a Zombie?
If zombie is at (0, 29) position, then just send the following command, and zombie will die:
`A0,0;0,29\n`
What is **0,0**? It is you archer's position. It is not validated currently, so you can put here anything you like. However, **0,29** must be correct position of a zombie you want to kill.

### Features
- You can become a zombie if you lose.
- Separate threads are created for each new client, so there should be no problems to play for multiple users at once without any lag.
- Server is configurable (grid size, game update time interval by the server, zombies to kill in order to win, port to listen to).
- Log of what's happening between server and it's clients textual representation in a dialog.
- Server can be closed and run again.

### Missing
- Automatic port forwarding. In other words, if your remote IP is, for example, 123.123.123.123, and you want to start server remotely at 123.123.123.123:6666, you will have to add forwarding rule to your router manually.

### Tools Used
- C++11 as programming language.
- Qt Creator as a tool to build, debug the server, create UI views, write code and unit tests testing the code written. However, there a better choice would be CMake, Visual Studio, BOOST for build and unit tests organization (it is easier to make this work in cross-platform way). Still, due to time limitation, I have chosen the way which would be faster in short-term.
- Qt as a framework to create a server, UI views, view models. Specifically, **QTcpServer** is used as a server instance which allows to listen to connections from client, and **QTcpSocket** as instance to accept incoming streams from clients, and write response to it.
- In other words, TCP/IP is being used to ensure bi-directional communication between server and client.

### How to Build and Run
- Download Qt5.8.0. It can be downloaded from http://download.qt.io/official_releases/qt/5.8/5.8.0/ .
- Run Qt Creator.
- Using Qt Creator, build and run the project.
- **Note.** Qt is cross-platform framework, so it should build properly on all most popular platforms. However, it was tested on Windows 7 and macOS Sierra Version 10.12.6, so I can not guarantee that it will really build on any other platforms than the mentioned ones.