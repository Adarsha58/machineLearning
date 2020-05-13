#ifndef NaiveBayesClassifier_H
#define NaiveBayesClassifier_H
#include <string>
#include <list>
using namespace std;

struct Label{
    std::string word; 
    int positiveCount;
    int negativeCount;
    double tf;
    int docsWithWord;
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
        void insert(std::string, int, bool);
        int hash(std::string);
        double returnProbability(std::string, int label, std::string);
        double test(std::string);
        double tf(std::string line, std:: string word){
            double freq = 0;
            double maxFreq = 0;
            istringstream ss(line.substr(0, line.size()-3));
            string token;
            string tmp;
            getline(ss, tmp, ' ');
            while(getline(ss, token, ' ')){
                string bigram = tmp + token;
                maxFreq++;
                if(bigram == word) freq ++;
                tmp = token;
            }
            return 0.5 + 0.5* freq / maxFreq;
        
        }

};
#endif
