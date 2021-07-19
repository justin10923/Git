#include "minigit.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

using namespace std;

miniGit::miniGit() //initialize data member
{
    headDouble = NULL;
}



void miniGit::displayMenu() //menu
{
    cout << "1. Initialize git" << endl;
    cout << "2. Add files to current commit" << endl;
    cout << "3. Remove files from current commit" << endl;
    cout << "4. Commit changes" << endl;
    cout << "5. Access version" << endl;
    cout << "6. Quit MiniGit" << endl;
}

void miniGit::setHeadDouble(doublyNode *input) //single use case for initialization of DLL and SLL
{
    headDouble = input;
    headDouble->next = NULL;
    headDouble->previous = NULL;
    headDouble->head = NULL;
    headDouble->commitNumber = 0;
}

bool miniGit::fileExists(string name) //tests if file exists in directory for adding
{
    ifstream test(name);
    return test.good();
}

bool miniGit::fileExistsInList(string name, doublyNode* check) //check to see if you already added the file to commit list before
{
    if(check->head == NULL)
    {
        return false;
    }
    singlyNode* temp = check->head;
    while(temp != NULL)
    {
        if(temp->filename == name)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}


doublyNode* miniGit::getHeadNode() //returns head node of DLL
{
    return headDouble;
}

void miniGit::addFile(string fileName, int version, doublyNode *&commitDouble) //function that adds file to commit list, adds SLL
/* 
First, it orients a test node at the correct spot in the singly linked list according to 
which doubly linked node the user is currently on.
Then, it creates a new filename using the version number.
*/
{
    singlyNode *current = commitDouble->head;
    if(commitDouble->head == NULL)
    {
        singlyNode* added1 = new singlyNode;
        commitDouble->head = added1;
        added1->next = NULL;
        added1->version = 0;
        added1->filename = fileName;
        return;
    }
    while(current->next != NULL)
    {
        current = current->next;
    }
    singlyNode *added = new singlyNode;
    current->next = added;
    added->next = NULL;
    added->version = 0;
    added->filename = fileName;
}

bool miniGit::testRemoval(string name, doublyNode* check) //makes sure the file you want to remove exists in commit list
{
    singlyNode* temp = check->head;
    while(temp != NULL)
    {
        if(temp->filename == name)
        {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

void miniGit::removeFile(string filename, singlyNode* &head) //removes a node from the singly linked list and commit list
{
    singlyNode* temp;
    if(head->filename == filename)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    else
    {
        singlyNode* previous = head;
        temp = head->next;
        while(temp != NULL)
        {
            if(temp->filename == filename)
            {
                previous->next = temp->next;
                if(temp->next == NULL)
                {
                    temp->next = previous;
                    delete temp;
                }
                return;
            }
            previous = temp;
            temp = temp->next;
        }
    }
}

void miniGit::commitFile(string fileName, int version) //commits a file in the SLL 
{
    string newFileName;
    for(int i = 0; i < fileName.length(); i++)
    {
        if(fileName[i] == '.')
        {
            newFileName = fileName.substr(0,i) + "_0" + to_string(version) + ".txt";
            break;
        }
    }
    ifstream  inputFile(fileName);
    ofstream  output("git/" + newFileName);
    output << inputFile.rdbuf();
}

bool miniGit::fileExistsinGit(string name, int commit) //ensures file you would like to commit exists in commit list
{
    commit--;
    string newFileName;
    for(int i = 0; i < name.length(); i++)
    {
        if(name[i] == '.')
        {
            newFileName = name.substr(0,i) + "_0" + to_string(commit) + ".txt";
            break;
        }
    }
    newFileName = "git/" + newFileName;
    ifstream test(newFileName);
    if(test.fail())
    {
        return false;
    }
    return true;
}

bool miniGit::fileChanged(string native, int commit) //this will send true if file was not changed
{
    commit--; //since commit # was updated last commit for this file, this function is only called if file exists
     string newFileName;
    for(int i = 0; i < native.length(); i++)
    {
        if(native[i] == '.')
        {
            newFileName = native.substr(0,i) + "_0" + to_string(commit) + ".txt";
            break;
        }
    }
    newFileName = "git/" + newFileName;
    ifstream f1(native, std::ifstream::binary|std::ifstream::ate);//opens file1, binary and ate used to solve issue
    ifstream f2(newFileName, std::ifstream::binary|std::ifstream::ate);//opens file2, binary and ate used to solve issue
    if (f1.tellg() != f2.tellg()) 
    {
        return false; //are the file sizes the same? We can automatically tell the file is changed if not.
    }
    f1.seekg(0, ifstream::beg); //we set the position at 0 for comparison
    f2.seekg(0, ifstream::beg); //we set the position at 0 for comparison
    return equal(istreambuf_iterator<char>(f1.rdbuf()), istreambuf_iterator<char>(),istreambuf_iterator<char>(f2.rdbuf()));
    //did some research on iterators, found this line of code  
    // which is a single-pass input iterator that reads successive characters from
    // the std::basic_streambuf object for which it was constructed.
}

doublyNode* miniGit::getNodeCommit(int commit) //not currently used anywhere
{
    doublyNode *curr = headDouble;
    while(true)
    {
        if(curr->commitNumber == commit)
        {
            return curr;
        }
        curr = curr->next;
    }
}

string miniGit::turnToRegular(string filename) //not currently used anywhere
{
    string newFileName;
    for(int i = 0; i < filename.length(); i++)
    {
        if(filename[i] == '_')
        {
            newFileName = filename.substr(0,i) + ".txt";
            break;
        }
    }
    return newFileName;
}

void miniGit::checkout(int commit) //checkout feature for any commit
{
    doublyNode *current = headDouble;
    while(true)
    {
        if(current->commitNumber == commit)
        {
            break;
        }
        current = current->next;
    }
    singlyNode *current1 = current->head;
    string temp , newFileName;
    bool inDirectory;
    while(current1 != NULL)
    {
        temp = current1->filename;
        for(int i = 0; i < temp.length(); i++)
        {
            if(temp[i] == '.')
            {
            newFileName = temp.substr(0,i) + "_0" + to_string(commit) + ".txt";
            break;
            }
        }
        inDirectory = fileExists(current1->filename);
        if(inDirectory == true)
        {
            newFileName = "git/" + newFileName;
            ifstream  inputFile(newFileName);
            ofstream  output(current1->filename);
            output << inputFile.rdbuf();
        }
        current1 = current1->next;
    }
}

bool miniGit::safeGuardCheckoutChange(int commit) //not currently used anywhere
{
    doublyNode* check = headDouble;
    while(true)
    {
        if(check->commitNumber == commit)
        {
            break;
        }
        check = check->next;
    }
    singlyNode* temp = check->head;
    while(temp != NULL);
    {
        if(!fileChanged(temp->filename, commit))
        {
            return false;
        }
        temp = temp->next;
    }
    return true;
}