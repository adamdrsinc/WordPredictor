#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <memory>
#include <queue>
#include <string>
#include <vector>

class TreeNode
{
  private:
  public:
    bool endOfWord = false;
    std::array<std::shared_ptr<TreeNode>, 26> children;
};

class WordTree
{
  private:
    std::array<std::shared_ptr<TreeNode>, 26> tree;

    size_t recursiveSize(std::shared_ptr<TreeNode> node);
    size_t getLetterIndex(const unsigned char letter);

  public:
    void add(std::string word);
    bool find(std::string word);
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    std::size_t size();
};
