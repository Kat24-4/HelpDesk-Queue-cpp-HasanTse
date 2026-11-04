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
The following images are from the test output sample session. Running the above test command should produce the same results.

<img width="767" height="717" alt="HelpDeskSampleSession1" src="https://github.com/user-attachments/assets/651bc76d-1482-4e8f-b722-1c18c2a27561" />
<img width="815" height="722" alt="HelpDeskSampleSession2" src="https://github.com/user-attachments/assets/42342546-d89f-4a4a-a4dd-617510ad74b6" />
<img width="788" height="642" alt="HelpDeskSampleSession3" src="https://github.com/user-attachments/assets/972de626-7411-4604-98a2-8203861af52c" />
<img width="727" height="596" alt="HelpDeskSampleSession4" src="https://github.com/user-attachments/assets/d0258595-7d02-4f1d-9aa9-6f647fa63817" />
<img width="732" height="566" alt="HelpDeskSampleSession5" src="https://github.com/user-attachments/assets/99ee23ad-28e7-4263-8e77-00b142e47bca" />
<img width="585" height="312" alt="HelpDeskSampleSession6" src="https://github.com/user-attachments/assets/abcb48b9-3099-40c5-a53f-ffdefc3309c0" />

## Simulation Results
