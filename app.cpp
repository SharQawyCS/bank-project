#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <iomanip>

using namespace std;

// Data
struct stClient
{
  string accNum;
  string pinCode;
  string name;
  string phone;
  float accBalance;
};

const char FILE_NAME[] = "clients.txt";

// Functions Prototypes
void showMainMenu();
void addNewClients();
void printClientData(stClient client);

// Clear Screen
void clearScreen()
{
#ifdef _WIN32
  // Windows system
  system("cls");
#else
  // POSIX system (Linux, macOS)
  system("clear");
#endif
  cout << endl;
}
// Exit Program
void exitProgram(int exitCode = EXIT_SUCCESS)
{
  clearScreen();
  cout << "Thanks for using our Bank App :)" << endl;
  cout << "Exiting the program..." << endl;
  exit(exitCode); // Terminate the program with the given exit code
}
// Back To Main Menu
void backToMainMenu()
{
  cout << "\nPress 0 to back to main menu: ";
  string choice;
  cin >> choice;
  if (choice == "0")
  {
    clearScreen();
    showMainMenu();
  }
  else
  {
    cout << "Wrong, Please try Again\n";
    backToMainMenu();
  }
}

// Read inputs
string readString(string message)
{
  string s1;
  cout << message;
  getline(cin, s1);
  return s1;
}
float readFloat(string message)
{
  float num;
  cout << message;
  cin >> num;
  return num;
}
short getUserChoice(short min, short max)
{
  short choice;
  while (true)
  {
    cin >> choice;

    // Check if the input is a valid short and within the specified range
    if (cin.fail())
    {
      cin.clear();                                         // clear the error flag
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
      cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
    }
    else if (choice < min || choice > max)
    {
      cout << "Number out of range. Please enter a number between " << min << " and " << max << ": ";
    }
    else
    {
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard any remaining input
      return choice;
    }
  }
}

// Data and file
vector<string> splitString(string S1, string Delim)
{
  vector<string> vString;
  short pos = 0;
  string sWord; // define a string variable
                // use find() function to get the position of the delimiters
  while ((pos = S1.find(Delim)) != std::string::npos)
  {
    sWord = S1.substr(0, pos);
    // store the word
    if (sWord != "")
    {
      vString.push_back(sWord);
    }
    S1.erase(0, pos + Delim.length());
    /* erase() until positon and move to next word. */
  }
  if (S1 != "")
  {
    vString.push_back(S1); // it adds last word of the string.
  }
  return vString;
}

stClient convertLineToRecored(string line, string sep = "#//#")
{
  stClient client;
  vector<string> clientData = splitString(line, sep);

  client.accNum = clientData[0];
  client.pinCode = clientData[1];
  client.name = clientData[2];
  client.phone = clientData[3];
  client.accBalance = stof(clientData[4]);

  return client;
}

vector<stClient> LoadClientsDataFromFile(string fileName)
{
  vector<stClient> vClients;
  fstream myFile;
  myFile.open(fileName, ios::in); // read Mode
  if (myFile.is_open())
  {
    string line;
    stClient client;
    while (getline(myFile, line))
    {
      client = convertLineToRecored(line);
      vClients.push_back(client);
    }
    myFile.close();
  }
  return vClients;
}

string generateLineFromRecord(stClient client, string sep = "#//#")
{
  string line = client.accNum + sep;
  line += client.pinCode + sep;
  line += client.name + sep;
  line += client.phone + sep;
  line += to_string(client.accBalance);

  return line;
}

void addDataLineToFile(string fileName, string line)
{
  fstream myFile;
  myFile.open(fileName, ios::out | ios::app);
  if (myFile.is_open())
  {
    myFile << line << endl;
    myFile.close();
  }
}

void addClientToFile(stClient client, string fileName)
{
  string dataLine = generateLineFromRecord(client);
  addDataLineToFile(fileName, dataLine);
}

void addNewClientsVectorToFile(vector<stClient> vClients)
{
  remove(FILE_NAME);
  for (stClient &client : vClients)
  {
    addClientToFile(client, FILE_NAME);
  }
}

stClient getClientFromFileByAccNum(string fileName, string accNum)
{
  vector<stClient> vClients = LoadClientsDataFromFile(fileName);
  for (vector<stClient>::iterator it = vClients.begin(); it != vClients.end();)
  {
    if (it->accNum == accNum)
    {
      return *it;
    }
    else
    {
      ++it;
    }
  }
  // Trash Struct, it supposed to be not returned
  return {"ERROR", "CHECK_FILE", "CANNOT_GET_DATA", "RESTART_APP", 0};
}

