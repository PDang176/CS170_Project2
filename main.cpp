#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

vector<int> nearest_neighbor_accuracy(){
    vector<int> ans;

    return ans;
}

void reading_data(string name, vector<vector<double>>& data){
    ifstream file(name);

    string line;

    if(file.is_open()){ // Checking if the file is open
        while(getline(file, line)){ // Looping through each instance
            string s;        
            vector<double> temp;
            istringstream iss(line);
            while(iss >> s){ // Looping through each feature
                temp.push_back(stod(s));
            }
            data.push_back(temp);
            temp.clear();
        }
    }
    else{
        cout << "Error opening file" << endl;
    }
}

int main(){
    vector<vector<double>> largeData;
    vector<vector<double>> smallData;

    reading_data("Large_data.txt", largeData);
    reading_data("Small_data.txt", smallData);

    

    return 0;
}