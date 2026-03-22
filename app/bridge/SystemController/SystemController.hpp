#pragma once

#include <QObject>
#include <QString>

class SystemController : public QObject {
    Q_OBJECT

    Q_PROPERTY(int clickCount READ getClickCount NOTIFY clickCountChanged)

public:

    explicit SystemController(
        QObject* parent = nullptr
    );

    [[nodiscard]] int getClickCount() const;

public slots:

    void executeAction(
        const QString& actionName
    );

signals:

    void clickCountChanged();

private:
    int m_clickCount; 
};