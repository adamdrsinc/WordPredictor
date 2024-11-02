#include "WordTree.hpp"

void WordTree::add(std::string word)
{
    // If word is empty, ignore it
    if (word.size() <= 0)
    {
        return;
    }

    if (!std::all_of(word.begin(), word.end(), [](unsigned char c)
                     {
                         return std::isalpha(c);
                     }))
    {
        return;
    }

    for (size_t i = 0; i < word.length(); i++)
    {
        char c = word[i];
        word[i] = tolower(c);
    }

    size_t idx = getLetterIndex(word[0]);
    // std::shared_ptr<TreeNode> currentNode = tree[idx];

    std::shared_ptr<TreeNode> currentNode;

    if (tree[idx] != nullptr)
    {
        currentNode = tree[idx];
    }
    else
    {
        tree[idx] = std::make_shared<TreeNode>();
        currentNode = tree[idx];
    }

    for (size_t i = 1; i <= word.size(); i++)
    {
        if (i == word.size())
        {
            currentNode->endOfWord = true;
            break;
        }

        // apple
        // a p p l e
        // 0 1 2 3 4
        //   1 2 3 4

        size_t idx = getLetterIndex(word[i]);

        if (currentNode->children[idx] != nullptr)
        {
            currentNode = currentNode->children[idx];
        }
        else
        {
            currentNode->children[idx] = std::make_shared<TreeNode>();
            currentNode = currentNode->children[idx];
        }
    }
}

size_t WordTree::getLetterIndex(const unsigned char letter)
{
    if (letter >= 'a' && letter <= 'z')
    {
        return static_cast<size_t>(letter - 'a');
    }

    return -1;
}

bool WordTree::find(std::string word)
{
    if (word.length() <= 0)
    {
        return false;
    }

    if (!std::all_of(word.begin(), word.end(), [](unsigned char c)
                     {
                         return std::isalpha(c);
                     }))
    {
        return false;
    }

    for (size_t i = 0; i < word.length(); i++)
    {
        char c = word[i];
        word[i] = tolower(c);
    }

    auto currentNode = tree[getLetterIndex(word[0])];
    if (currentNode == nullptr)
    {
        return false;
    }

    if (word.size() == 1)
    {
        if (currentNode->endOfWord)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    for (size_t i = 1; i < word.size(); i++)
    {
        size_t idx = getLetterIndex(word[i]);

        if (i == word.size() - 1)
        {
            if (currentNode->children[idx] != nullptr)
            {
                if (currentNode->children[idx]->endOfWord)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        if (currentNode->children[idx] != nullptr)
        {
            currentNode = currentNode->children[idx];
        }
        else
        {
            return false;
        }
    }

    return false;
}

// barss
std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{

    if (partial.size() <= 0)
    {
        return {};
    }

    if (!std::all_of(partial.begin(), partial.end(), [](unsigned char c)
                     {
                         return std::isalpha(c);
                     }))
    {
        return {};
    }

    if (tree.size() <= 0)
    {
        return {};
    }

    for (size_t i = 0; i < partial.size(); i++)
    {
        partial[i] = tolower(partial[i]);
    }

    auto currentNode = tree[getLetterIndex(partial[0])];

    if (currentNode == nullptr)
    {
        return {};
    }

    const std::uint8_t alphChar{ 26 };

    for (size_t i = 1; i < partial.size(); i++)
    {
        size_t idx = getLetterIndex(partial[i]);
        currentNode = currentNode->children[idx];
        if (currentNode == nullptr)
        {
            return {};
        }
    }

    std::queue<std::pair<std::shared_ptr<TreeNode>, std::string>> nodeQueue;
    std::vector<std::string> predictedWords;

    nodeQueue.push(std::make_pair(currentNode, partial));

    while (!nodeQueue.empty() && predictedWords.size() < howMany)
    {
        auto theNode = nodeQueue.front().first;
        auto theWord = nodeQueue.front().second;

        nodeQueue.pop();

        if (theNode->endOfWord)
        {
            if (theWord != partial)
            {
                predictedWords.emplace_back(theWord);
            }
        }

        for (size_t i = 0; i < alphChar; i++)
        {
            if (theNode->children[i] != nullptr)
            {
                nodeQueue.push(std::make_pair(theNode->children[i], theWord + static_cast<char>(i + 'a')));
            }
        }
    }

    return predictedWords;
}

std::size_t WordTree::size()
{
    size_t count = 0;

    for (int i = 0; i < 26; i++)
    {
        if (tree[i] != nullptr)
        {
            count += recursiveSize(tree[i]);
        }
    }

    return count;
}

std::size_t WordTree::recursiveSize(std::shared_ptr<TreeNode> node)
{

    if (node == nullptr)
    {
        return 0;
    }

    size_t count = 0;

    if (node->endOfWord)
    {
        count++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != nullptr)
        {
            count += recursiveSize(node->children[i]);
        }
    }

    return count;
}