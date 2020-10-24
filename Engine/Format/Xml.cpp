#include "Xml.hpp"

#include <cstring>
#include <iostream>
#include <sstream>

#include "rapidxml_print.hpp"

using namespace Azgard;

XmlAttribute::XmlAttribute(rapidxml::xml_attribute<>* attribute): attribute{attribute} {}

AZG_API XmlAttribute::XmlAttribute(const XmlAttribute& other) {
    memcpy(this->attribute, other.attribute, sizeof(rapidxml::xml_attribute<>));
}

AZG_API XmlAttribute XmlAttribute::next(const char* key) {
    return XmlAttribute(this->attribute->next_attribute(key));
}

AZG_API const char* XmlAttribute::readAsText() {
    return this->attribute->value();
}

AZG_API int XmlAttribute::readAsInt() {
    return atoi(this->attribute->value());
}

AZG_API long int XmlAttribute::readAsLongInt() {
    return atol(this->attribute->value());
}

AZG_API long long int XmlAttribute::readAsLongLongInt() {
    return atoll(this->attribute->value());
}

AZG_API float XmlAttribute::readAsFloat() {
    return atof(this->attribute->value());
}

AZG_API const char* XmlAttribute::name() {
    return this->attribute->name();
}

AZG_API XmlNode::XmlNode(rapidxml::xml_node<>* node, rapidxml::xml_document<>* doc): node{node}, doc{doc} {}

AZG_API XmlNode::XmlNode(const XmlNode& other) {
    memcpy(this->node, other.node, sizeof(rapidxml::xml_node<>));
}

AZG_API XmlNode XmlNode::firstNode(const char* key) {
    return XmlNode(this->node->first_node(key), this->doc);
}

AZG_API XmlNode XmlNode::nextSibling(const char* key) {
    return XmlNode(this->node->next_sibling(), this->doc);
}

AZG_API XmlNode XmlNode::appendNode(XmlNodeType type, const char* name, const char* value) {
    char *node_name = doc->allocate_string(name);
    rapidxml::xml_node<> *node_ = this->doc->allocate_node((rapidxml::node_type)type, node_name, value);
    this->node->append_node(node_);
    return XmlNode(node_, this->doc);
}

AZG_API XmlNode XmlNode::insertNode(XmlNode& where, XmlNodeType type, const char* name, const char* value) {
    char *node_name = doc->allocate_string(name);
    rapidxml::xml_node<> *node_ = this->doc->allocate_node((rapidxml::node_type)type, node_name, value);
    this->node->insert_node(where.node, node_);
    return XmlNode(node_, this->doc);
}

AZG_API void XmlNode::removeNode(XmlNode& node) {
    this->node->remove_node(node.node);
    node.node = nullptr;
}

AZG_API XmlAttribute XmlNode::getAttribute(const char* attribute) {
    return XmlAttribute(this->node->first_attribute(attribute));
}

AZG_API XmlAttribute XmlNode::addAttribute(const char* name, const char* value) {
    rapidxml::xml_attribute<> *attr = this->doc->allocate_attribute(name, value);
    this->node->append_attribute(attr);
    return XmlAttribute(attr);
}

AZG_API void XmlNode::removeAttribute(XmlAttribute& att) {
    this->node->remove_attribute(att.attribute);
    att.attribute = nullptr;
}

AZG_API const char* XmlNode::readAsText() {
    return this->node->value();
}

AZG_API int XmlNode::readAsInt() {
    return atoi(this->node->value());
}

AZG_API long int XmlNode::readAsLongInt() {
    return atol(this->node->value());
}

AZG_API long long int XmlNode::readAsLongLongInt() {
    return atoll(this->node->value());
}

AZG_API float XmlNode::readAsFloat() {
    return atof(this->node->value());
}

AZG_API const char* XmlNode::name() {
    return this->node->name();
}


AZG_API XmlDocument::XmlDocument(File* file) {
    // TODO: not use std::string
    this->doc = new rapidxml::xml_document<>();
    std::string str (file->getBuffer());
    xml_raw = new char[str.size()];
    strcpy (xml_raw, str.c_str());
    doc->parse<0>(xml_raw);  
}

AZG_API XmlDocument::XmlDocument(const char* src) {
    this->doc = new rapidxml::xml_document<>();
    std::string str (src);
    xml_raw = new char[str.size()];
    strcpy (xml_raw, str.c_str());
    doc->parse<0>(xml_raw);  
}

AZG_API XmlDocument::~XmlDocument() {
    delete xml_raw;
    delete doc;
}

AZG_API XmlNode XmlDocument::firstNode(const char* key) {
    return XmlNode(doc->first_node(key), this->doc);
}

AZG_API XmlNode XmlDocument::appendNode(XmlNodeType type, const char* name, const char* value) {
    char *node_name = doc->allocate_string(name);
    rapidxml::xml_node<> *node = this->doc->allocate_node((rapidxml::node_type)type, node_name, value);
    this->doc->append_node(node);
    return XmlNode(node, this->doc);
}

AZG_API void XmlDocument::save(File* handle) {
    std::stringstream stream;
    std::ostream_iterator<char> iter(stream);

    rapidxml::print(iter, *doc);

    handle->write(stream.str());
}