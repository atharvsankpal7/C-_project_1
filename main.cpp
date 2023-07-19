#include <iostream>
#include <string> 
#include <cstdlib>
#include <vector>

using namespace std;

class PasswordGenerator {
  public:
    virtual string generatePassword(int length, bool includeNumbersAndSymbols) {
      
      string password;
      
      // Seed random number generator
      srand(time(0));
      
      for(int i=0; i<length; i++) {
      
        char c = 'a' + rand() % 26;
        
        if(includeNumbersAndSymbols && rand()%2 == 0) {
        
          if(rand()%2 == 0) {
            c = '0' + rand()%10;  
          } else {
            string symbols = "!@#$%^&*()_+-=[]{};':\"<>,.?/|\\";
            c = symbols[rand() % symbols.size()];
          }
        }
        
        password += c;
      }
      
      return password;
    }
};

class AdvancedPasswordGenerator : public PasswordGenerator
{
public:
    string generatePassword(int length, bool includeNumbersAndSymbols) override
    {
        string password = PasswordGenerator::generatePassword(length, includeNumbersAndSymbols);

        // Add uppercase letters to the password
        for (int i = 0; i < password.size(); i++)
        {
            if (rand() % 2 == 0)
            {
                password[i] = toupper(password[i]);
            }
        }

        return password;
    }
};
int main()
{
    PasswordGenerator *generator = new AdvancedPasswordGenerator();
    vector<string> passwords;

    while (true)
    {
        // Take password length from user
        cout << "Enter the length of the password (0 to exit): ";
        int length;
        cin >> length;

        if (length == 0)
        {
            break;
        }

        // Prompt user to include numbers and symbols
        cout << "Include numbers and symbols in the password (y/n)? ";
        char input;
        cin >> input;
        bool includeNumbersAndSymbols = (input == 'y');

        // Generate password
        string password = generator->generatePassword(length, includeNumbersAndSymbols);

        // Display password
        cout << "Your password is: " << password << endl;

        passwords.push_back(password);
    }

    // Display list of generated passwords
    cout << "Generated passwords:" << endl;
    for (int i = 0; i < passwords.size(); i++)
    {
        cout << passwords[i] << endl;
    }
    return 0;
}
