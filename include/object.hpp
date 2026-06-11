#pragma once

#include <string>
#include <chrono>
#include <memory>
#include <sstream>
#include <map>
#include <iostream>

using FileType = int;
using Clock = std::chrono::system_clock::time_point;
using std::chrono::system_clock;

class Object;
class Directory;
class File;

class Object
{
public:
    Object() = default;
    Object(std::string const& name, unsigned int securityDomain, unsigned int securityLevel, Directory* parent)
        :  parent{parent}, name{name}, uid{/*Not used as of now*/}, lastModified{system_clock::now()}, securityDomain{securityDomain}, securityLevel{securityLevel}
    {

    }

    Object(std::string const& name, unsigned int securityDomain, unsigned int securityLevel)
        : Object(name, securityDomain, securityLevel, nullptr)
    {}

    virtual ~Object() = default;

    std::string getName() const
    {
        return name;
    }
    Clock getLastModified() const
    {
        return lastModified;
    }

    void setSecurityDomain(int secDomain)
    {
        securityDomain = secDomain;
    }

    void setSecurityLevel(int secLevel)
    {
        securityLevel = secLevel;
    }

    unsigned int getSecurityDomain() const
    {
        return securityDomain;
    }
    unsigned int getSecurityLevel() const
    {
        
        return securityLevel;
    }
    void setParent(Directory* newParent)
    {
        parent = newParent;
    }

    Directory* getParent() const
    {
        return parent;
    }

    virtual void print(std::ostream & os) const
    {
        // if (getParent() != nullptr)
        //     os << getParent()->getName();
        os << getName() << " " << getSecurityDomain() << " " << getSecurityLevel() << " " << getSecurityDomain() << std::endl;
    }

    friend std::ostream& operator<<(std::ostream & os, Object const& obj)
    {
        obj.print(os);
        return os;
    }
protected:
    Directory* parent; /// Non-owning pointer that points to the parent of the object.
private:
    std::string name;
    unsigned int uid;

    Clock lastModified;

    unsigned int securityDomain;
    unsigned int securityLevel;

};



class Directory : public Object
{
public:
    Directory()
        : Object()
    {}

    Directory(std::string const& name, unsigned int securityDomain, unsigned int securityLevel, Directory* parent)
        : Object(name, securityDomain, securityLevel, parent)
    {
        // std::cout << parent->getName() << std::endl;
    }

    Directory(std::string const& name, unsigned int securityDomain, unsigned int securityLevel)
        : Object{name, securityDomain, securityLevel}
    {}

    std::map<std::string, Object*> getChildren() const
    {
        return children;
    }

    void addChild(Object* child)
    {
        child->setParent(this);
        children.emplace(child->getName(), child);
    }

    std::string getDirectoryTree() const
    {
        if (this->parent == nullptr)
            return getName();

        return this->parent->getDirectoryTree() + '/' + getName();
    }

    Directory switchDirectory(Directory const& dirToChange)
    {
        auto it = children.find(dirToChange.getName());

        return *dynamic_cast<Directory*>(it->second);
    }

    friend std::ostream & operator<<(std::ostream & os, Directory const& dir)
    {
        dir.print(os);

        for (std::pair<std::string, Object*> child: dir.getChildren())
        {
            os << child.second;
        }
        return os;
    }
private:
    std::map<std::string, Object*> children; /// List of non-owning pointers that point to all the objects in the directory.
};



class File : public Object
{
public: 
    File(std::string const& name, unsigned int securityDomain, unsigned int securityLevel, int size, FileType const& fileType)
    : Object(name, securityDomain, securityLevel), size{size}, fileType{fileType}
    {
        
    }
    File(std::string const& name)
        : File(name, 0, 0, 0, 0)
    {}

    int getSize() const
    {
        return size;
    }
    FileType getFileType() const
    {
        return fileType;
    }

    void addData(char const* newData)
    {
        // if (data != nullptr)
        //     delete data;

        data = newData;
    }

    const char* getData() const
    {
        return data;
    }

    void print(std::ostream & os) const override
    {
        os << dynamic_cast<Object*>(const_cast<File*>(this));
    }

    friend std::ostream& operator<<(std::ostream & os, File const& file)
    {
        file.print(os);

        os << file.getSize() << " " << file.getFileType() << " " << file.getData() << std::endl;
        return os;
    }
private:
    int size;
    FileType fileType;

    const char* data; /// Pointer to where the file's data is located.
};


