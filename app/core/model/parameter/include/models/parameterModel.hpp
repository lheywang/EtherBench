/**
 * @file    parameterModel.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief
 * @version 0.1
 * @date    2026-04-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// =============================================================
// INCLUDES
// =============================================================
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

class ParameterModel : public QStandardItemModel {
    Q_OBJECT
  public:
    explicit ParameterModel(QObject *parent = nullptr);

    void syncWithRegistry();
    void buildFromRegistry(const ParameterRegistry &registry);

  private:
    QStandardItem *findOrCreatePath(QStandardItem *parentItem, const QString &name);
};

} // namespace EtherBench::Models