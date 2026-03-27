/**
 * @file    MemoryModel.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Hold the data of the settings treeView on the QT Interface
 * @version 0.1
 * @date    2026-03-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// =============================================================
// INCLUDES
// =============================================================
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

class ConfigModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    // Ensure we'll be able to fetch the allowedValues property.
    enum ConfigRoles {
        ParameterNameRole = Qt::UserRole + 1,
        ParameterValueRole,
        AllowedValuesRole
    };

  public:
    /*
     * Constructors and destructord
     */
    /**
     */
    explicit ConfigModel(
        QObject *parent = nullptr, QString fileName = QString("settings.json"));
    ~ConfigModel() override;

    /*
     * Overloads to ensure QT can naviguate over the tree :
     */
    /**
     */
    QModelIndex
    index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief
     *
     * @param index
     * @return QModelIndex
     */
    QModelIndex parent(const QModelIndex &index) const override;

    /**
     * @brief
     *
     * @param parent
     * @return int
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief
     *
     * @param parent
     * @return int
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief
     *
     * @param index
     * @param role
     * @return QVariant
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /*
     * Overloads to ensure QT can edit the tree :
     */
    /**
     */
    bool setData(
        const QModelIndex &index,
        const QVariant &value,
        int role = Qt::DisplayRole) override;

    /**
     * @brief
     *
     * @param index
     * @return Qt::ItemFlags
     */
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * @brief
     *
     * @return QHash<int, QByteArray>
     */
    QHash<int, QByteArray> roleNames() const override;

  signals:
    void parameterChanged(const QString &parameterName, const QString &newValue);

  public:
    /**
     * @brief Load the JSON formatted config.
     *
     * @param filePath  The filepath where the config could be found
     * @return  true    The config was correctly loaded.
     * @return  false   An error occured. Check the logs.
     */
    bool loadFromFile(const QString &filePath);

  private:
    std::unique_ptr<ConfigNode> m_rootNode;
};