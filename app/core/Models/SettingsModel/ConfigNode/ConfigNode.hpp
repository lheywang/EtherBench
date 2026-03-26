/**
 * @file    ConfigNodes.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define what a node is, and how is does hold values.
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
// QT
#include <QList>
#include <QVariant>
#include <QVector>

// =============================================================
// CLASS
// =============================================================

class ConfigNode {
  public:
    /*
     * Constructors and Destructors
     */
    /**
     * @brief Build a new node from empty data and eventually a parent.
     */
    explicit ConfigNode(const QList<QVariant> &data, ConfigNode *parent = nullptr);

    /**
     * @brief Destroy the Config Node object
     *
     */
    ~ConfigNode();

    /*
     * Methods to manage childs :
     */
    /**
     * @brief Append a new child to this node count.
     * @param[in] child Pointer to a ConfigNode class instance.
     */
    void appendChild(ConfigNode *child);

    /**
     * @brief Return a child at a specified row.
     *
     * @param[in] row The specified row.
     * @return ConfigNode* The requested child.
     */
    ConfigNode *child(int row);

    /**
     * @brief Return the number of childs that handled by this class.
     *
     * @return int The number of childs.
     */
    int childCount() const;

    /**
     * @brief Return the number of properties we handle.
     *
     * @return int The number of properties.
     */
    int columnCount() const;

    /**
     * @brief Return the requested data at a specified column.
     *
     * @param[in] column The requested column
     * @return QVariant The data requested for that column.
     */
    QVariant data(int column) const;

    /**
     * @brief Return the row of ourselves within our parent class.
     * @return int The row of ourselves inside our parent.
     */
    int row() const;

    /**
     * @brief Return the parent of that class.
     * @return ConfigNode*
     */
    ConfigNode *parentItem();

    /*
     * Functions to handle the values restrictions :
     */
    /**
     * @brief Configure the allowed values for the property list.
     */
    void setAllowedValues(const QStringList &values);

    /**
     * @brief Return the list of allowedValues for our properyty.
     * @return QStringList The list of allowed values.
     */
    QStringList allowedValues() const;

    /**
     * @brief Update a property of an object
     *
     * @param column The column to be updated
     * @param value The new value to be set.
     */
    void setData(int column, const QVariant &value);

  private:
    QVector<ConfigNode *> m_children;

    QList<QVariant> m_itemData;

    ConfigNode *m_parentItem;

    QStringList m_allowedValues;
};