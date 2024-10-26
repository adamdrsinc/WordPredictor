#pragma once

#include <string>
#include <vector>
#include <array>
#include <memory>

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

public:
	void add(std::string word);
	//bool find(std::string word);

	//Given the partial word, returns up to howMany predicted words
	//std::vector<std::string> predict(std::string partial, std::uint8_t howMany);

	//Returns the number of words in the tree
	std::size_t size();

};

/*

std::string word = "abc";

std::array<std::shared_ptr<TreeNode>, 26> tree;

[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10... 25]

firstLetter = word[0]; //g
index = firstLetter - 97;

wordWithoutLetter = word.substr(1, word.length() - 1); //bc

tree[index] = std::make_shared<TreeNode>(wordWithoutLetter);
tree[0] is now filled. This represents 'a'.

This should 


*/


