#ifndef USERMANAGER_H_INCLUDED
#define USERMANAGER_H_INCLUDED

#include <bits/stdc++.h>
#include<fstream>
#include<cstring>

using namespace std;
class User;

class Node
{
public :
    string key;
    int priority;
    Node *leftNode;
    Node *rightNode;
    User *user;
};
class User
{
public:

    string userName;
    string firstName;
    string lastName;
    string Email;
    string FriendBST;
    User * next;
    User * previous;
    Node* friendNode;


    Node*Add( Node*nodePointer,string key, User* user);
    Node*Delete(Node* nodePointer,string key);
    User* Find(Node* root, string key);
    void printFriends(Node* node);
    Node* setTreap(string userName);

};
////////////////////////////////////////////////////////////////////////
//Linked list

User* head;
User* tail;
void insertList()
{
    ifstream thefile("all-users.in");
    ifstream thefile2("all-users-relations.in");
    string username;
    string firstname;
    string lastname;
    string email;
    string friendBST;

//Traverse the users file to set all users in the linked list
    while(thefile>>username>>firstname>>lastname>>email)
    {
        bool flag=true;
        User * new_User=new User();
        User*curr=head;
        //Avoid Duplicate userName
        while(curr!=NULL)
        {
            if(username==curr->userName)
            {
                flag=false;
            }
            curr=curr->next;
        }
        if(flag==true)
        {

            new_User->userName=username;
        }
        else
        {
            new_User->userName="invalid";
        }

        new_User->firstName=firstname;
        new_User->lastName=lastname;
        new_User->Email=email;
        if(tail == NULL)
        {
            head=new_User;
            tail=new_User;
        }
        else
        {
            new_User->previous=tail;
            new_User->previous->next=new_User;
            tail=new_User;
        }
    }
    //Traverse the users linked list and set their friends
    User* curr = new User();
    curr = head;
    while(curr != NULL)
    {
        curr->friendNode = curr->setTreap(curr->userName);
        curr=curr->next;
    }

}

