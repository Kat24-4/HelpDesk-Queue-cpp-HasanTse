# EECE 7205 Help Desk Queue - Nashita Hasan, Katherine Tse 

## The Problem 
An IT help desk wants a system that will store requests as tickets as they come in and allow agents to serve them in that order. Agents and Managers must be able to add, serve, undo, search, cancel, and print the tickets. Additionally, tickets can be created from a CSV file and stored into a CSV file. 

## Class Design 
### TicketQueue Class
The TicketQueue class utilizes the queue data structure implemented with a linked list where each node is an instance of the Ticket class. 

#### ActionStack Class 
The ActionStack class utilizes the stack data structure implemented with a linked list where each node is an instance of the Action class.

## Build and Run Commands
The code can be built using the following bash command from the main folder of the project: `g++ src/main.cpp -o helpdesk`

The code can be run in test mode to generate a test output with the following command: `./helpdesk test`

The code can be run with a menu to try each function with the following command: `./helpdesk`

## Sample Session

## Simulation Results