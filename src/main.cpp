#include <iostream>
#include"UserManager.h"
using namespace std;

int main()
{

    insertList();
    User* user = new User();

all:
    cout<<"========= Welcome in FCAI App =========\nPlease type your choice:\n- To login type \"Login\".\n- To exit type \"Exit\".\n";
    string log;
    cin>>log;

    if(log == "login" || log == "Login")
    {
        cout<<"========== Hello in FCAI App ==========\n"<<"Enter your user name: ";
        string str;
        cin>>str;
        user = getUserByName(str);

        if (user == NULL)
        {
            cout << "\nNot found. Please try again.\n\n";
            goto all;
        }
        else
        {
            cout << "\nLogged in successfully. Welcome "<< str << "\nPlease enter your choice number\n\n";


            while(true)
            {
Menu:
                int choice;
                cout<<"1) List all friends.\n2) Search by user name.\n"<<
                    "3) Add friend.\n4) Remove friend.\n"<<
                    "5) People you may know.\n6) Log out.\n";

                cin>>choice;
                switch(choice)
                {
                case 1:
                {
                    cout<<"\n============= All Friends =============\n\n";
                    Node* root = new Node();
                    root = user->friendNode;
                    user->printFriends(root);
                    cout << "\n======================================\n\n";
                    break;
                }
                case 2:
                {
                    string name;
                    cout<<"\n";
                    cout << "Enter user name: ";
                    cin >> name;

                    Node* root = new Node();
                    root = user->friendNode;

                    User* newUser= new User;

                    newUser=user->Find(root, name);
                    if (newUser!=NULL)
                    {
                        cout<<newUser->userName<<" "<<newUser->firstName<<" "<<newUser->lastName<<" "<<newUser->Email<<endl;
                        cout<<"-------------------"<<"\n";
                    }
                    else
                    {
                        cout<<"Not Found"<<endl;
                    }
                    break;
                }
                case 3:
                {

                    cout<<endl;
                    string name;
                    cout << "Enter user name: ";
                    cin >> name;

                    Node* root = new Node();
                    root = user->friendNode;

                    if(user->Find(root, name)==NULL)
                    {
                        User* friendUser = new User();
                        Node* newRoot = new Node();
                        friendUser = getUserByName(name);
                        newRoot = friendUser->friendNode;

                        user->friendNode = user->Add(root, name, friendUser);

                        string newName;
                        if(user->userName.find(',')==0)
                            newName=user->userName;
                        else
                        {
                            newName=user->userName.substr(0,user->userName.find(','));
                        }
                        friendUser->friendNode = friendUser->Add(newRoot, newName, user);

                        cout<<"You are now friends"<<endl;
                        cout << "================\n";

                    }
                    else
                    {
                        cout<<"You are already friends"<<endl;
                        cout << "================\n";
                    }
                    break;
                }
                case 4:
                {
                    cout<<endl;
                    string name;
                    cout << "Enter user name: ";
                    cin >> name;
                    Node* root = new Node();
                    root = user->friendNode;

                    if(user->Find(root, name)!=NULL)
                    {
                        User* friendUser = new User();
                        Node* newRoot = new Node();
                        user->friendNode = user->Delete(root, name);

                        string newName;
                        if(user->userName.find(',')==0)
                            newName=user->userName;
                        else
                        {
                            newName=user->userName.substr(0,user->userName.find(','));
                        }
                        friendUser = getUserByName(name);
                        newRoot = friendUser->friendNode;
                        friendUser->friendNode = friendUser->Delete(newRoot,newName);
                        cout<<"Done"<<endl;

                    }
                    else
                    {
                        cout<<"you are not friends"<<endl;
                    }

                    break;
                }
                case 5:
                {
                    cout<<"\n";
                    Node* root = new Node();
                    root=user->friendNode;

                    User * curr= new User();
                    curr=head;
                    int cnt=0;
                    while(curr!=NULL)
                    {
                        if(cnt<5){
                        string newName;
                        string newName2;
                        if((curr->userName.find(',')==0)||(user->userName.find(',')==0)){
                            newName=curr->userName;
                            newName2=user->userName;
                        }
                        else
                        {
                            newName=curr->userName.substr(0,curr->userName.find(','));
                            newName2=user->userName.substr(0,user->userName.find(','));
                        }

                        if (user->Find(root,newName)==NULL && newName2!=newName)
                        {
                            string newlastName=curr->lastName.substr(0,curr->lastName.find(','));
                            cout<<newName<<","<<curr->firstName<<" "<<newlastName<<endl;
                        }
                        else{
                            cnt--;
                        }
                        curr=curr->next;
                        cnt++;
                        }
                        else{
                        break;
                        }

                    }
                    cout<<endl;


                    break;
                }
                case 6:
                {
                    cout<<"\nIf you are sure to logout --> please type \"Logout\".\nIf not --> type \"Back\".\n-\"Make sure to type the statements correctly\"-\n";
                    string wanted;
                    cin >> wanted;
                    if(wanted == "Logout" || wanted == "logout")
                    {
                        goto all;
                    }
                    else if (wanted == "Back" || wanted == "back")
                    {
                        goto Menu;
                    }
                    else
                    {
                        cout << "Wrong choice. Please try again.\n\n";
                    }
                    break;
                }
                default:
                {
                    cout << "Wrong choice. Please try again\n\n";
                }

                }

            }
        }
    }
    else if(log == "Exit" || log == "exit")
    {
        cout<<"--------------------------------\n";
        exit(0);
    }
    else
    {
        cout << "Wrong choice .Please try again\n";
        goto all;
    }
    return 0;
}

