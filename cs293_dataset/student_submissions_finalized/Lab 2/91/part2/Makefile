all: planner dictionaryTestSelf

dictionaryTestSelf: dictionaryTestSelf.cpp dictionary.tpp.hpp
	g++ -o dictionaryTestSelf dictionaryTestSelf.cpp

planner: planner.cpp planner.hpp dictionary.tpp.hpp
	g++ -o planner planner.cpp
