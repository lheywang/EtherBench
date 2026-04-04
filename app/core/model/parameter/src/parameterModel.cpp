/**
 * @file    parameterModel.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief
 * @version 0.1
 * @date    2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Header
#include <models/parameterModel.hpp>

// Local libraries
#include <models/parameters/parameterStruct.hpp>

// Qt
#include <QMap>
#include <QObject>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStringList>
#include <QVariant>

// =============================================================
// CLASS
// =============================================================
namespace EtherBench::Models {
/*
 * Constructor and destructors
 */
ParameterModel::ParameterModel(QObject *parent) : QStandardItemModel(parent) {}

/*
 * Functions
 */
void ParameterModel::syncWithRegistry() {
    buildFromRegistry(ParameterRegistry::instance());
    return;
}

QStandardItem *
ParameterModel::findOrCreatePath(QStandardItem *parentItem, const QString &name) {

    for (int i = 0; i < parentItem->rowCount(); ++i) {
        if (parentItem->child(i)->text() == name) {
            return parentItem->child(i);
        }
    }

    auto *newItem = new QStandardItem(name);
    newItem->setEditable(false);
    parentItem->appendRow(newItem);
    return newItem;
}

void ParameterModel::buildFromRegistry(const ParameterRegistry &registry) {

    this->clear();
    this->setHorizontalHeaderLabels({"Parameters"});

    auto keys = registry.allKeys();

    for (const QString &fullPath : keys) {
        QStringList parts = fullPath.split("/");
        QStandardItem *parentItem = this->invisibleRootItem();

        for (int i = 0; i < parts.size() - 1; i += 1) {
            parentItem = findOrCreatePath(parentItem, parts[i]);
        }

        QString scopePath = QStringList(parts.mid(0, parts.size() - 1)).join("/");
        parentItem->setData(scopePath, Qt::UserRole);
    }
}

} // namespace EtherBench::Models