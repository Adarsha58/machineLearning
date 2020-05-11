all: NaiveBayesClassifier.sh

NaiveBayesClassifier.sh: NaiveBayesClassifier.cpp
	g++ -o NaiveBayesClassifier.sh NaiveBayesClassifier.cpp

