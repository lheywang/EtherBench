/**
 * @file    ConfigParser.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Handle the JSON to SettingModel conversion.
 * @version 0.1
 * @date    2026-03-26
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// =============================================================
// INCLUDES
// =============================================================
// Local libraries
#include "models/settings/node/node.hpp"

// QT
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>

// =============================================================
// CLASS
// =============================================================
class ConfigLoader {
  public:
    /**
     * @brief Parse a JSON config file and build the node susbsystem.
     *
     * @param filePath  The JSON file to be parsed.
     * @param rootNode  The root node to which the tree shall be attached.
     * @return true     The loading was successfull.
     * @return false    The loading was not sucessfull.
     */
    static bool parseFile(const QString &filePath, ConfigNode *rootNode);

  private:
    /**
     * @brief Parse a JSON object and build the node data related to it.
     *
     * @param jsonObject    The JSON object to be parsed.
     * @param parentNode    The parent node to which this node shall be attached.
     */
    static void parseObject(const QJsonObject &jsonObject, ConfigNode *parentNode);

    /**
     * @brief Attach some specific properties to the parent node, such as :
     *          - specific allowedValues.
     *          - default value.
     *
     * @param key           The key name.
     * @param valueObject   The value object which contain the specific properties.
     * @param parentNode    The parent node to which we shall attach theses new
     * properties.
     */
    static void extractNodeData(
        const QString &key, const QJsonObject &valueObject, ConfigNode *parentNode);
};