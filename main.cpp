#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

template <typename Out>
void split(const std::string& s, char delim, Out result)
{
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim))
    {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
        // Need to consume the carriage return character for some systems, if it exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
        // it will throw exception on negative values; e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(), [](unsigned char c)
                        {
                            return std::isalpha(c);
                        }))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](char c)
                           {
                               return static_cast<char>(std::tolower(c));
                           });
            wordTree->add(word);
        }
    }

    return wordTree;
}

void add(int& x, int& y)
{
    x + y;
}

void add(int x, int y)
{
    x + y;
}

int main()
{
    auto wordTree = readDictionary("dictionary.txt");

    int coords[2] = { 1, 1 };

    std::string word;

    rlutil::cls();

    while (true)
    {
        int keyPressed = rlutil::getkey();

        rlutil::cls();

        rlutil::locate(coords[0], 1);

        if (keyPressed == rlutil::KEY_BACKSPACE)
        {
            if (!word.empty())
            {
                word.pop_back();
            }
        }
        else
        {
            word.push_back(static_cast<char>(keyPressed));
        }

        std::cout << word << std::endl;

        if (word.size() > 0)
        {
            auto splitWords = split(word, ' ');

            int rows = rlutil::trows() - 4;
            std::vector<std::string> predictedWords = wordTree->predict(splitWords.back(), rows);

            std::cout << std::endl;
            std::cout << "-- Predictions --" << std::endl;

            for (auto& word : predictedWords)
            {
                std::cout << word << std::endl;
            }
        }
    }

    std::shared_ptr<int> p = std::make_shared<int>(5);
    std::unique_ptr<int> f = std::make_unique<int>(10);

    {
        std::shared_ptr<int> p2 = p;
    }

    int* arr = new int[5];

    // do what ever you want wtih arr

    delete[] arr;
}
