#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
#include <vector>

using namespace std;

struct ContactNode
{
public:
    string name;
    string phoneNumber;
    ContactNode *left;
    ContactNode *right;

public:
    ContactNode(string nm, string ph)
    {
        name = nm;
        phoneNumber = ph;
        left = NULL;
        right = NULL;
    }
};

class ContactBST
{
public:
    ContactNode *root;
    map<char, bool> mp;

public:
    ContactBST()
    {
        root = NULL;

        for (int i = 0; i < 27; i++)
        {
            char alpha = i + 97;
            mp[alpha] = true;
        }
    }
    bool isEmpty()
    {
        return root == NULL;
    }

    void resetMp()
    {

        for (int i = 0; i < 27; i++)
        {
            char alpha = i + 97;
            mp[alpha] = true;
        }
    }
    ContactNode *insertHelper(ContactNode *root, string name, string phoneNumber)
    {

        if (root == NULL)
        {
            return new ContactNode(name, phoneNumber);
        }
        else if (tolower(name[0]) < tolower(root->name[0]))
        {
            root->left = insertHelper(root->left, name, phoneNumber);
        }
        else
        {
            root->right = insertHelper(root->right, name, phoneNumber);
        }
        return root;
    }
    void insert(string name, string phoneNumber)
    {
        root = insertHelper(root, name, phoneNumber);
    }

    ContactNode *preOrderHelper(ContactNode *node) // root - left -right
    {

        if (node != NULL)
        {
            if (mp[node->name[0]])
            {
                char ch = toupper(node->name[0]);
                cout << "----------------" << ch << "----" << ch << "-----" << ch << "-----------------" << endl;
                mp[node->name[0]] = false;
            }

            cout << "Name: " << node->name << ", Phone Number: " << node->phoneNumber << endl;
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }

        return node;
    }
    void preOrder()
    {
        inOrderHelper(root);
    }

    ContactNode *inOrderHelper(ContactNode *node) // left - root - right
    {

        if (node != NULL)
        {
            inOrderHelper(node->left);
            if (mp[node->name[0]])
            {
               
                char ch = toupper(node->name[0]);
                cout << "----------------" << ch << "----" << ch << "-----" << ch << "-----------------" << endl;
                mp[node->name[0]] = false;
            }
            
            cout << "Name: " << node->name << ", Phone Number: " << node->phoneNumber << endl;
            inOrderHelper(node->right);
        }

        return node;
    }
    void inOrder()
    {
        inOrderHelper(root);
    }

    ContactNode *postOrderHelper(ContactNode *node) // left - right - root
    {

        if (node != NULL)
        {
            if (mp[node->name[0]])
            {
                char ch = toupper(node->name[0]);
                cout << "----------------" << ch << "----" << ch << "-----" << ch << "-----------------" << endl;
                mp[node->name[0]] = false;
            }
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << "Name: " << node->name << ", Phone Number: " << node->phoneNumber << endl;
        }

        return node;
    }
    void postOrder()
    {
        postOrderHelper(root);
    }

    ContactNode *rightRootLeftHelper(ContactNode *node)
    {

        if (node != NULL)
        {

            if (mp[node->name[0]])
            {

                rightRootLeftHelper(node->right);
                char ch = toupper(node->name[0]);
                cout << "----------------" << ch << "----" << ch << "-----" << ch << "-----------------" << endl;
                mp[node->name[0]] = false;
            }

            cout << "Name: " << node->name << ", Phone Number: " << node->phoneNumber << endl;
            rightRootLeftHelper(node->left);
        }

        return node;
    }
    void rightRootLef()
    {
        rightRootLeftHelper(root);
    }

    ContactNode *searchHelper(ContactNode *node, string name)
    {

        if (node == NULL)
        {
            cout << "NOT FOUND !" << endl;
            system("pause");
            system("cls");
            return node;
        }
        else if (node->name == name)
        {
            cout << "Name : " << node->name << " Phone: " << node->phoneNumber << endl;
            system("pause");
            system("cls");
            return node;
        }

        if (tolower(name[0]) < tolower(node->name[0]))
        {
            return searchHelper(node->left, name);
        }
        else
        {
            return searchHelper(node->right, name);
        }
    }
    ContactNode *search(string name)
    {
        return searchHelper(root, name);
    }