//Travers the linked list and print all user's information
void print()
{
    User*curr=head;
    while(curr != NULL)
    {
        cout<<curr->userName<<" "<<curr->firstName<<" "<<curr->lastName<<" "<<curr->Email<<" "<<curr->FriendBST<<endl<<endl;
        curr=curr->next;
    }
}
//Print specific user
void printUser(User* curr)
{
    if ( curr == NULL)
    {
        cout << "NULL\n";
    }
    else
    {
        cout<<curr->userName<<" "<<curr->firstName<<" "<<curr->lastName<<" "<<curr->Email<<" "<<curr->FriendBST<<endl<<endl;

    }
}
//Get a user using his name
User* getUserByName(string name)
{
    User*curr=head;
    while(curr != NULL)
    {

        int index = curr->userName.find(",");

        string userName2 = curr->userName.substr(0,index);

        if(userName2 == name)
        {
            return curr;
        }
        curr=curr->next;

    }
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Treap Functions

Node* newNode (User *user1,string key)
{
    Node *node=new Node;
    node->key=key;
    node->priority= rand()%100;
    node->leftNode=NULL;
    node->rightNode=NULL;
    node->user = user1;
    return node;
}
Node* Rotate_left(Node* node)
{
    Node * rightchild=node->rightNode;
    Node * rightleftchild = rightchild->leftNode;
    rightchild->leftNode=node;
    node->rightNode=rightleftchild;
    return rightchild;
}
Node* Rotate_right(Node *node)
{
    Node * leftchild =node->leftNode;
    Node * leftrightchild =leftchild->rightNode;
    leftchild->rightNode=node;
    node->leftNode=leftrightchild;
    return leftchild;
}

Node* User::Add( Node*nodePointer,string key, User* user)
{
    if (nodePointer==NULL)
    {
        return newNode(user,key);
    }
    if (nodePointer->key<key)
    {
        nodePointer->rightNode=Add(nodePointer->rightNode,key,user);
        if (nodePointer->rightNode->priority >  nodePointer->priority)
        {
            nodePointer= Rotate_left(nodePointer);
        }

    }
    else
    {
        nodePointer->leftNode= Add(nodePointer->leftNode,key,user);
        if (nodePointer->leftNode->priority >  nodePointer->priority)
        {
            nodePointer=Rotate_right(nodePointer);
        }
    }
    return nodePointer;

}

Node* User::Delete(Node* nodePointer,string key)
{
    if(nodePointer==NULL)
    {
        return nodePointer;
    }



    if (nodePointer->key>key)
    {

        nodePointer->leftNode= Delete(nodePointer->leftNode,key);

    }
    else if (nodePointer->key < key)
    {
        nodePointer->rightNode= Delete(nodePointer->rightNode,key);

    }

    else if (nodePointer->rightNode==NULL)
    {
        Node * n=nodePointer->leftNode;
        delete (nodePointer);
        nodePointer=n;
    }
    else if (nodePointer->leftNode==NULL)
    {
        Node * n=nodePointer->rightNode;
        delete (nodePointer);
        nodePointer=n;
    }

    else if (nodePointer->leftNode->priority <nodePointer->rightNode->priority)
    {
        nodePointer = Rotate_left(nodePointer);
        nodePointer->leftNode = Delete(nodePointer->leftNode, key);
    }
    else
    {
        nodePointer = Rotate_right(nodePointer);
        nodePointer->rightNode = Delete(nodePointer->rightNode, key);
    }

    return nodePointer;
}


User* User::Find(Node* root, string key)
{
    User* user;
    // Base Cases: root is null or key is present at root
    if (root == NULL)
    {
        user = NULL;
        return user;
    }

    if (root->key == key)
    {
        user = getUserByName(key);
        return user;
    }
    // Key is greater than root's key
    if (root->key < key)
    {

        return Find(root->rightNode, key);
    }

    // Key is smaller than root's key
    if(root->key > key)
    {

        return Find(root->leftNode, key);
    }

}

//Print friends in-order
void User::printFriends(Node* node)
{
    if (node==NULL) return;
    else
    {
        printFriends(node->leftNode);
        string nodeKey;

        User* user;
        int i = node->key.find(",");
        if (i == -1)
        {
            nodeKey = node->key;
        }
        else
        {
            nodeKey = node->key.substr(0,i);
        }
        user = getUserByName(nodeKey);

        string userLastName;
        int index = user->lastName.find(",");
        userLastName = user->lastName.substr(0,index);


        cout<< node->key << ", " << user->firstName << " " << userLastName << endl;

        if (node->leftNode)
        {
            user = getUserByName(node->leftNode->key);
        }
        else if (node->rightNode)
        {
            user = getUserByName(node->rightNode->key);
        }
        printFriends(node->rightNode);

    }

}

//Read friends from all-users-relations file

Node* User::setTreap(string userName)
{

    fstream file;
    Node *root=NULL;
    file.open("all-users-relations.in",ios::in);
    if (file)
    {
        string relation ;
        while(getline(file,relation))
        {
            string s1,s2;

            int before,after;
            for(int i=0; i<relation.size(); i++)
            {
                if (relation[i]==',')
                {
                    before=i-1;
                    after=i+2;
                    break;
                }
            }
            for(int i=0; i<=before; i++)s1+=relation[i];
            for(int i=after; i<relation.size(); i++)s2+=relation[i];


            User* user;
            user = getUserByName(userName);

            int index = userName.find(",");
            string userName2 = userName.substr(0,index);

            if (s1==userName2)
            {
                root=Add(root,s2,user);
            }
            else if (s2==userName2)
            {
                root=Add(root,s1,user);
            }
        }
        file.close();
    }
    return root;
}

#endif // USERMANAGER_H_INCLUDED
