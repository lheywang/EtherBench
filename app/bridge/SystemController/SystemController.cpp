#include "SystemController.hpp"
#include <QDebug>

SystemController::SystemController(
    QObject* parent
) : QObject(parent), m_clickCount(0) {}

int SystemController::getClickCount() const {
    return m_clickCount;
}

void SystemController::executeAction(
    const QString& actionName
) {
    m_clickCount++;
    
    qInfo() << "[C++] Action reçue du QML :" << actionName << "| Compteur interne :" << m_clickCount;
    
    emit clickCountChanged();
}