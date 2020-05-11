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
        int positiveReview;
        int negativeReview;
        int p;
        int n;
        int kPositve;
        int kNegative;
        double returnProbability(std::string, int label);

    public:
        NaiveBayesClassifier(std::string); //constructor is used for training
        void insert(std::string, int);
        int hash(std::string);
        void test(std::string);

        void print(){
            for(int i =0; i < size; i++){
                for (std::list<Label>::iterator it = entries[i].begin(); it != entries[i].end(); ++it){
                   std::cout<< (it)->word << " " << (it)->positiveCount <<  " " << (it)->negativeCount << "\n";
                }
               // std::cout << "__________________________________________________________\n";
            }
        }

};
#endif
