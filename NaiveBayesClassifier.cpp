#include <iostream>
#include <sstream>
#include <fstream>
#include "NaiveBayesClassifier.h"

using namespace std;


NaiveBayesClassifier::NaiveBayesClassifier()
{
    size = 0;
    positiveReview = 0;
    negativeReveiw = 0;
    trainingTime = 0;
    entries = 0;

}

NaiveBayesClassifier::NaiveBayesClassifier(string fileName){
    ifstream in(fileName);
    string line;
    if(in.is_open()){
        while (getline(in, line)){
            cout<< line<<endl;
        }
        in.close();
    }
}

void NaiveBayesClassifier::test(string fileName){
    cout<< "Testing:"<< fileName<< endl;
}

int main(int argc, char** argv){
    if(argc != 3){
        cerr << "Include both your training and testing data"<< endl;
    }
    NaiveBayesClassifier n(argv[1]);
    n.test(argv[2]);
}