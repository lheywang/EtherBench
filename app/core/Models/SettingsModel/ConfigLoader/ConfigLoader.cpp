/**
 * @file    ConfigParser.cpp
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
#include "ConfigLoader.hpp"

// Local libraries
#include "ConfigNode/ConfigNode.hpp"

// QT
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>

// =============================================================
// CLASS
// =============================================================

bool ConfigLoader::parseFile(const QString &filePath, ConfigNode *rootNode) {

    // Ensure the root node is a valid instance
    if (!rootNode) {
        return false;
    }

    // Open the file, and check if it was correct
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical()
            << "[ConfigLoader] IO Error : Could not open config file for reading : "
            << filePath;
        return false;
    }

    // Fetch all bytes, and close.
    // That's OK, because a JSON file isn't expected to be that big.
    // If needed, we may required to changed that to a bufferised reading.
    QByteArray rawData = file.readAll();
    file.close();

    // Parse the bytestream into a structured JSON object :
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qCritical() << "[ConfigLoader] Failed to parse the JSON file at offset "
                    << parseError.offset << " : " << parseError.errorString();
        return false;
    }

    if (!jsonDoc.isObject()) {
        qCritical() << "[ConfigLoader] The JSON root must be an object. Invalid config.";
        return false;
    }

    // Finish the parsing by expading the properties into the different sub nodes :
    parseObject(jsonDoc.object(), rootNode);
    return true;
}

void ConfigLoader::parseObject(const QJsonObject &jsonObject, ConfigNode *parentNode) {

    // We just need to iterate over all the keys :
    for (auto it = jsonObject.constBegin(); it != jsonObject.constEnd(); it += 1) {
        const QString key = it.key();
        const QJsonValue value = it.value();

        if (value.isObject()) {
            ConfigLoader::extractNodeData(key, value.toObject(), parentNode);
        }
    }

    return;
}

void ConfigLoader::extractNodeData(
    const QString &key, const QJsonObject &valueObject, ConfigNode *parentNode) {

    // Fetch the "value" field :
    QString paramValue;
    if (valueObject.contains("value") && valueObject.value("value").isString()) {
        paramValue = valueObject.value("value").toString();
    }

    // Creating a new ConfigNode class to store the elements :
    QList<QVariant> nodeData;
    nodeData << key << paramValue;
    ConfigNode *currentNode = new ConfigNode(nodeData, parentNode);

    // Check if some restrictions must be added :
    if (valueObject.contains("allowedValues") &&
        valueObject.value("allowedValues").isArray()) {
        QJsonArray allowedArray = valueObject.value("allowedValues").toArray();
        QStringList allowedList;

        for (const QJsonValue &val : allowedArray) {
            if (val.isString()) {
                allowedList << val.toString();
            }
        }

        currentNode->setAllowedValues(allowedList);
        parentNode->appendChild(currentNode);
    }

    // Handling recursively elements :
    if (valueObject.contains("children") && valueObject.value("children").isObject()) {
        parseObject(valueObject.value("children").toObject(), currentNode);
    }
}