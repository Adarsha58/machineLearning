#ifndef NaiveBayesClassifier_H
#define NaiveBayesClassifier_H
#include <list>

struct label{
    string 
}
class NaiveBayesClassifier{
    private:
        const int size = 43;
        std::list<Integer*> *entries;

    public:
        NaiveBayesClassifier();
        void insert(Integer*);
        int deleteElement(int, bool);
        int look(int);
        void lookup(int);
        int hash(int value){
            if(value < 0)
                return (value % 43) + 43;
            return value % 43;
        }
        void print();
};
#endif
