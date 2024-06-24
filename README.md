# bank-project
## Project Overview
**This project is a simple console-based banking application written in C++. It manages client information, including account numbers, PIN codes, names, phone numbers, and account balances. The application provides functionalities to add, delete, update, and find clients. It ensures cross-platform compatibility for clearing the console screen and exiting the program.**

## Project Structure

### Client Data Management:
- Storing and retrieving client information.
- Reading and writing data to/from a file.
  
### User Interface:
- Displaying menus.
- Handling user inputs.
  
### Utility Functions:
- Clearing the screen.
- Exiting the program.
- Validating user input.

## Key Functions
- **clearScreen():** Clears the console screen. Works on both Windows and POSIX systems (Linux, macOS).
  
- **exitProgram(int exitCode = EXIT_SUCCESS):** Clears the screen and exits the program with the provided exit code.
- **backToMainMenu():** Prompts the user to press '0' to return to the main menu.
- **performIfIsFileEmpty(const string fileName):** Checks if the client data file is empty and prompts the user to add a client if it is.
- **performDefault():** Handles unexpected errors and exits the program.
- **readString(string message):** Reads a string input from the user with a prompt message.
- **readShort(string message):** Reads a short input from the user with input validation.
- **getUserChoice(short min, short max):** Reads a user choice within a specified range.
- **printClientData(stClient client):** Prints client details.
- **findClient():** Finds and displays a client's details by account number.
- **showMainMenu():** Displays the main menu and handles user choices.



## Main Menu Options

[1] Show Clients List: Display the list of all clients.

[2] Add New Client: Add a new client to the database.

[3] Delete Client: Delete an existing client.

[4] Update Client Info: Update information for an existing client.

[5] Find Client: Find and display details of a client by account number.

[0] EXIT: Exit the application.


## Notes
**Error Handling:** The application includes basic error handling to manage invalid inputs and unexpected errors.

**Cross-Platform Compatibility:** The clearScreen and exitProgram functions ensure the application works on different operating systems.

**Data Persistence:** Client data is stored in a text file (clients.txt), ensuring data persistence between sessions.

## Conclusion
**This project provides a foundational framework for a console-based banking application. It includes essential functionalities for managing client data and a simple user interface.**

**The code can be further extended to include more features and robust error handling as needed.**
