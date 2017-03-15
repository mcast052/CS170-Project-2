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
#include <list> 
#include <algorithm> 

using namespace std; 

long double nearest_neighbor(vector<long double> p, vector< vector< long double> > t) { 
    long double minDis = 0.0; long double classification = 0.0; 
    for(unsigned int i = 0; i < t.at(0).size(); i++) { 
        long double dis = 0.0; 
        for(unsigned int j = 1; j < t.size(); j++) { dis += pow(t.at(j).at(i) - p.at(j), 2); } 
        if(i == 0) {minDis = dis;} 
        else if(dis <= minDis) { minDis = dis; classification = t.at(0).at(i); } 
    } 
    return classification; 
} 

float validator(vector< vector< long double> > features) { 
    vector < vector <long double>> instance_subset; 
    vector<long double> instanceCheck; 
    int numCorrect = 0; 
    for(unsigned int i = 0; i < features.at(0).size(); i++) { 
        for(unsigned int j = 0; j < features.size(); j++) {
            vector<long double> tmp = features.at(j); 
            instanceCheck.push_back(tmp.at(i));
            tmp.erase(tmp.begin() + i);
            instance_subset.push_back(tmp); 
        }
        if( nearest_neighbor(instanceCheck, instance_subset) == instanceCheck.at(0)) { numCorrect++;}
        instance_subset.clear(); 
    	instanceCheck.clear();
    } 

    return ((float)numCorrect / (float)features.at(0).size()) * 100; 
} 

void forward_Selection(vector<vector<long double>> training_set, unsigned int numFeatures) { 
    vector<unsigned int> bestFeatures;
    vector<unsigned int> localBest;  
    float accuracy, max = 0.0;  
    
    for(unsigned int i = 1; i <= numFeatures; i++) {
        float localmax = 0.0; 
        vector<unsigned int> tmpMax; 
        for(unsigned int j = 1; j <= numFeatures; j++) {
            vector<vector<long double>> tmp; 
            vector<unsigned int> tmpLocal; 
            tmp.push_back(training_set.at(0)); 
            tmpLocal = localBest; 
            
            for(unsigned int x = 0; x < bestFeatures.size(); x++) { tmp.push_back( training_set.at(bestFeatures.at(x)) ); } 
                
            if(find(tmpLocal.begin(), tmpLocal.end(), j) == tmpLocal.end()) {
                tmp.push_back(training_set.at(j)); 
                tmpLocal.push_back(j); 
                cout << "Testing "; 
                for(unsigned int i = 0; i < tmpLocal.size(); i++) {cout << tmpLocal.at(i) << " "; } 
                accuracy = validator(tmp); 
                cout << "Accuracy: " << accuracy << endl; 
                if(accuracy > localmax) { localmax = accuracy; tmpMax = tmpLocal; } 
            }   
        } 
        localBest = tmpMax; 
        cout << "The best feature set is: "; 
        for(unsigned int i = 0; i < localBest.size(); i++) { cout << localBest.at(i) << " "; } 
        cout << "with an accuracy of " << localmax << "%" << endl << endl; 
        
        if(localmax > max) { bestFeatures = localBest; max = localmax; }
        else if(localmax < max) { cout << "Warning! Accuracy is decreasing. Continuing check in case of local maxima." << endl; } 
    } 
    cout << endl << "Searched finished." << endl; 
    cout << "The final best feature set is: "; 
    for(unsigned int i = 0; i < bestFeatures.size(); i++) { cout << bestFeatures.at(i) << " "; } 
    cout << "with an accuracy of " << max << "%" << endl; 
} 

void backward_Selection(vector<vector<long double>> training_set, unsigned int numFeatures) { 
    vector<unsigned int> bestFeatures(numFeatures); 
    std::iota(bestFeatures.begin(), bestFeatures.end(), 1); 
    vector<unsigned int> localBest = bestFeatures; 
    float accuracy, max = 0.0; 
    
    for(unsigned int i = 1; i <= numFeatures; i++) {
        float localmax = 0.0; 
        vector<unsigned int> tmpMax; 
        for(unsigned int j = 1; j <= numFeatures; j++) {
            vector<vector<long double>> tmp; 
            vector<unsigned int> tmpLocal; 
            tmp.push_back(training_set.at(0)); 
            tmpLocal = localBest; 
            
            for(unsigned int x = 0; x < tmpLocal.size(); x++) { tmp.push_back( training_set.at(tmpLocal.at(x)) ); } 
            vector<unsigned int>::iterator it = find(tmpLocal.begin(), tmpLocal.end(), j);     
            if(it != tmpLocal.end()) {
                unsigned int index = *it; 
                tmpLocal.erase(it);
                tmp.erase(tmp.begin() + index); 
                /*cout << "TMP: " << endl; 
                for(unsigned int i = 0; i < tmp.at(0).size(); i++) { 
                    for(unsigned int j = 0; j < tmp.size(); j++) { 
                        cout << tmp.at(j).at(i) << " "; 
                    } 
                    cout << endl; 
                } */
                cout << "Testing "; 
                for(unsigned int i = 0; i < tmpLocal.size(); i++) {cout << tmpLocal.at(i) << " "; } 
                accuracy = validator(tmp); 
                cout << "Accuracy: " << accuracy << endl; 
                if(accuracy > localmax) { localmax = accuracy; tmpMax = tmpLocal; } 
            }   
        } 
        localBest = tmpMax; 
        cout << "The best feature set is: "; 
        for(unsigned int i = 0; i < localBest.size(); i++) { cout << localBest.at(i) << " "; } 
        cout << "with an accuracy of " << localmax << "%" << endl << endl; 
        
        if(localmax > max) { bestFeatures = localBest; max = localmax; }
        else if(localmax < max) { cout << "Warning! Accuracy is decreasing. Continuing check in case of local maxima." << endl; } 
    } 
    cout << endl << "Searched finished." << endl; 
    cout << "The final best feature set is: "; 
    for(unsigned int i = 0; i < bestFeatures.size(); i++) { cout << bestFeatures.at(i) << " "; } 
    cout << "with an accuracy of " << max << "%" << endl; 
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
    vector <long double> features; 
    string line; 
    
    getline(fin, line); 
    std::stringstream sstream(line); 
    string feature; 
    while(sstream >> feature) { 
        features.push_back(stold(feature)); 
        training_set.push_back(features); 
        features.clear(); 
    } 

    while( getline(fin, line) ) { 
        std::stringstream sstream(line); 
        string feature; 
        for(unsigned int i = 0; i < training_set.size(); i++) { 
            if( sstream >> feature) { training_set.at(i).push_back(stold(feature)); }  
        } 
    } 
    
    fin.close(); 
	unsigned int numFeatures = training_set.size() - 1; 
	cout << "Number of instances: " << training_set.at(0).size() << endl; 
	cout << "Number of features: " << numFeatures << endl; 
	cout << "Running nearest neighbor with all " << numFeatures << " features, using \"leaving-one-out\" evaluation, I get an accuracy of "; 
	cout << validator(training_set) << "%" << endl; 
	
	if(algorithm == "1") { forward_Selection(training_set, numFeatures); }  
	else { backward_Selection(training_set, numFeatures); } 
    return 0; 
} 
