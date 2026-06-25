#include "secureFileSystem.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
#include <algorithm>
#include <iterator>

SecureFileSystem::SecureFileSystem(std::string const &filesystemName)
    : filesystemName{filesystemName}, nodes{}
{
    nodes["root"] = Node{"root", {}, {}, nullptr, true}; // Root node of the file system.
}

SecureFileSystem::~SecureFileSystem()
{
}

bool SecureFileSystem::save()
{

    return true;
}

void SecureFileSystem::createFile(std::string const &nodeName, std::vector<unsigned char> const& newData, std::string const& parentDirectory)
{
    Node newNode {};
    if (nodes.find(parentDirectory) != nodes.end())
    {
        newNode.name = nodeName;
        newNode.isDirectory = false;
        newNode.data = newData;
        // std::copy(std::begin(newNode.data), std::end(newNode.data), std::ostream_iterator<unsigned char>(std::cout));
        newNode.parent = &nodes.at(parentDirectory);
        nodes[newNode.name] = newNode;
        nodes[newNode.parent->name].children.push_back(&nodes[newNode.name]);
    }
}

std::vector<unsigned char> SecureFileSystem::readFile(std::string const &fileName) const
{
    std::cout << fileName << std::endl;
    if (nodes.find(fileName) != nodes.end() && nodes.at(fileName).isDirectory == false)
    {
        return nodes.at(fileName).data;
    }

    return std::vector<unsigned char>();
}

void SecureFileSystem::createDirectory(std::string const &directoryName, std::string const& parentDirectory)
{
    if (nodes.find(parentDirectory) != nodes.end())
    {
        Node newNode {};
        newNode.name = directoryName;
        newNode.isDirectory = true;
        newNode.parent = &nodes.at(parentDirectory);
        nodes[newNode.name] = newNode;
        nodes[newNode.parent->name].children.push_back(&nodes[newNode.name]);
    }
}

/// @brief Currently returns a vector of pointers to the nodes, breaking encapsulation.
/// TODO: Change to not return pointers to the actual nodes, but instead just return the metadata.
/// @param directoryName 
/// @return 
std::vector<Node *> SecureFileSystem::getDirectoryChildren(std::string const &directoryName) const
{
    if (nodes.find(directoryName) != nodes.end())
    {
        return nodes.at(directoryName).children;
    }
    return std::vector<Node *>();
}

/// @brief Returns a node, if it exists on the filesystem. Currently breaks encapsulation by returning a pointer.
/// TODO: Find better way to return a node's data and metadata.
/// @param nodeName 
/// @return 
Node * SecureFileSystem::getNode(std::string const &nodeName)
{
    if (nodes.find(nodeName) != nodes.end())
        return &nodes[nodeName];
    return nullptr;
}

const Node *SecureFileSystem::getRootNode() const
{
    return &nodes.at("root");
}

std::vector<std::string> SecureFileSystem::getDirectoryTree(std::string const &directoryName) const
{
    std::vector<std::string> absolutePath{};

    Node* currentNodeParent {nodes.at(directoryName).parent};

    absolutePath.push_back(nodes.at(directoryName).name);
    while (currentNodeParent != nullptr && nodes.find(currentNodeParent->name) != nodes.end())
    {
        absolutePath.push_back(currentNodeParent->name);
        currentNodeParent = currentNodeParent->parent;
    }


    return absolutePath;
}
