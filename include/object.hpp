#pragma once

#include <string>
#include <chrono>
#include <memory>

using FileType = int;
using Clock = std::chrono::system_clock::time_point;
using std::chrono::system_clock;

class Object
{
public:
    Object(std::string const& name, unsigned int securityDomain, unsigned int securityLevel)
        : name{name}, uid{/*Not used as of now*/}, lastModified{system_clock::now()}, securityDomain{securityDomain}, securityLevel{securityLevel}
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
private:
    std::string name;
    unsigned int uid;

    Clock lastModified;

    unsigned int securityDomain;
    unsigned int securityLevel;

    std::weak_ptr<Object> parent;
};

class Directory : public Object
{
public:
    Directory(std::string const& name, unsigned int securityDomain, unsigned int securityLevel)
        : Object{name, securityDomain, securityLevel}
    {}

    std::vector<std::weak_ptr<Object>> getChildren() const
    {
        return children;
    }

    void addChild(std::weak_ptr<Object> child)
    {
        children.push_back(child);
    }
private:
    std::vector<std::weak_ptr<Object>> children;
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
private:
    int size;
    FileType fileType;
};

