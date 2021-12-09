#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <cfloat>

using namespace std;

double calculate_distance(vector<double> const & v1, vector<double> const & v2){ // Distance formula between v1 and v2
    double sum = 0;
    for(int i = 0; i < v1.size(), i < v2.size(); i++){
        sum += pow(v1[i] - v2[i], 2);
    }

    return sqrt(sum);
}

double nearest_neighbor_accuracy(vector<vector<double>> const & data){
    int correct = 0; // Number of correct classifications

    for(int i = 0; i < data.size(); i++){
        double classification = data[i][0]; // Class for data at i
        vector<double> features = {data[i].begin() + 1, data[i].end()}; // Features for data at i

        double nearest_dist = DBL_MAX; // Nearest distance to data at i
        int nearest_loc; // Location of the nearest data instance
        double nearest_class; // Class of the nearest data instance

        for(int j = 0; j < data.size(); j++){
            if(j != i){ // Checking every other data instance besides itself
                double j_classification = data[j][0]; // Class for data at j
                vector<double> j_features = {data[j].begin() + 1, data[j].end()}; // Features for data at j
                double distance = calculate_distance(features, j_features); // Calculating distance between i and j

                if(distance < nearest_dist){ // If the new distance is the closest then replace
                    nearest_dist = distance;
                    nearest_loc = j;
                    nearest_class = j_classification;
                }
            }
        }

        
    }

    return (double)(correct / data.size());
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

    double temp = nearest_neighbor_accuracy(smallData);

    return 0;
}