#pragma once

#include <QObject>
#include <QString>
#include <QtQml/qqml.h> // <- INDISPENSABLE POUR LES MACROS QT6

class SystemController : public QObject {
  Q_OBJECT
QML_ELEMENT       // Dit à CMake d'exposer cette classe au QML
    QML_SINGLETON // Précise qu'il n'y aura qu'une seule instance (Singleton)

    Q_PROPERTY(ViewId currentView READ getCurrentView WRITE setCurrentView
                   NOTIFY currentViewChanged)

        public : enum ViewId {
          Home = 0,
          Memory,
          InputOutput,
          Sequences,
          Debugger
        };
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