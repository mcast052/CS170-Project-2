/* 

Melissa Castillo, mcast052, 861157259 
CS170 Project 2: Nearest Neighbor Classifier using Forward and Backward Selection

*/

#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector>
#include <string> 
#include <cmath> 

using namespace std; 

long double nearest_neighbor(vector<long double> p, vector< vector< long double> > t) { 
    long double minDis = 0.0;
    long double dis = 0.0;  
    long double classification = 0.0; 
    for(unsigned int i = 0; i < t.size(); i++) { 
        for(unsigned int j = 1; j < t.at(i).size(); j++) { dis += pow(t.at(i).at(j) - p.at(j), 2); } 
        if(i == 0) {minDis = dis;} 
        else if(dis < minDis) { minDis = dis; classification = t.at(i).at(0); } 
        dis = 0.0; 
    } 
    return classification; 
} 

void validator(vector< vector< long double> > features) { 
    vector < vector < long double > > instance_subset; 
    int numCorrect = 0; 
    for(unsigned int i = 0; i < features.size(); i++) { 
            instance_subset = features; 
            instance_subset.erase(instance_subset.begin() + i); 
            if( nearest_neighbor(features.at(i), instance_subset) == features.at(i).at(0)) {numCorrect++;}
    } 
    cout << "Accuracy is " << numCorrect << "/" << features.size() << endl; 
} 

int main() {
    
    //GUI
    string filename, algorithm; 
    cout << "Welcome to Melissa Castillo's Feature Selection Algorithm." << endl; 
    cout << "Type in the name of the file to test: " << endl; 
    cin >> filename; 
    cout << "Type the number of the algorithm you want to run." << endl; 
    cout << "1) Forward Selection \n2) Backward Elimination" << endl; 
    cin >> algorithm; 
	
	ifstream fin; 
    fin.open(filename.c_str());
    if(!fin.is_open())
    {
        cout << "Error opening file." << endl; 
        return -1; 
    }
    
	vector< vector<long double> > training_set;
    vector < long double > instance; 
    string line; 
    
    while( getline(fin, line) ) { 
        std::stringstream sstream(line); 
        string feature; 
        while(sstream >> feature) { instance.push_back(stold(feature)); } 
        training_set.push_back(instance); instance.clear(); 
    } 
    
    fin.close(); 
	
	cout << "Testing input" << endl; 
	cout << "Number of instances: " << training_set.size() << endl; 
	cout << "Number of features: " << training_set.at(0).size() - 1 << endl; 
	
	validator(training_set); 
	
    return 0; 
} 
