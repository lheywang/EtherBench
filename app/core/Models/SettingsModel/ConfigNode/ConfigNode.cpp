/**
 * @file    ConfigNodes.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-26
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Header
#include "ConfigNode.hpp"

// QT
#include <QList>
#include <QVariant>
#include <QVector>

// =============================================================
// INCLUDES
// =============================================================
/*
 * Constructors and Destructors
 */
ConfigNode::ConfigNode(const QList<QVariant> &data, ConfigNode *parent)
    : m_itemData(data), m_parentItem(parent) {
    return;
}

ConfigNode::~ConfigNode() {
    qDeleteAll(this->m_children);
    return;
}

/*
 * Methods to manage childs :
 */
void ConfigNode::appendChild(ConfigNode *child) {
    this->m_children.append(child);
    return;
}

ConfigNode *ConfigNode::child(int row) {
    if ((row < 0) || (row > this->m_children.size())) {
        return nullptr;
    }
    return this->m_children.at(row);
}

int ConfigNode::childCount() const { return this->m_children.count(); }
int ConfigNode::columnCount() const { return this->m_itemData.count(); }

QVariant ConfigNode::data(int column) const {
    if ((column < 0) || (column > this->m_itemData.size())) {
        return QVariant();
    }
    return this->m_itemData.at(column);
}

int ConfigNode::row() const {
    if (this->m_parentItem) {
        return this->m_parentItem->m_children.indexOf(const_cast<ConfigNode *>(this));
    }
    return 0;
}

ConfigNode *ConfigNode::parentItem() { return this->m_parentItem; }

void ConfigNode::setAllowedValues(const QStringList &values) {
    this->m_allowedValues = values;
    return;
}

QStringList ConfigNode::allowedValues() const { return this->m_allowedValues; }

void ConfigNode::setData(int column, const QVariant &value) {
    if ((column < 0) || (column > this->m_itemData.size())) {
        return;
    }
    this->m_itemData[column] = value;
    return;
}