#pragma once

#include "object.hpp"

#include <vector>
#include <unordered_map>

/// The basic block for the file system.
/// Stores the metadata and a pointer where the data is located in memory.
/// A node can either be a normal file or a directory, which is decided by the isDirectory variable.
struct Node
{
    std::string name; // The name of the node

    /// The data of the node, can either be data for a file. Is undefined if Node is a directory.
    /// Check if directory by checking the isDirectory variable
    std::vector<unsigned char> data;
    /// Stores a list of non-owning pointers to all the Nodes under the directory.
    std::vector<Node*> children;
    /// The parent of the node, can be invalid.
    Node* parent;
    bool isDirectory = false;
};

class SecureFileSystem
{
public:
    SecureFileSystem(std::string const& filesystemName);

    ~SecureFileSystem();

    /// Saves the filesystem to a file
    bool save();

    void createFile(std::string const& nodeName, std::vector<unsigned char> const& newData, std::string const& parent = std::string{});

    std::vector<unsigned char> readFile(std::string const& fileName) const;

    void createDirectory(std::string const& directoryName, std::string const& parentDirectory);

    std::vector<Node*> getDirectoryChildren(std::string const& directoryName) const;

    Node * getNode(std::string const& nodeName);
    const Node* getRootNode() const;

    std::vector<std::string> getDirectoryTree(std::string const& directoryName) const;

    // File* createFile(File & newFile, std::string parentDirectoryName, const char* data);
    // std::vector<char> readFile(File const& file) const;

    // int createDirectory(Directory & newDirectory, Directory const& parentDirectory);
private:
    std::string filesystemName;
    /// A constant-time access list that stores all the nodes that exists in the filesystem.
    std::unordered_map<std::string, Node> nodes;

};