// MAIN FUNCTIONS
// For Client List [1]
void printHeader(int clientsNO)
{
  cout << "\n\t\t\tClient List (" << clientsNO << ") Client(s).";
  cout << "\n______________________________________________";
  cout << "________________________________\n"
       << endl;
  cout << "| " << left << setw(15) << "Accout Number";
  cout << "| " << left << setw(10) << "Pin Code";
  cout << "| " << left << setw(20) << "Client Name";
  cout << "| " << left << setw(12) << "Phone";
  cout << "| " << left << setw(12) << "Balance";
  cout << "\n______________________________________________";
  cout << "________________________________\n"
       << endl;
}
void printOneRow(stClient client)
{
  cout << "| " << setw(15) << left << client.accNum;
  cout << "| " << setw(10) << left << client.pinCode;
  cout << "| " << setw(20) << left << client.name;
  cout << "| " << setw(12) << left << client.phone;
  cout << "| " << setw(12) << left << client.accBalance;
}
void showClientList()
{
  clearScreen();
  vector<stClient> vClients = LoadClientsDataFromFile(FILE_NAME);
  printHeader(vClients.size());

  for (stClient &singleClient : vClients)
  {
    printOneRow(singleClient);
    cout << "\n";
  }
  cout << "______________________________________________";
  cout << "________________________________\n"
       << endl;
  backToMainMenu();
}

// For Adding New Clients [2]
short isClientExist(string fileName, string accNum)
{
  vector<stClient> vClients = LoadClientsDataFromFile(fileName);

  short index = -1;
  for (int i = 0; i < vClients.size(); ++i)
  {
    if (vClients[i].accNum == accNum)
    {
      index = i;
    }
  }
  // Returns Client index if exist and -1 is not
  return index;
}
stClient readNewClient()
{
  stClient client;
  string accNumByUser = readString("Plz enter account number: ");
  if (isClientExist(FILE_NAME, accNumByUser) == -1)
  {
    client.accNum = accNumByUser;
  }
  else
  {
    cout << "Client With Account Number " << accNumByUser << " is Exist!\n";
    cout << "[0] Back to Main Menu\n[1] Add another client\n: ";
    switch (getUserChoice(0, 1))
    {
    case 0:
      showMainMenu();
      break;
    case 1:
      addNewClients();
      break;
    default:
      break;
    }
  }
  client.pinCode = readString("plz enter pin Code: ");
  client.name = readString("plz Enter ur name: ");
  client.phone = readString("plz enter ur phone num: ");
  client.accBalance = readFloat("plz enter Account balance($): ");

  return client;
}
void addNewClients()
{
  clearScreen();
  cout << "Adding New Client... \n\n";
  addClientToFile(readNewClient(), FILE_NAME);
  cout << "\nClient Added Successefully! \n\n";
  cout << "[0] Back to Main Menu\n[1] Add another client\n: ";
  switch (getUserChoice(0, 1))
  {
  case 0:
    showMainMenu();
    break;
  case 1:
    addNewClients();
    break;
  default:
    break;
  }
}

// For Delete Client [3]
void eraseClientByClientNumber(string fileName, string accNum)
{
  vector<stClient> vClients = LoadClientsDataFromFile(fileName);
  for (vector<stClient>::iterator it = vClients.begin(); it != vClients.end();)
  {
    if (it->accNum == accNum)
    {
      it = vClients.erase(it);
    }
    else
    {
      ++it;
    }
  }
  addNewClientsVectorToFile(vClients);
}
void deleteClient()
{
  clearScreen();

  string accNumByUser = readString("Plz enter account number to DELETE: ");
  if (isClientExist(FILE_NAME, accNumByUser) == -1)
  {
    cout << "No Account with Number " << accNumByUser << endl;
    cout << "\n[0] Back to Main Menu\n[1] Try Agian\n: ";
    switch (getUserChoice(0, 1))
    {
    case 0:
      showMainMenu();
      break;
    case 1:
      deleteClient();
      break;
    default:
      break;
    }
  }
  else
  {
    eraseClientByClientNumber(FILE_NAME, accNumByUser);

    clearScreen();
    cout << "Account with Number " << accNumByUser << " deleted!" << endl;
    cout << "\n[0] Back to Main Menu\n[1] Delete Another Client\n: ";
    switch (getUserChoice(0, 1))
    {
    case 0:
      showMainMenu();
      break;
    case 1:
      deleteClient();
      break;
    default:
      break;
    }
  }
}

