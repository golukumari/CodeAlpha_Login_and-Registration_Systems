#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

const string FILE_NAME = "users.txt";

// Validate username
bool validUsername(string username)
{
    if (username.length() < 3 || username.length() > 20)
    {
        return false;
    }

    for (int i = 0; i < username.length(); i++)
    {
        char ch = username[i];

        if (!isalnum(static_cast<unsigned char>(ch)) && ch != '_')
        {
            return false;
        }
    }

    return true;
}

// Validate password
bool validPassword(string password)
{
    if (password.length() < 8)
    {
        return false;
    }

    bool hasLetter = false;
    bool hasDigit = false;

    for (int i = 0; i < password.length(); i++)
    {
        unsigned char ch = password[i];

        if (isalpha(ch))
        {
            hasLetter = true;
        }

        if (isdigit(ch))
        {
            hasDigit = true;
        }
    }

    return hasLetter && hasDigit;
}

// Check whether username already exists
bool usernameExists(string username)
{
    ifstream file(FILE_NAME.c_str());

    string storedUsername;
    string storedPassword;

    while (file >> storedUsername >> storedPassword)
    {
        if (storedUsername == username)
        {
            return true;
        }
    }

    return false;
}

// Registration function
void registerUser()
{
    string username;
    string password;

    cout << "\n===== REGISTRATION =====\n";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    if (!validUsername(username))
    {
        cout << "Error: Username must contain 3-20 "
             << "letters, numbers, or underscores.\n";
        return;
    }

    if (!validPassword(password))
    {
        cout << "Error: Password must contain at least "
             << "8 characters, one letter, and one digit.\n";
        return;
    }

    if (usernameExists(username))
    {
        cout << "Error: Username already exists!\n";
        return;
    }

    ofstream file(FILE_NAME.c_str(), ios::app);

    if (!file)
    {
        cout << "Error: Unable to open the file.\n";
        return;
    }

    // This beginner version stores the password as plain text.
    // Do not use it for real users or sensitive passwords.
    file << username << " " << password << endl;

    file.close();

    if (!file)
    {
        cout << "Error: Could not save user details.\n";
        return;
    }

    cout << "Registration successful!\n";
    cout << "You can now log in.\n";
}

// Login function
void loginUser()
{
    string username;
    string password;

    string storedUsername;
    string storedPassword;

    cout << "\n===== LOGIN =====\n";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file(FILE_NAME.c_str());

    if (!file)
    {
        cout << "Error: No registered users found.\n";
        cout << "Please register first.\n";
        return;
    }

    while (file >> storedUsername >> storedPassword)
    {
        if (storedUsername == username)
        {
            if (storedPassword == password)
            {
                cout << "Login successful!\n";
                cout << "Welcome, " << username << "!\n";
            }
            else
            {
                cout << "Error: Incorrect password.\n";
            }

            return;
        }
    }

    cout << "Error: Username not found.\n";
    cout << "Please register first.\n";
}

// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n================================\n";
        cout << " LOGIN AND REGISTRATION SYSTEM\n";
        cout << "================================\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Error: Please enter a number.\n";
            return 1;
        }

        switch (choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Select 1, 2, or 3.\n";
        }

    } while (choice != 3);

    return 0;
}


