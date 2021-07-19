# Git Version Control MiniSystem
Git Version Control system Built in C++.
Instructions:

This is a readme.txt for a native git on Windows 10.

# Compiling

Simply use g++ -std=c++17 driver.cpp minigit.cpp to compile.
Run executable to bring up CLI.

# Features and Functionality:

This git system has been tested and works for .txt files. Simply add any file
to commit list and then upon committing that file will permanently be in commit
list until user chooses to remove it. Each file that is commited will be subsequently
copied into new versions upon additional commits if the user changes the file. If no
changes were made to a file in the commit list that has a previous version, the git
ignores it from the commit. Easily access any old commits using the checkout feature.
Once the checkout feature is used, the add, remove, and commit options will be disabled.
The program ends if the user explicity chooses to or if the checkout option has been selected.

Three sample files have been provided:
1. test.txt
2. test2.txt
3. test3.txt

# Instructions:
1. Initialization
Simply enter the command to initialize the git and a new directory will appear in workspace.
No user input required. For all other operations to work, this option is mandatory.
2. Adding files
Add any file to git! The condiitions are: file must exist in current directory and file must not 
have been added to git previously during any commit. If either of these two conditions fails, the user
will recieve an error message to enter a valid filename.
3. Removing files
The way this miniGit works is the linked list of file nodes is copied to subsequent commits, so the user 
must remove any file they would not like to continue commiting. This remove file feature can be used at any
point for any commit as long as the file currently exists in the git directory.
4. Committing changes
The user can commit changes upon adding files to the commit list. The user is given the name of the first commit as 0,
and any commit after that is simply 1, 2, 3 and so on. The git system will commit any and all files added up until that point.
Any deleted files from this add list will not be committed. Additionally, the git system checks to see if changes have been made 
to a previously committed file, if there are none then the git DOES NOT create a new version. Any previously absent files will
be added to git. File version nomenclature is rudimentary, with file versions updating based on their native version and NOT the 
commit number that they were committed in. The user must keep track of which files are in which commit for using the checkout feature.
5. checkout
The checkout feature restores any commit number to current files in workspace. The name of the files is not updated, but the changes
will immediately replace the current version, losing any saved work that was not present in the most recent commit. The program
exits at this point as no new changes can be made once a checkout has taken place; the git will not allow the "add, remove, and commit" 
options if the current file version does not match the most recent commit after checkout.
6. exit
Exits program. Deletes Git.

# Sample Test Run:
1
*git initialized in workspace*
2
test.txt
2
test2.txt
4
*commit with test.txt and test2.txt added*
2
test3.txt
3 
test2.txt
4
*only test3.txt is added to commit 1 as test.txt was unchanged*
*user now makes change to test.txt*
4
*commit 2 contains solely test.txt as it was the only file that was changed
from previous commit and no new files were added*
*user makes another change to test.txt*
5
0
*user checkouts 0, restoring version of test.txt before changes were made*
*no changes were made to test2.txt and test3.txt so they remain the same*
6
*user exits program. Git is deleted*


