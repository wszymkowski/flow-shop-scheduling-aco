#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <bits/stdc++.h>
#include <iomanip>
#include <chrono>

using namespace std;

struct Task {
    int op1_time;
    int op2_time;
    int op1_machine;
    int op2_machine;
};

////////////// Parameters /////////////
int cycles = 100;
int ants = 100;
int tau = 20;
int break_time = 10;
int maintenance_time = 10;
int maintenance_period = 30;

double Q = 10;
double rho = 0.5;
int chance = 5;


///////////// GLOBAL //////////////
vector<int> m1_operations_final,m1_start_final,m1_end_final,m1_time_final;
vector<int> m2_operations_final,m2_start_final,m2_end_final,m2_time_final;
string instance_id;
int task_count;
vector<Task*> task_vector;
vector<int> candidates;
vector<double> candidatesF;

double feromone_sum=0;
double feromone[1000][1000];
double deltaFeromone[1000][1000];




///////////// Functions //////////////

void printMatrix(double matrix[1000][1000]){
    for(int i=0; i<task_count*2; i++){
        for(int j=0; j<task_count*2; j++){
            if(matrix[i][j] == 0){
                cout << "----" << " ";
            }else{
                cout << fixed << setprecision(2) << matrix[i][j] <<" ";
            }
        }
        cout << endl;
    }
    cout << "#########################################" << endl;
}

void printOutVector(vector <int> &data){        //funkcja printujaca zawartosc wektora
    for(int i=0; i<data.size(); i++){
        cout << fixed <<data[i] << "\t";
    }
    cout <<endl;
}

void zeroFeromoneMatrix(){
    for(int i=0;i<task_count*2; i++){
        for(int j=0;j<task_count*2; j++){
            feromone[i][j]=0;
            deltaFeromone[i][j]=0;
        }
    }
}

void load_file(string file_name){
    ifstream file;
    string line;
    file.open(file_name);

    getline(file,line);
    cout << "Instance Id: " << line << endl;
    instance_id=line;

    getline(file,line);
    cout << "Number of tasks: " << line <<endl;
    task_count = stoi(line);

    while(!file.eof()){
        getline(file, line);

        if(line ==  "**** EOF ****"){
            break;
        }

        vector<int> array;
        replace(line.begin(),line.end(),';',' ');
        stringstream ss(line);
        int temp;
        while(ss >> temp){
            array.push_back(temp);
        }
        Task *task = new Task;
        task ->op1_time = array[0];
        task ->op2_time = array[1];
        task ->op1_machine = array[2];
        task ->op2_machine = array[3];

        task_vector.push_back(task);
        array.clear();
    }
    file.close();
}

int selectFirstVertex(){
    int first = 2*(rand()%task_count);  //wybierz losowa parzysta operacje - bedzie to op1
    return first;
}

bool findInVector(int target,vector<int> visited){
    for(int i=0;i<visited.size();i++){
        if(visited[i]==target){
            return true;
        }
    }
    return false;
}

void createCandidates(vector<int> visited){
    for(int i=0;i<task_count*2;i++){
        if(i%2==0){
            if(!findInVector(i,visited)){
                candidates.push_back(i);
                candidatesF.push_back(feromone[visited.back()][i]);
                feromone_sum = feromone_sum+feromone[visited.back()][i];
            }
        }else{
            if(findInVector(i-1,visited) && !findInVector(i,visited)){
                candidates.push_back(i);
                candidatesF.push_back(feromone[visited.back()][i]);
                feromone_sum = feromone_sum+feromone[visited.back()][i];
            }
        }
    }
}

int selectNextVertex(int current, vector<int> visited){
    if(feromone_sum == 0 || (rand() % chance) == 1){
        int r=rand() % candidates.size();
        return r;
    }else{
        double r = (double)rand() / RAND_MAX * feromone_sum;
        double s = 0;
        for(int i=0; i<candidatesF.size(); i++){
            s=s+candidatesF[i];
            if(r<=s){
                return i;
            }
        }
        return candidates.size()-1;
    }
}