    void deleteAllContacts()
    {
        deleteAllContactsHelper(root);
        root = nullptr; // Reset the root pointer after deleting all nodes
    }

public:
    // Recursive helper function to delete all contacts
    void deleteAllContactsHelper(ContactNode *node)
    {
        if (node != nullptr)
        {
            deleteAllContactsHelper(node->left);
            deleteAllContactsHelper(node->right);
            delete node;
        }
    }
    ContactNode *removeHelper(ContactNode *node, string name)
    {
        // Base case: If the node is null, return null
        if (node == nullptr)
        {
            return nullptr;
        }

        if (name < node->name)
        {
            node->left = removeHelper(node->left, name);
        }

        else if (name > node->name)
        {
            node->right = removeHelper(node->right, name);
        }

        else
        {

            if (node->left == nullptr)
            {
                ContactNode *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                ContactNode *temp = node->left;
                delete node;
                return temp;
            }

            ContactNode *successor = minNode(node->right);

            node->name = successor->name;
            node->phoneNumber = successor->phoneNumber;

            node->right = removeHelper(node->right, successor->name);
        }
        return node;
    }
    void remove(string name)
    {
        root = removeHelper(root, name);
    }

    ContactNode *minNode(ContactNode *node)
    {
        ContactNode *current = node;
        while (current && current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }

    void update(string name, string newPhoneNumber)
    {
        ContactNode *node = search(name);
        if (node != NULL)
        {
            node->phoneNumber = newPhoneNumber;
            cout << "Contact updated successfully." << endl;
        }
        else
        {
            cout << "Contact not found." << endl;
        }
    }
    void saveToFile(string filename)
    {
        ofstream outFile(filename);
        saveHelper(outFile, root);
        outFile.close();
    }

    // Helper function to recursively save contacts to a file
    void saveHelper(ofstream &outFile, ContactNode *node)
    {
        if (node != nullptr)
        {
            saveHelper(outFile, node->left);
            outFile << node->name << " " << node->phoneNumber << endl;
            saveHelper(outFile, node->right);
        }
    }
    void collectContactsByFirstCharacterHelper(ContactNode *node, char firstChar, vector<ContactNode *> &contacts)
    {
        if (node != nullptr)
        {
            // If the current node's name starts with the specified character
            if (node->name[0] == firstChar)
            {
                contacts.push_back(node);
            }
            // Recursively search the left subtree
            collectContactsByFirstCharacterHelper(node->left, firstChar, contacts);
            // Recursively search the right subtree
            collectContactsByFirstCharacterHelper(node->right, firstChar, contacts);
        }
    }
    void displayContactsByFirstCharacter(char firstChar)
    {
        // Output message to let the user know what's happening
        cout << "________Contacts with names starting with '" << firstChar << "':________\n"
             << endl;
        vector<ContactNode *> contacts;
        // Call the recursive helper function to collect contacts
        collectContactsByFirstCharacterHelper(root, firstChar, contacts);
        // Display the contacts found
        if (contacts.empty())
        {
            cout << "No contacts found with names starting with '" << firstChar << "'\n"
                 << endl;
        }
        else
        {
            for (const auto &contact : contacts)
            {
                cout << "Name: " << contact->name << ", Phone Number: " << contact->phoneNumber << "\n"
                     << endl;
            }
        }
    }
};

int main()
{

    ContactBST contacts;

    // contacts.insert("ali", "111");
    // contacts.insert("mohamed", "222");
    // contacts.insert("girgis", "333");
    // contacts.insert("fahd", "444");
    // contacts.insert("patrick", "555");
    // contacts.insert("tony", "666");
    // contacts.insert("abdo", "777");
    // contacts.insert("kero", "888");
    // contacts.insert("mina", "999");
    // contacts.preOrder();
    // cout << "$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    // contacts.rightRootLef();

    ifstream inFile("contacts.txt");
    if (inFile.is_open())
    {
        string name, phoneNumber;
        while (inFile >> name >> phoneNumber)
        {
            contacts.insert(name, phoneNumber);
        }
        inFile.close();
    }

a:
    cout << "---------------Contact Management System---------------" << endl;
    cout << "1. Add Contact\n"
         << endl;
    cout << "2. Delete Contact\n"
         << endl;
    cout << "3. Update Contact\n"
         << endl;
    cout << "4. View All Contacts\n"
         << endl;
    cout << "5. Save Contacts\n"
         << endl;
    cout << "6. Search for number\n"
         << endl;
    cout << "7. Delete All\n"
         << endl;
    cout << "8. Search by letter\n"
         << endl;
    cout << "9. Exit\n"
         << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {

        string name, phoneNumber, lowerName = "";
        cout << "Enter contact name: ";
        cin >> name;
        for (char c : name)
            lowerName += tolower(c);
        cout << "Enter contact phone number: ";
        cin >> phoneNumber;
        contacts.insert(lowerName, phoneNumber);
        system("cls");
        cout << "Contact added successfully." << endl;
        lowerName = "";
        system("cls");
        cout << "Pres any key " << endl;
        system("pause");
        goto a;
    }
    case 2:
    {
        // Delete Contact
        string nameToDelete;
        cout << "Enter name of contact to delete: ";
        cin >> nameToDelete;
        contacts.remove(nameToDelete);
        system("cls");
        cout << "Pres any key " << endl;
        system("pause");
        goto a;
    }
    case 3:
    {
        // Update Contact
        string nameToUpdate, newPhoneNumber;
        cout << "Enter name of contact to update: ";
        cin >> nameToUpdate;
        cout << "Enter new phone number: ";
        cin >> newPhoneNumber;
        contacts.update(nameToUpdate, newPhoneNumber);
        system("cls");
        cout << "Pres any key " << endl;
        system("pause");
        goto a;
    }
    case 4:
    {
    // View All Contacts
    case4:

        int choise;
        cout << "____1)FROM A->Z" << endl;
        cout << "____2)From Z->A" << endl;
        cin >> choice;
        cout << "All Contacts:" << endl;
        switch (choice)
        {
        case 1:
        {
            contacts.preOrder();
            contacts.resetMp();
            cout
                << "\n";
            break;
        }

        case 2:
        {

            contacts.rightRootLef();
            contacts.resetMp();
        }

        default:
        {
            cout << " ENVALID OPTION TRY AGAIN" << endl;
            system("pause");
            system("cls");
            goto a;
        }
        }
    }
    case 5:
    {
        // Save Contacts
        contacts.saveToFile("contacts.txt");
        cout << "Contacts saved to file." << endl;
        cout << "Contacts saved to file." << endl;
        system("pause");
        system("cls");
        goto a;
    }
    case 6:
    {
        string nm;
        cout << "_____Search for number by Name______\n"
             << endl;
        cout << "Enter Name :";
        cin >> nm;
        contacts.search(nm);
        system("pause");
        system("cls");
        goto a;
    }
    case 7:
    {

        char choice;
        cout << "\nDo you want to delete all contacts? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
        {
            contacts.deleteAllContacts();
            cout << "All contacts have been deleted." << endl;
            system("pause");
            system("cls");
            goto a;
        }
        else
        {
            cout << "\nOperation canceled. Contacts remain unchanged." << endl;
            system("pause");
            system("cls");
            goto a;
        }
    }

    case 8:
    {
        system("cls");
        char firstChar;
        cout << "Enter the first character of the name to search for: ";
        cin >> firstChar;
        contacts.displayContactsByFirstCharacter(firstChar);
        system("pause");
        system("cls");

        goto a;
    }
    case 9:
    {

        cout << "Exiting program." << endl;
        return 0;
    }
    default:
    {
        cout << "Invalid choice!" << endl;
        system("pause");
        system("cls");
        goto a;
    }

        return 0;
    }
}