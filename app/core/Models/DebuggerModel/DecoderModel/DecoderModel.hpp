/**
 * @file    DecoderModel.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
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
#include "ProtocolsStructs.hpp"
#include <QObject>
#include <QtQml/qqml.h>
#include <qcontainerfwd.h>
#include <qobject.h>
#include <qqmlintegration.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================
class DecoderModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString decodedTimestamp READ getDecodedTimestamp NOTIFY decodingComplete)
    Q_PROPERTY(QString decodedBus READ getDecodedBus NOTIFY decodingComplete)
    Q_PROPERTY(QString decodedPayload READ getDecodedPayload NOTIFY decodingComplete)

  public:
    explicit DecoderModel(QObject *parent = nullptr);
    ~DecoderModel();

  public:
    [[nodiscard]] QString getDecodedTimestamp() const;
    [[nodiscard]] QString getDecodedBus() const;
    [[nodiscard]] QString getDecodedPayload() const;

  public slots:
    void decodeFrameAt(int rowIndex);

  signals:
    void decodingComplete();

  private:
    QString m_decodedTimestamp;
    QString m_decodedBus;
    QString m_decodedPayload;
};
