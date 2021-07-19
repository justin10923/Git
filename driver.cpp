#include "minigit.h"
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

int main()
{
    miniGit current;
     //initialize the class
    int option = 0;
    int commit = 0;
    while(true)
    {
        current.displayMenu();
        cin >> option;
        if(cin.fail())
        {
            cout << "Not a number" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //used for infinite loop with char error
            continue;
        }
        switch(option)
        {
            case 1: 
            {
                cout << "New git Initialized. Commit Identifier is 0. " << endl;
                doublyNode *init = new doublyNode;
                singlyNode *curr = new singlyNode;
                current.setHeadDouble(init);
                filesystem::create_directory("git");
                break;
            }
            case 2:
            {
                string filename;
                doublyNode *check = current.getHeadNode();
                while(check->next != NULL)
                {
                    check = check ->next;
                }
                while(true)
                {
                    cout << "Enter a filename: " << endl;
                    cin >> filename;
                    if(!current.fileExists(filename))
                    {
                        cout << "File is not in current directory" << endl;
                        continue;
                    }
                    else if (current.fileExistsInList(filename, check))
                    {
                        cout << "You have already added this file to the .git directory" << endl;
                        continue;
                    }
                    else
                    {
                        current.addFile(filename, commit, check);
                        cout << filename << " was added to commit list." << endl;
                        break;
                    }   
                }
                break;
            }
            case 3:
            {
                doublyNode* check = current.getHeadNode();
                while(check->next != NULL)
                {
                    check = check->next;
                }
                string remove;
                while(true)
                {
                    cout << "Which file would you like to remove from current commit?" << endl;
                    cin >> remove;
                    if(current.testRemoval(remove, check))
                    {
                        cout << "This file does not currently exist in your commit list. " << endl;
                        continue;
                    }
                    else
                    {
                        cout << remove << " was successfully removed" << endl;
                        current.removeFile(remove,check->head);
                        break;
                    }
                }
                break;
            }
            case 4: // to do: make sure that upon commiting the program checks if file is already in git, if it is check if it has been changed.
            {
                doublyNode* check = current.getHeadNode(); //receives head node from class
                while(check->next != NULL) //iterates to current node
                {
                    check = check->next;
                }
                singlyNode* temp = check->head; //sets pointer to head of SLL   

                while(temp != NULL) //we are iterating through commit list
                {
                    if(check->previous != NULL && current.fileExistsinGit(temp->filename, temp->version)) //fixed error with seg fault when attempting
                    // to access previous NULL
                    {
                        if(current.fileChanged(temp->filename, temp->version))
                        {
                            temp = temp->next;
                            continue; //skips iteration if file from previous commit was not changed
                        }
                    }
                    cout << "committing " << temp->filename << "..." << endl;
                    current.commitFile(temp->filename, temp->version);
                    cout << temp->version << endl;
                    temp->version++;
                    temp = temp->next;
                }
                commit++;
                doublyNode *added = new doublyNode; //creates new doubly node
                added->head = check->head;
                singlyNode* debug = added->head;
                added->previous = check;
                added->next = NULL;
                added->commitNumber = commit;
                check->next = added;
                cout << "Changes commited. New commit number is " << commit << endl;
                break;
            }
            case 5:
            {
                string str;
                cout << "Warning: Restoring a different commit will erase current changes made." << endl;
                cout << "Additionally, the miniGit program will end upon checking out a" << endl;
                cout << " old commit, as you cannot make more changes which differ from most recent commit." << endl;
                cout << "Please enter version you would like to access." << endl;
                int commitNumber;
                cin >> commitNumber;
                current.checkout(commitNumber);
                cout << "Commit number " << commitNumber << " has been checked out. Program Exited." << endl;
                filesystem::remove_all("git");
                return 0;
            }
            case 6:
            {
                filesystem::remove_all("git");
                cout << "Program exited. " << endl;
                return 0;
            }
            default:
            {
                cout << "Not a valid choice." << endl;
                break;
            }
        }
    }
}