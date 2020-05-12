#ifndef NaiveBayesClassifier_H
#define NaiveBayesClassifier_H
#include <string>
#include <list>
using namespace std;

struct Label{
    std::string word; 
    int positiveCount;
    int negativeCount;
    Label(std::string w, int p = 0, int n = 0): word(w), positiveCount(p), negativeCount(n){}
};
class NaiveBayesClassifier{
    private:
        const int size = 6577;
        std::list<Label>* entries;
        int totalPositiveReviewWords;
        int totalNegativeReviewWords;
        int k;
        int totalPositiveReviews;
        int totalNegativeReviews;

    public:
        NaiveBayesClassifier(std::string); //constructor is used for training
        void insert(std::string, int);
        int hash(std::string);
        double returnProbability(std::string, int label);
        double test(std::string);
        void stopWords(std:: string &);

};
#endif
