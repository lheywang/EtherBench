#pragma once

#include <QObject>
#include <QString>
#include <QtQml/qqml.h>

class SystemController : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(SystemController)
    QML_SINGLETON

    Q_PROPERTY(
        ViewId currentView READ getCurrentView WRITE setCurrentView NOTIFY
            currentViewChanged)

  public:
    enum ViewId { Home = 0, Memory, InputOutput, Sequences, Debugger, Settings, Help };
    Q_ENUM(ViewId)

    explicit SystemController(QObject *parent = nullptr);
    [[nodiscard]] ViewId getCurrentView() const;

  public slots:
    void setCurrentView(ViewId view);

  signals:
    void currentViewChanged();

  private:
    ViewId m_currentView;
};