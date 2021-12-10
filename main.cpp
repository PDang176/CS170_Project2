#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <cfloat>
#include <unordered_set>

using namespace std;

double calculate_distance(vector<double> const & v1, vector<double> const & v2){ // Distance formula between v1 and v2
    double sum = 0;
    for(int i = 0; i < v1.size(), i < v2.size(); i++){
        sum += pow(v1[i] - v2[i], 2);
    }

    return sqrt(sum);
}

/*
    params:
        data
        used features
        new feature added or removed
        forward(true) backward(false)
*/
double nearest_neighbor_accuracy(vector<vector<double>> const & data, vector<int> const & features_index, int new_feature, bool algorithm){
    int correct = 0; // Number of correct classifications

    for(int i = 0; i < data.size(); i++){
        double classification = data[i][0]; // Class for data at i
        vector<double> features; // Features for data at i
        
        for(int k = 1; k < features_index.size(); k++){ // Inserting only features we're testing
            if(features_index[k] == 1){
                if(!algorithm && k == new_feature){ // If backward eliminiation remove new_feature
                    continue;
                }
                features.push_back(data[i][k]);
            }
        }
        if(algorithm){ // If forward selection add new_feature
            features.push_back(data[i][new_feature]);
        }

        double nearest_dist = DBL_MAX; // Nearest distance to data at i
        int nearest_loc; // Location of the nearest data instance
        double nearest_class; // Class of the nearest data instance

        for(int j = 0; j < data.size(); j++){
            if(j != i){ // Checking every other data instance besides itself
                double j_classification = data[j][0]; // Class for data at j
                vector<double> j_features; // Features for data at j
                
                
                for(int k = 1; k < features_index.size(); k++){ // Inserting only features we're testing
                    if(features_index[k] == 1){
                        if(!algorithm && k == new_feature){ // If backward elimination remove new_feature
                            continue;
                        }
                        j_features.push_back(data[j][k]);
                    }
                }
                if(algorithm){ // If forward selection add new_feature
                    j_features.push_back(data[j][new_feature]);
                }

                double distance = calculate_distance(features, j_features); // Calculating distance between i and j

                if(distance < nearest_dist){ // If the new distance is the closest then replace
                    nearest_dist = distance;
                    nearest_loc = j;
                    nearest_class = j_classification;
                }
            }
        }

        if(classification == nearest_class){ // If the nearest neighbor's class matches i then it's correct
            correct++;
        }
    }

    return (double)correct / data.size();
}

void forward_selection(vector<vector<double>> const & data){
    vector<int> features(data[0].size(), 0); // Current features tested

    vector<int> best_features(data[0].size(), 0); // Best features
    double best_accuracy = 0; // Accuracy of best features

    for(int i = 1; i < data[0].size(); i++){ // Loop through all features
        int feature_to_add;
        double best_new_accuracy = 0;

        for(int j = 1; j < data[0].size(); j++){
            if(features[j] == 0){
                double accuracy = nearest_neighbor_accuracy(data, features, j, true);

                if(accuracy > best_new_accuracy){
                    best_new_accuracy = accuracy;
                    feature_to_add = j;
                }
            }
        }
        features[feature_to_add] = 1; // Adding the selected feature;
        
        if(best_new_accuracy > best_accuracy){ // Setting the top accuracy
            best_accuracy = best_new_accuracy;
            best_features = {features.begin(), features.end()};
        }
    }

    for(int i = 1; i < best_features.size(); i++){
        if(best_features[i] == 1){
            cout << i << " ";
        }
    }
    cout << "were the best features with an accuracy of " << best_accuracy << "." << endl;
}

void backward_elimination(vector<vector<double>> const & data){
    vector<int> features(data[0].size(), 1); // Current features tested

    vector<int> best_features(data[0].size(), 1); // Best features
    double best_accuracy = 0; // Accuracy of best features

    for(int i = 1; i < data[0].size(); i++){ // Loop through all features
        int feature_to_remove;
        double best_new_accuracy = 0;

        for(int j = 1; j < data[0].size(); j++){
            if(features[j] == 1){
                double accuracy = nearest_neighbor_accuracy(data, features, j, false);

                if(accuracy > best_new_accuracy){
                    best_new_accuracy = accuracy;
                    feature_to_remove = j;
                }
            }
        }
        features[feature_to_remove] = 0; // Adding the selected feature;
        
        if(best_new_accuracy > best_accuracy){ // Setting the top accuracy
            best_accuracy = best_new_accuracy;
            best_features = {features.begin(), features.end()};
        }
    }

    for(int i = 1; i < best_features.size(); i++){
        if(best_features[i] == 1){
            cout << i << " ";
        }
    }
    cout << "were the best features with an accuracy of " << best_accuracy << "." << endl;
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

int select_data(){
    int data;
    cout << "Small Data or Large Data (Type 1 or 2 respectively): ";
    cin >> data;
    while(data != 1 && data != 2){
        cout << "Invalid input. Small Data or Large Data (Type 1 or 2 respectively): ";
        cin >> data;
    }

    return data;
}

void select_algorithm(vector<vector<double>> const & smallData, vector<vector<double>> const & largeData){
    int data = select_data();
    int algorithm;
    cout << "Forward Selection or Backward Elimination (Type 1 or 2 respectively): ";
    cin >> algorithm;
    while(algorithm != 1 && algorithm != 2){
        cout << "Invalid input. Forward Selection or Backward Elimination (Type 1 or 2 respectively): ";
        cin >> algorithm;
    }

    int combined = data * 10 + algorithm;

    switch(combined){
        case 11:
            forward_selection(smallData);
            break;
        case 12:
            backward_elimination(smallData);
            break;
        case 21:
            forward_selection(largeData);
            break;
        case 22:
            backward_elimination(largeData);
            break;
        default:
            cout << "Error: Data or Algorithm does not exist." << endl;
            break;
    }
}

int main(){
    vector<vector<double>> smallData;
    vector<vector<double>> largeData;

    reading_data("Small_data61.txt", smallData);
    reading_data("Large_data.txt", largeData);

    select_algorithm(smallData, largeData);

    return 0;
}