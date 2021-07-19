#include <iostream>
#include <filesystem>
#pragma ONCE

using namespace std;


struct singlyNode
{
    string filename;
    int version;
    singlyNode* next;
};

struct doublyNode
{
    int commitNumber;
    singlyNode* head;
    doublyNode* previous;
    doublyNode* next;
};

class miniGit
{
    public: 

    miniGit();

    //displays and initializers
    void displayMenu(); //standard display for driver
    void setHeadDouble(doublyNode *input); //solely for initialization in option 1

    //add or delete
    bool fileExists(string name); //solely for adding a file, will check if the file exists in current directory
    bool fileExistsInList(string name, doublyNode *check); //tests to see if the file you are trying to add has already been added
    bool testRemoval(string name, doublyNode* check); //tests if file exists in git directory for removal
    void addFile(string fileName, int version, doublyNode *&commitDouble); //function to add a file, passed by refrence since we append the linked list
    void removeFile(string filename, singlyNode* &head); //removes a file from git
    

    //commit
    void commitFile(string filename, int version);
    bool fileExistsinGit(string name, int commit);
    bool fileChanged(string native, int commit);
    
    //checkout
    void checkout(int commit);
    string turnToRegular(string filename);
    bool safeGuardCheckoutChange(int commit);

    doublyNode* getHeadNode(); //returns headDouble
    doublyNode* getNodeCommit(int commit); //returns a specific file you would like to access

    private:
    doublyNode *headDouble;
};


