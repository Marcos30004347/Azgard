#ifndef AZGARD_LIB_XML
#define AZGARD_LIB_XML

#include "Core/Engine.hpp"

#include "rapidxml.hpp"

#include "Library/File.hpp"

namespace Azgard {

class XmlAttribute {
    friend class XmlNode;
private:
    rapidxml::xml_attribute<char> *attribute = nullptr;
    XmlAttribute(rapidxml::xml_attribute<>* attribute);
public:
    AZG_API XmlAttribute(const XmlAttribute& other);
    AZG_API XmlAttribute next(const char* key = nullptr);
    AZG_API const char* readAsText();
    AZG_API int readAsInt();
    AZG_API long int readAsLongInt();
    AZG_API long long int readAsLongLongInt();
    AZG_API float readAsFloat();
    AZG_API const char* name();
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

class XmlNode {
    friend class XmlDocument;
private:
    rapidxml::xml_node<>* node = nullptr;
    rapidxml::xml_document<>* doc = nullptr;
    XmlNode(rapidxml::xml_node<>* node, rapidxml::xml_document<>* doc);
public:
    AZG_API XmlNode(const XmlNode& other);
    AZG_API XmlNode firstNode(const char* key = nullptr);
    AZG_API XmlNode nextSibling(const char* key = nullptr);
    AZG_API XmlNode appendNode(XmlNodeType type, const char* name, const char* value = nullptr);
    AZG_API XmlNode insertNode(XmlNode& where, XmlNodeType type, const char* name, const char* value = nullptr);
    AZG_API void removeNode(XmlNode& node);
    AZG_API XmlAttribute getAttribute(const char* attribute = nullptr);
    AZG_API XmlAttribute addAttribute(const char* name, const char* value);
    AZG_API void removeAttribute(XmlAttribute& att);
    AZG_API const char* readAsText();
    AZG_API int readAsInt();
    AZG_API long int readAsLongInt();
    AZG_API long long int readAsLongLongInt();
    AZG_API float readAsFloat();
    AZG_API const char* name();
};

class XmlDocument {
private:
    char* xml_raw;
    rapidxml::xml_document<>* doc = nullptr;
public:
    AZG_API XmlDocument(File* file);
    AZG_API XmlDocument(const char* src);
    AZG_API ~XmlDocument();
    AZG_API XmlNode firstNode(const char* key = nullptr);
    AZG_API XmlNode appendNode(XmlNodeType type, const char* name, const char* value = nullptr);
    AZG_API void save(File* handle);
};


}
#endif