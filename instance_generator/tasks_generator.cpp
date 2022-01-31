#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Task{
    int op1_time;
    int op2_time;
    int op1_machine;
    int op2_machine;
};

vector <Task*> task_vector;
string file_name;
int number_of_tasks;
int task_time_range;
int instance_id;

void save_to_file(){
    ofstream file;
    file.open(file_name);
    file<<"**** "<<instance_id<<" ****"<<endl;
    file<<number_of_tasks<<endl;
    for(int i=0;i<task_vector.size();i++){
        file<<task_vector[i]->op1_time<<";"<<task_vector[i]->op2_time<<";"<<task_vector[i]->op1_machine<<";"<<task_vector[i]->op2_machine<<";"<<endl;
    }
    file<<"**** EOF ****";
    file.close();

}

int main() {
    srand(time(NULL));

    cout<<"Welcome to task generator !"<<endl;
    cout<<"Name the file: ";
    cin>>file_name;
    cout<<"Input instance id: ";
    cin>>instance_id;
    cout<<"Input number of tasks: ";
    cin>>number_of_tasks;
    cout<<"Input time range for tasks. From 1 to: ";
    cin>>task_time_range;

    for(int i = 0; i<number_of_tasks; i++){
        Task *task = new Task;

        task->op1_machine = 1;
        task->op2_machine = 2;
        task->op1_time = rand()%task_time_range+1;
        task->op2_time = rand()%task_time_range+1;

        task_vector.push_back(task);
    }

    save_to_file();


    return 0;
}