int countTime(vector<int> visited, bool save){
    vector<int> m1_operations, m1_start, m1_end, m1_time;
    vector<int> m2_operations, m2_start, m2_end, m2_time;

    int* op2_ready_times=new int[task_count];
    for(int i=0;i<task_count;i++){
        op2_ready_times[i]=0;
    }

    int length1 = 0, length2 = 0, start_time = 0, end_time = 0;
    int check_tau1 = 0, check_tau2 = 0;
    bool tau_ready_time = false;

    for(int i=0; i<visited.size(); i++){
        int time = 0, ready_time = 0, machine = 0;


        if(visited[i]%2 == 1){
            time = task_vector[visited[i]/2]->op2_time;
            machine = task_vector[visited[i]/2]->op2_machine;
            ready_time = op2_ready_times[visited[i]/2];
        }else{
            time = task_vector[visited[i]/2]->op1_time;
            machine = task_vector[visited[i]/2]->op1_machine;
        }

        if(machine == 1){
            start_time = length1;
            length1 = length1 + time;
            end_time = length1;
            check_tau1 = check_tau1 + time;
        }else{
            if(length2 < ready_time){

                start_time = ready_time;
                length2 = ready_time + time;
                end_time = length2;
                check_tau2 = check_tau2 + (ready_time-check_tau2);
                check_tau2 = check_tau2 + time;
                tau_ready_time = true;
            }else{
                start_time = length2;
                length2 = length2 + time;
                end_time = length2;
                check_tau2 = check_tau2 + time;
            }
        }

        if(check_tau1 > tau){
            m1_operations.push_back(-1);
            m1_time.push_back(break_time);
            m1_start.push_back(start_time);
            m1_end.push_back(start_time+break_time);
            end_time = end_time + break_time;
            start_time = start_time+break_time;
            length1 = length1 + break_time;

            check_tau1 = end_time - start_time;
        }else if(check_tau2 > tau){
            if(tau_ready_time){
                m2_operations.push_back(-1);
                m2_time.push_back((break_time));
                m2_start.push_back(ready_time - break_time);
                m2_end.push_back(ready_time);
                length2 = length2 + break_time;
                tau_ready_time = false;
                check_tau2 = end_time - start_time;
            }else {
                m2_operations.push_back(-1);
                m2_time.push_back((break_time));
                m2_start.push_back(start_time);
                m2_end.push_back(start_time + break_time);
                end_time = end_time + break_time;
                start_time = start_time + break_time;
                length2 = length2 + break_time;
                check_tau2 = end_time - start_time;
            }

        }
        if(machine == 1){
            m1_operations.push_back(visited[i]);
            m1_start.push_back(start_time);
            m1_end.push_back(end_time);
            m1_time.push_back(end_time-start_time);
        }else{
            m2_operations.push_back(visited[i]);
            m2_start.push_back(start_time);
            m2_end.push_back(end_time);
            m2_time.push_back(end_time-start_time);
        }

        if(visited[i]%2==0){                                //potrzebne do sprawdzania czy op1 zakonczyla sie zanim rozpocznie sie op2
            op2_ready_times[visited[i]/2]=end_time;
        }
    }
    if(save){
        m1_operations_final=m1_operations;
        m1_start_final=m1_start;
        m1_end_final=m1_end;
        m1_time_final = m1_time;

        m2_operations_final=m2_operations;
        m2_start_final=m2_start;
        m2_end_final=m2_end;
        m2_time_final = m2_time;
    }
    return max(m2_end.back(),m1_end.back());
}

void makeChangesToDeltaFeromone(vector<int> visited, int length, float multiplier ){       //multiplier = e
    int current = visited[0];
    int next;
    for(int i=1; i<visited.size(); i++){
        next = visited[i];
        deltaFeromone[current][next] = deltaFeromone[current][next] + ((Q/length) * multiplier);
        current = next;
    }
}

void makeChangesToFeromone(){
    for(int i=0; i<2*task_count; i++){
        for(int j=0; j<2*task_count; j++){
            feromone[i][j] = (rho * feromone[i][j]) + deltaFeromone[i][j];
            deltaFeromone[i][j] = 0;
        }
    }
}

int main() {
    srand(time(NULL));
    zeroFeromoneMatrix();
    string file_name;
    cout << "------------ACO for task scheduling------------" << endl;
    cout << "Enter file name: ";
    cin >> file_name;
    load_file(file_name);

    int operation_count = task_count * 2;
    int bestInGlobal = std::numeric_limits<int>::max();
    vector <int> bestVisitedGlobal;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i=0; i<cycles; i++){
        int bestInCycle = std::numeric_limits<int>::max();
        vector <int> bestVisitedInCycle;
        for(int j=0; j<ants; j++){
            vector<int> visitedVertexes;
            int currentVertex = -1;
            while(visitedVertexes.size()<operation_count){
                if(currentVertex == -1){
                    currentVertex = selectFirstVertex();
                    visitedVertexes.push_back(currentVertex);
                }else{
                    createCandidates(visitedVertexes);
                    currentVertex = selectNextVertex(currentVertex,visitedVertexes);
                    visitedVertexes.push_back(candidates[currentVertex]);

                    feromone_sum = 0;
                    candidates.clear();
                    candidatesF.clear();
                }
            }
            int currentLength = countTime(visitedVertexes,false);
            if(currentLength <= bestInCycle){
                bestInCycle = currentLength;
                bestVisitedInCycle = visitedVertexes;
            }
            makeChangesToDeltaFeromone(visitedVertexes, currentLength, 2);
            visitedVertexes.clear();
        }
        makeChangesToDeltaFeromone(bestVisitedInCycle, bestInCycle, 4);
        if(bestInCycle < bestInGlobal){
            bestInGlobal = bestInCycle;
            bestVisitedGlobal = bestVisitedInCycle;
        }
        makeChangesToDeltaFeromone(bestVisitedGlobal, bestInGlobal, 10);
        makeChangesToFeromone();
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    int final_result=countTime(bestVisitedGlobal,true);

    /*cout<<"--------------------- M1 --------------------"<<endl;
    cout<<"operations   : ";printOutVector(m1_operations_final); cout<<endl;
    cout<<"times        : ";printOutVector(m1_time_final);cout<<endl;
    cout<<"start times  : ";printOutVector(m1_start_final);cout<<endl;
    cout<<"end times    : ";printOutVector(m1_end_final);cout<<endl;
    cout<<"--------------------- M2 --------------------"<<endl;
    cout<<"operations   : ";printOutVector(m2_operations_final);cout<<endl;
    cout<<"times        : ";printOutVector(m2_time_final);cout<<endl;
    cout<<"start times  : ";printOutVector(m2_start_final);cout<<endl;
    cout<<"end times    : ";printOutVector(m2_end_final);cout<<endl;*/

    cout<<"Length: "<<final_result<<" | Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    cout<<"done";
    return 0;
}
