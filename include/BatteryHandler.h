#ifndef BATTERYHANDLER_H
#define BATTERYHANDLER_H

// Qt include
#include <QObject>

// 2W include
#include "GuiController.h"

class BatteryHandler : public QObject
{
    Q_OBJECT

    //!
    //! \brief Expose the batteryLevel member to qml
    //!
    Q_PROPERTY(int batteryLevel READ getBatteryLevel WRITE setBatteryLevel NOTIFY batteryLevelChanged)

public:
    //!
    //! \brief BatteryHandler
    //!
    BatteryHandler(QObject* parent = nullptr, std::shared_ptr<sdl::GuiController> guiCtrl = nullptr);

    //!
    //! \brief ~BatteryHandler
    //!
    ~BatteryHandler();

    //!
    //! \brief setBatteryLevel
    //!
    void setBatteryLevel(int);

    //!
    //! \brief getBatteryLevel
    //! \return
    //!
    int getBatteryLevel();

signals:
    //!
    //! \brief batteryLevelChanged
    //!
    void batteryLevelChanged();

private:
    //!
    //! \brief m_batteryLevel
    //!
    int m_batteryLevel;

    //!
    //! \brief m_batteryLevelPercent
    //!
    int m_batteryLevelPercent;

    //!
    //! \brief m_guiController
    //!
    std::shared_ptr<sdl::GuiController> m_guiController;
};

#endif // BATTERYHANDLER_H
