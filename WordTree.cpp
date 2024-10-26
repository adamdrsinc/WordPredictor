#include "WordTree.hpp"

void WordTree::add(std::string word) {
	//If word is empty, ignore it
	if (word.size() <= 0)
	{
		return;
	}

	for (int i = 0; i < word.length(); i++)
	{
		char c = word[i];

		//If word contains non-alphabetic characters, ignore it
		if (!std::isalpha(c))
		{
			return;
		}

		word[i] = tolower(c);
	}


		/*
	Get array of nodes
	Check if node corresponding to letter exists
		If it does, traverse to that node
		If it doesn't, create a new node and traverse to that node
	At the end, set boolean to true
	*/

	int idx = word[0] - 97;
	std::shared_ptr<TreeNode> currentNode = tree[idx];

	if (tree[idx] == nullptr)
	{
		tree[idx] = std::make_shared<TreeNode>();
		currentNode = tree[idx];
	}


	for (int i = 1; i <= word.size(); i++)
	{
		if (i == word.size())
		{
			currentNode->children[idx] = std::make_shared<TreeNode>();
			currentNode->endOfWord = true;
			break;
		}

		int idx = word[i] - 97;

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


//bool WordTree::find(std::string word) {
//}
//
////Given the partial word, returns up to howMany predicted words
//std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany) {
//
//}
//	
////Returns the number of words in the tree

std::size_t WordTree::size() {
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

std::size_t WordTree::recursiveSize(std::shared_ptr<TreeNode> node) {

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