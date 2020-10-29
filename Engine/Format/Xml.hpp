#ifndef AZGARD_LIB_XML
#define AZGARD_LIB_XML

#include "Core/Engine.hpp"

#include "rapidxml.hpp"

#include "File/FileHandle.hpp"

namespace Azgard {

class AZG_API XmlAttribute {
    friend class XmlNode;
private:
    rapidxml::xml_attribute<char> *attribute = nullptr;
    XmlAttribute(rapidxml::xml_attribute<>* attribute);
public:
    XmlAttribute(const XmlAttribute& other);
    XmlAttribute next(const char* key = nullptr);
    const char* readAsText();
    int readAsInt();
    long int readAsLongInt();
    long long int readAsLongLongInt();
    float readAsFloat();
    const char* name();
};

enum XmlNodeType {
    cdata = rapidxml::node_type::node_cdata,
    comment = rapidxml::node_type::node_comment,
    data = rapidxml::node_type::node_data,
    declaration = rapidxml::node_type::node_declaration,
    doctype = rapidxml::node_type::node_doctype,
    document = rapidxml::node_type::node_document,
    element = rapidxml::node_type::node_element,
    pi = rapidxml::node_type::node_pi,
};

class AZG_API XmlNode {
    friend class XmlDocument;
private:
    rapidxml::xml_node<>* node = nullptr;
    rapidxml::xml_document<>* doc = nullptr;
    XmlNode(rapidxml::xml_node<>* node, rapidxml::xml_document<>* doc);
public:
    XmlNode(const XmlNode& other);
    XmlNode firstNode(const char* key = nullptr);
    XmlNode nextSibling(const char* key = nullptr);
    XmlNode appendNode(XmlNodeType type, const char* name, const char* value = nullptr);
    XmlNode insertNode(XmlNode& where, XmlNodeType type, const char* name, const char* value = nullptr);
    void removeNode(XmlNode& node);
    XmlAttribute getAttribute(const char* attribute = nullptr);
    XmlAttribute addAttribute(const char* name, const char* value);
    void removeAttribute(XmlAttribute& att);
    const char* readAsText();
    int readAsInt();
    long int readAsLongInt();
    long long int readAsLongLongInt();
    float readAsFloat();
    const char* name();
};

class AZG_API XmlDocument {
private:
    char* xml_raw;
    rapidxml::xml_document<>* doc = nullptr;
public:
    XmlDocument(FileHandle& file);
    XmlDocument(String src);
    ~XmlDocument();
    XmlNode firstNode(const char* key = nullptr);
    XmlNode appendNode(XmlNodeType type, const char* name, const char* value = nullptr);
    void save(FileHandle handle);
};


}
#endif