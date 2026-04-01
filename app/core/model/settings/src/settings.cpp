/**
 * @file    SettingsModel.cpp
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
#include "SettingsModel.hpp"

// Local libraries
#include "ConfigLoader/ConfigLoader.hpp"
#include "ConfigNode/ConfigNode.hpp"

// QT
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

// STD
#include <memory>

// =============================================================
// CLASS
// =============================================================

/*
 * Constructors and destructord
 */
ConfigModel::ConfigModel(QObject *parent, QString fileName) : QAbstractItemModel(parent) {

    // Init some data
    QList<QVariant> rootData;
    rootData << "Paramètre" << "Valeur";
    this->m_rootNode = std::make_unique<ConfigNode>(rootData);

    // Load the config file
    qInfo() << "[ConfigModel] Starting the parsing of the JSON file";
    this->loadFromFile(fileName);
    return;
}

ConfigModel::~ConfigModel() {
    // We shall probably delete the config.
    return;
}

/*
 * Overloads to ensure QT can naviguate over the tree :
 */
QModelIndex ConfigModel::index(int row, int column, const QModelIndex &parent) const {

    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    ConfigNode *parentNode = parent.isValid()
                                 ? static_cast<ConfigNode *>(parent.internalPointer())
                                 : this->m_rootNode.get();

    ConfigNode *childNode = parentNode->child(row);

    if (childNode) {
        return createIndex(row, column, childNode);
    }

    return QModelIndex();
}

QModelIndex ConfigModel::parent(const QModelIndex &index) const {

    if (!index.isValid()) {
        return QModelIndex();
    }

    ConfigNode *childNode = static_cast<ConfigNode *>(index.internalPointer());
    ConfigNode *parentNode = childNode->parentItem();

    if (parentNode == this->m_rootNode.get() || !parentNode) {
        return QModelIndex();
    }

    return createIndex(parentNode->row(), 0, parentNode);
}

int ConfigModel::rowCount(const QModelIndex &parent) const {

    if (parent.column() > 0) {
        return 0;
    }

    ConfigNode *parentNode = parent.isValid()
                                 ? static_cast<ConfigNode *>(parent.internalPointer())
                                 : this->m_rootNode.get();

    return parentNode->childCount();
}

int ConfigModel::columnCount(const QModelIndex &parent) const {

    if (parent.isValid()) {
        return static_cast<ConfigNode *>(parent.internalPointer())->columnCount();
    }

    return this->m_rootNode->columnCount();
}

QVariant ConfigModel::data(const QModelIndex &index, int role) const {

    // Ensure the index is valid
    if (!index.isValid()) {
        return QVariant();
    }

    ConfigNode *node = static_cast<ConfigNode *>(index.internalPointer());

    switch (role) {
    case ParameterNameRole:
    case Qt::DisplayRole:
        return node->data(0);

    case ParameterValueRole:
    case Qt::EditRole:
        return node->data(1);

    case AllowedValuesRole:
        return node->allowedValues();

    default:
        return QVariant();
    }
}

/*
 * Overloads to ensure QT can edit the tree :
 */

bool ConfigModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    // Ensure the request is correctly formed :
    if (!index.isValid() || role != ParameterValueRole) {
        return false;
    }

    ConfigNode *node = static_cast<ConfigNode *>(index.internalPointer());
    QStringList constraints = node->allowedValues();
    if (!constraints.isEmpty() && !constraints.contains(value.toString())) {
        return false;
    }

    // Update the node
    node->setData(1, value);

    // Update the QML
    emit dataChanged(index, index, {role});
    emit parameterChanged(node->data(0).toString(), value.toString());

    return true;
}

Qt::ItemFlags ConfigModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    ConfigNode *node = static_cast<ConfigNode *>(index.internalPointer());

    if ((index.column() == 1) && (node->childCount() == 0)) {
        return defaultFlags | Qt::ItemIsEditable;
    }

    return defaultFlags;
}

/*
 * Functions
 */

bool ConfigModel::loadFromFile(const QString &filePath) {
    // Warn the model that we're going to update things ...
    this->beginResetModel();

    // Initialize the root node :
    QList<QVariant> rootHeaders;
    rootHeaders << "Parameter" << "Value";

    this->m_rootNode = std::make_unique<ConfigNode>(rootHeaders);

    // Start the file parsing :
    bool parseSucess = ConfigLoader::parseFile(filePath, m_rootNode.get());
    if (!parseSucess) {
        qWarning() << "[SettingsModel] Failed to load the setting tree from " << filePath;
    }

    qInfo() << "[ConfigModel] Finished loading configuration file";

    // We finished updating it.
    this->endResetModel();
    return parseSucess;
}

QHash<int, QByteArray> ConfigModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ParameterNameRole] = "parameterName";
    roles[ParameterValueRole] = "parameterValue";
    roles[AllowedValuesRole] = "allowedValues";
    return roles;
}