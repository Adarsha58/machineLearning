#include <iostream>
#include <sstream>
#include <fstream>
#include "NaiveBayesClassifier.h"
#include <math.h>
#include <chrono>
#include <unordered_set>
#include <iomanip>

using namespace std;

NaiveBayesClassifier::NaiveBayesClassifier(string fileName){
    
    ifstream in(fileName);
    string line;
    totalPositiveReviewWords = 0;
    totalNegativeReviewWords = 0;
    kPositve = 0;
    kNegative = 0;
    totalPositiveReviews = 0;
    totalNegativeReviews = 0;

    if(in.is_open()){
        
        entries = new list<Label>[size];
        while (getline(in, line)){
        
            int label= line[line.size()-1] - '0';
            

            istringstream ss(line.substr(0, line.size()-3));
            string token;
            if(label == 0){
               totalPositiveReviews++;
            }else{
                totalNegativeReviews++;
            }
           
            string tmp;
            getline(ss, tmp, ' ');
            while(getline(ss, token, ' ')){
                string bigram = tmp + token;
                this->insert(bigram, label);
                tmp = token;
            }
           
        }
        in.close();
        
    } else{
        cerr << "Can't open the file"<< endl;
    } 
}


void NaiveBayesClassifier::insert(string word, int label){
    int index = this->hash(word);
    for (list<Label>::iterator it = entries[index].begin(); it != entries[index].end(); ++it){
        if((it)-> word == word){
            if(label == 1){
                if(it->positiveCount == 0) kPositve++;
                (it->positiveCount)++;
                totalPositiveReviewWords++;

            } else{
                if(it->negativeCount == 0) kNegative++;
                (it->negativeCount)++;
                totalNegativeReviewWords++;
    
            }
            return;
        }
    }
    if(label == 0){
        Label l(word, 0, 1);
        entries[index].push_front(l);
        kNegative ++;
        totalNegativeReviewWords++;
      
    }else{
        Label l(word, 1, 0);
        entries[index].push_front(l);
        kPositve++;
        totalPositiveReviewWords++;
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
    double a = 0.995;

    for (list<Label>::iterator it = entries[index].begin(); it != entries[index].end(); ++it){
        if((it)-> word == word){
            if(label == 0){
                return (it->negativeCount + a)/ (totalNegativeReviewWords + a *kPositve);
            }else{
                return (it->positiveCount + a)/ (totalPositiveReviewWords + a* kNegative);
            }
        }
    }

    if(label == 1)
        return a/(totalPositiveReviewWords + a* kPositve);
    else 
        return a/(totalNegativeReviewWords + a* kNegative);
}

double NaiveBayesClassifier::test(string fileName){
    double accuracy = 0;
    double totalReviews = 0.0;
    ifstream in(fileName);
    string line;
  
    double pPositiveReview = totalPositiveReviews * 1.0 / (totalPositiveReviews + totalNegativeReviews); 
    double pNegativeReview = 1 - pPositiveReview;

    if(in.is_open()){
        while (getline(in, line)){
            totalReviews++;
            double probPos = log(pPositiveReview); 
            double probNeg = log(pNegativeReview);

            int label = line[line.size()-1] - '0';
            
            istringstream ss(line.substr(0, line.size()-3));
            string token;
            string tmp;
            getline(ss, tmp, ' ');

        
            while(getline(ss, token, ' ')){
                string bigram = tmp + token;
                probPos += log(returnProbability(bigram, 1));
                probNeg += log(returnProbability(bigram, 0));
                tmp = token;
            }
        
        
            if(probNeg > probPos){
                if (fileName != "training.txt") cout<<0<<endl;
                if(label == 0) {
                     accuracy ++;  
                }
            }else{
                if (fileName != "training.txt") cout<<1<<endl;
                if(label ==1){
                    accuracy ++;
                }
            }
        }
        in.close();
    } else{
        cerr << "Can't open the file"<< endl;
    }
    return accuracy/ totalReviews;
}

int main(int argc, char** argv){
    if(argc != 3){
        cerr << "Include both your training and testing data"<< endl;
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    NaiveBayesClassifier n(argv[1]);
    auto t2 = std::chrono::high_resolution_clock::now();
    double durationTraining = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count() * 0.000001;
    
    t1 = std::chrono::high_resolution_clock::now();
    double accuracy = n.test(argv[2]);
    t2 = std::chrono::high_resolution_clock::now();
    double durationTesting = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count() * 0.000001;
    
    cout<< (int) durationTraining << " seconds (training)\n";
    cout<< (int) durationTesting << " seconds (labeling)\n";
    
    cout<< fixed << setprecision(3) << n.test(argv[1]) << " (training)\n";
    cout<< fixed << setprecision(3) <<  accuracy << " (testing)\n";
}