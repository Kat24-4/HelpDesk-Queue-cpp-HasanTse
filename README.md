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
### 1 Agent
<img width="873" height="561" alt="HelpDesk1Agent" src="https://github.com/user-attachments/assets/1a6f68a9-f75a-4c3a-a6c5-4cfba6990d77" />

Average Wait Time = (0 + 10 + 35 + 75 + 90 + 110 + 140 + 152 + 187 + 232) / 10 = 1031 / 10 = 103.1 Minutes

Longest Wait Time = 232 Minutes

Total Waiting Minutes = 250 Minutes

### 2 Agents 
<img width="967" height="580" alt="HelpDesk2Agents" src="https://github.com/user-attachments/assets/4e38cf91-0a36-4d25-8ee5-f1f950202a8b" />

Average Wait Time Agent 1 = (0 + 10 + 50 + 70 + 82) / 5 = 212 / 5 = 42.4 Minutes

Average Wait Time Agent 2 = (0 + 25 + 40 + 70 + 105) / 5 = 240 / 5 = 48 Minutes

Total Average Wait Time = (0 + 0 + 10 + 25 + 50 + 40 + 70 + 70 + 82 + 105) / 10 = 45.2 Minutes 

Longest Wait Time Agent 1 = 82 Minutes

Longest Wait Time Agent 2 = 105 Minutes

Total Waiting Minutes Agent 1 = 127 Minutes

Total Waiting Minutes Agent 2 = 123 Minutes
