#ifndef NaiveBayesClassifier_H
#define NaiveBayesClassifier_H
#include <string>
#include <list>

struct label{
    std::string word; 
    int positiveCount;
    int negativeCount;
    label(std::string w, int p = 0, int = 0): word(w), positiveCount(p), negativeCount(n){}
};
class NaiveBayesClassifier{
    private:
        int size;
        std::list<label>* entries;
        int positiveReview;
        int negativeReveiw;
        int trainingTime; 

    public:
        NaiveBayesClassifier(std::string); //default constructor is used for training
        NaiveBayesClassifier();
        void insert(label);
        int hash(std::string);
        void test(std::string);

};
#endif
