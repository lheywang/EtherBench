#pragma once

#include <QObject>
#include <QString>
#include <qtmetamacros.h>

class SystemController : public QObject {
    Q_OBJECT

    Q_PROPERTY(int clickCount READ getClickCount NOTIFY clickCountChanged)

public:

    enum class ActiveView {
        Home = 0,
        Debugger,
        Memory,
        Sequences,
        Settings
    };
    Q_ENUM(ActiveView);

    explicit SystemController(
        QObject* parent = nullptr
    );

    [[nodiscard]] int getClickCount() const;
    [[nodiscard]] int getCurrentView() const;

public slots:

    void executeAction(
        const QString& actionName
    );

    void setCurrentView(
        int viewId
    );

signals:

    void clickCountChanged();
    void currentViewChanged();

private:
    int m_clickCount; 
    int m_currentView;
};