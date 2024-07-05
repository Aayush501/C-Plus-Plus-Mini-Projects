#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct ToDoList
{
    int id;
    string task;
};

int ID;


void banner();
void addTask();
void showTask();
int searchTask();
void deleteTask();
void updateTask();

int main(){
    system("cls");
    while(true){
        banner();
        cout<<"\n\t1. Add Task";
        cout<<"\n\t2. Show Task";
        cout<<"\n\t3. Search Task";
        cout<<"\n\t4. Delete Task";
        cout<<"\n\t5. Update Task";

        int choice;
        cout<<"\n\tEnter Choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            addTask();
            break;
        case 2:
            showTask();
            break;
        case 3:
            searchTask();
            break;
        case 4:
            deleteTask();
            break;
        case 5:
            updateTask();
            break;
        
        default:
            break;
        }
    }
    return 0;
}


void banner(){
    cout<<"_________________________________________\n";
    cout<<"\n                My TODO\n";
    cout<<"_________________________________________\n";
}


void addTask(){
    system("cls");
    banner();
    ToDoList todo;
    cout<<"Enter new task: "<<endl;
    cin.get();
    getline(cin, todo.task);
    char save;
    cout<<"Save? (y/n): ";
    cin>>save;
    if(save == 'y'){
        ID++;
        fstream fout;
        fout.open("todo.txt", ios::app);
        fout<<"\n"<<ID;
        fout<<"\n"<<todo.task;
        fout.close();

        char more;
        cout<<"Add more task? (y/n): ";
        cin>>more;
        if(more=='y'){
            addTask();
        }
        else{
            system("cls");
            cout<<"Added Successfully!"<<endl;
            return;
        }
    }
    system("cls");
}

void showTask(){
    system("cls");
    banner();
    ToDoList todo;
    fstream fin;
    fin.open("todo.txt", ios::in);
    cout<<"Task: \n";

    while(!fin.eof()){
        fin>>todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if(todo.task != ""){
            cout<<"\t"<<todo.id<<": "<<todo.task<<"\n";
        }
        else {
            cout<<"\tEmpty!"<<endl;
        }
    }
    fin.close();
    char exit;
    cout<<"Exit? (Y/N): ";
    cin>>exit;
    if(exit != 'y'){
        showTask();
    }
    system("cls");
}

int searchTask(){
    system("cls");
    banner();
    int id;
    cout<<"Enter task id: ";
    cin>>id;
    ToDoList todo;
    fstream fin("todo.txt", ios::in);
    while(!fin.eof()){
        fin>>todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if(todo.id==id){
            system("cls");
            cout<<"\t"<<todo.id<<": "<<todo.task<<"\n";
            return id;
        }
    }
    system("cls");
    cout<<"Not Found\n";
    return 0;
}

void deleteTask(){
    system("cls");
    int id = searchTask();
    if(id != 0){
        char del;
        cout<<"\tDelete? (Y/N): ";
        cin>>del;
        if(del == 'y'){
            ToDoList todo;
            fstream tempFile("temp.txt", ios::out);
            fstream fin;
            fin.open("todo.txt");
            int index=1;
            while (!fin.eof())
            {
                fin>>todo.id;
                fin.ignore();
                getline(fin, todo.task);
                if(todo.id != id){
                    tempFile << "\n" << index;
                    tempFile << "\n" << todo.task;
                    index++;
                    ID--;
                }
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            system("cls");
            cout<<"\n\tDeleted Successfully!\n";
        }
        else{
            system("cls");
            cout<<"Not Deleted!\n";
        }
    }
}

void updateTask(){
    system("cls");
    int id = searchTask();
    if(id!=0){
        char update;
        cout<<"\tUpdate? (Y/N): ";
        cin>>update;
        if(update=='y'){
            ToDoList todo;
            fstream tempFile("temp.txt", ios::out);
            fstream fin("todo.txt");
            while (!fin.eof())
            {
                fin>>todo.id;
                fin.ignore();
                getline(fin, todo.task);
                tempFile << "\n" << todo.id;
                if(todo.id != id){
                    tempFile << "\n" << todo.task;
                }
                else{
                    cout<<"\tAdd New Task: ";
                    cin.get();
                    getline(cin, todo.task);
                    tempFile << "\n" << todo.task;
                }
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            system("cls");
            cout<<"\n\tUpdated Successfully!\n";
        }
    }
}