// For Update Client Info [4]
stClient readNewClient(string accNumToUpdateClient)
{
  stClient client;

  client.accNum = accNumToUpdateClient;
  client.pinCode = readString("plz enter new pin Code: ");
  client.name = readString("plz Enter new name: ");
  client.phone = readString("plz enter new phone num: ");
  client.accBalance = readFloat("plz enter new Account balance($): ");

  return client;
}
void updateClientInfo()
{
  clearScreen();

  string accNumByUser = readString("Plz enter account number to UPDATE: ");
  if (isClientExist(FILE_NAME, accNumByUser) == -1)
  {
    cout << "No Account with Number " << accNumByUser << endl;
    cout << "\n[0] Back to Main Menu\n[1] Try Agian\n: ";
    switch (getUserChoice(0, 1))
    {
    case 0:
      showMainMenu();
      break;
    case 1:
      updateClientInfo();
      break;
    default:
      break;
    }
  }
  else
  {
    // NO VALIDATION NEEDEED, THE ACCOUNT NUMBER HERE IS TRUE!!!!
    // 1- Show client
    clearScreen();
    printClientData(getClientFromFileByAccNum(FILE_NAME, accNumByUser));

    // 2- erase client
    eraseClientByClientNumber(FILE_NAME, accNumByUser);

    // 3- Make user enter new client
    addClientToFile(readNewClient(accNumByUser), FILE_NAME);

    // DONE!
    clearScreen();
    cout << "Account with Number " << accNumByUser << " updated!" << endl;
    cout << "\n[0] Back to Main Menu\n[1] Update Another Client\n: ";
    switch (getUserChoice(0, 1))
    {
    case 0:
      showMainMenu();
      break;
    case 1:
      updateClientInfo();
      break;
    default:
      break;
    }
  }
}

// For Find Client [5]
void printClientData(stClient client)
{
  cout << "Account Number   : " << client.accNum << "\n";
  cout << "Pin Code         : " << client.pinCode << "\n";
  cout << "Member Name      : " << client.name << "\n";
  cout << "Phone Number     : " << client.phone << "\n";
  cout << "Total Balance    : " << client.accBalance << "\n";
  cout << endl;
}
void findClient()
{
  clearScreen();

  string accNumByUser = readString("Plz enter account number to FIND: ");
  if (isClientExist(FILE_NAME, accNumByUser) == -1)
  {
    clearScreen();
    cout << "No Account with Number " << accNumByUser << endl;
    cout << "\n[0] Back to Main Menu\n[1] Try Agian\n: ";
    switch (getUserChoice(0, 1))
    {
    case 0:
      showMainMenu();
      break;
    case 1:
      findClient();
      break;
    default:
      break;
    }
  }
  else
  {
    clearScreen();
    printClientData(getClientFromFileByAccNum(FILE_NAME, accNumByUser));
    cout << "\n[0] Back to Main Menu\n[1] Find Another Client\n: ";
    switch (getUserChoice(0, 1))
    {
    case 0:
      showMainMenu();
      break;
    case 1:
      findClient();
      break;
    default:
      break;
    }
  }
}

// Main Menu Function
void showMainMenu()
{
  clearScreen();
  // Header
  cout << "-----------------------------\n"
       << "      Main Menu Screen\n"
       << "-----------------------------\n";

  // Options
  cout << "[1] Show Clients List.\n"
       << "[2] Add New Client.\n"
       << "[3] Delete Client\n"
       << "[4] Update Client Info\n"
       << "[5] Find Client.\n"
       << "[0] EXIT.\n";

  // Footer
  cout
      << "-----------------------------\n"
      << "  Choose from [0] to [5]... ";

  // Choosing
  switch (getUserChoice(0, 5))
  {
  case 1:
    showClientList();
    break;
  case 2:
    addNewClients();
    break;
  case 3:
    deleteClient();
    break;
  case 4:
    updateClientInfo();
    break;
  case 5:
    findClient();
    break;

  case 0:
    exitProgram();
    break;

  default:
    break;
  }
}

int main()
{
  showMainMenu();
  return 0;
}