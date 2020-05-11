#include <iostream>
#include <sstream>
#include <fstream>
#include "NaiveBayesClassifier.h"
#include <math.h>
#include <chrono>

using namespace std;

NaiveBayesClassifier::NaiveBayesClassifier(string fileName){
    
    ifstream in(fileName);
    string line;
    negativeReview = 0;
    positiveReview = 0;
    kNegative = 0;
    kPositve = 0;
    p = 0;
    n = 0;

    auto t1 = std::chrono::high_resolution_clock::now();
    if(in.is_open()){
        
        entries = new list<Label>[size];
        while (getline(in, line)){
        
            int label= line[line.size()-1] - '0';
            

            istringstream ss(line.substr(0, line.size()-3));
            string token;
            if(label == 0){
                n++;
            }else{
                p++;
            }

            while(getline(ss, token, ' '))
                    this->insert(token, label);
           
        }
        in.close();
        
    } else{
        cerr << "Can't open the file"<< endl;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout<< "Trianing time: "<< duration<<endl; 
}


void NaiveBayesClassifier::insert(string word, int label){
    int index = this->hash(word);
    for (list<Label>::iterator it = entries[index].begin(); it != entries[index].end(); ++it){
        if((it)-> word == word){
            if(label == 1){
                if(it->positiveCount == 0) kPositve++;
                (it->positiveCount)++;
                positiveReview++;
            } else{
                if(it->negativeCount == 0) kNegative++;
                (it->negativeCount)++;
                negativeReview++;
            }
            return;
        }
    }
    if(label == 0){
        Label l(word, 0, 1);
        entries[index].push_front(l);
        kNegative ++;
        negativeReview++;
      
    }else{
        Label l(word, 1, 0);
        entries[index].push_front(l);
        kPositve++;
        positiveReview++;
    }
}

int NaiveBayesClassifier::hash(string word){
    unsigned int hashValue = 1;
    for (int i = 0; i < word.size(); i++){
        hashValue = hashValue* word[i];
    }
    return hashValue % this->size; 
}

double NaiveBayesClassifier::returnProbability(string word, int label){
    int index = this->hash(word);

    for (list<Label>::iterator it = entries[index].begin(); it != entries[index].end(); ++it){
        if((it)-> word == word){
            if(label == 0){
                return (it->negativeCount + 1.0)/ (negativeReview + kPositve);
            }else{
                return (it->positiveCount + 1.0)/ (positiveReview + kNegative);
            }
        }
    }
    return 0;
}

void NaiveBayesClassifier::test(string fileName){
    double accuracy = 0;
    double totalReviews = 0.0;
    ifstream in(fileName);
    string line;
  
    double pPositiveReview = p * 1.0 / (p + n); 
    double pNegativeReview = n * 1.0 / (p + n); 

    if(in.is_open()){
        while (getline(in, line)){
            totalReviews++;
            double probPos = log(pPositiveReview); 
            double probNeg = log(pNegativeReview);

            int label = line[line.size()-1] - '0';
            
            istringstream ss(line.substr(0, line.size()-3));
            string token;


           while(getline(ss, token, ' ')){
                    probPos += log(returnProbability(token, 1));
                    probNeg += log(returnProbability(token, 0));
            
            }
           
            if(probNeg > probPos){
                if(label == 0) accuracy ++;
                //cout << 0;
            }else{
                if(label ==1) accuracy ++;
               // cout<< 1;
            }
        }
        in.close();
    } else{
        cerr << "Can't open the file"<< endl;
    }
    cout<< "accuracy " <<accuracy<<endl;
    cout<< "totalReviews " << totalReviews <<endl;
    accuracy = accuracy/ totalReviews;
    cout<< "Accuary: "<< accuracy<<endl;
}

int main(int argc, char** argv){
    if(argc != 3){
        cerr << "Include both your training and testing data"<< endl;
    }
    NaiveBayesClassifier n(argv[1]);
    n.test(argv[2]);
   // n.print();
}