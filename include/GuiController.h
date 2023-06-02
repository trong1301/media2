#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

// SDL include
#include "sdl_libs/include/SDLTypes.h"

// 2W include
#include "SettingHandler.h"
#include "IndicatorIcon.h"
#include "MagicNumbers.h"

// Qt include
#include <QObject>

namespace sdl {
//!
//! \brief The GuiController class
//!
class GuiController : public QObject{
    Q_OBJECT

public:
    //!
    //! \brief GuiController()
    //!
    explicit GuiController(QObject* parent = nullptr,  std::shared_ptr<SettingHandler> settingHandler = nullptr);

    //!
    //! \brief ~GuiController()
    //!
    virtual ~GuiController();

    //!
    //! \brief init()
    //!
    virtual void init();

    //!
    //! \brief getSpeedDataStructure()
    //! \return Speedo structure
    //!
    TwoWheelsTypes::Speedo getSpeedDataStructure();

    //!
    //! \brief getBatteryDataStructure
    //! \return Battery structure
    //!
    TwoWheelsTypes::Battery getBatteryDataStructure();

    //!
    //! \brief getIndicatorDataStructure
    //! \return Indicators structure
    //!
    TwoWheelsTypes::Indicators getIndicatorDataStructure();

    //!
    //! \brief getIndicatorList
    //! \return
    //!
    QList<IndicatorIcon*> getIndicatorList();

    //!
    //! \brief getSettingHandler
    //! \return
    //!
    std::shared_ptr<SettingHandler> getSettingHandler() const;

    //!
    //! \brief randomSeed
    //! \param number
    //! \return
    //!
    int randomSeed(int number);

    //!
    //! \brief dummyRandomData
    //!
    void dummyRandomData();

signals:
    //!
    //! \brief onSpeedDataStructureChanged
    //! \param Speedo structure
    //!
    void onSpeedDataStructureChanged(const TwoWheelsTypes::Speedo&);

    //!
    //! \brief onBatteryDataStructureChanged
    //! \param Battery structure
    //!
    void onBatteryDataStructureChanged(const TwoWheelsTypes::Battery&);

    //!
    //! \brief onIndicatorsDataStructureChanged
    //! \param Indicators structure
    //!
    void onIndicatorsDataStructureChanged(const TwoWheelsTypes::Indicators&);

private:
    //!
    //! \brief mSpeedo
    //!
    TwoWheelsTypes::Speedo mSpeedo;

    //!
    //! \brief mBattery
    //!
    TwoWheelsTypes::Battery mBattery;

    //!
    //! \brief mIndicators
    //!
    TwoWheelsTypes::Indicators mIndicators;

    //!
    //! \brief m_indicatorIconList
    //!
    QList<IndicatorIcon*> m_indicatorIconList;

    //!
    //! \brief setIndicators
    //!
    void setIndicators(const QString&, const QString&, const bool&);

    //!
    //! \brief setSpeedDataStructure()
    //! \param Speedo structure
    //!
    void setSpeedDataStructure(TwoWheelsTypes::Speedo&);

    //!
    //! \brief setBatteryDataStructure
    //! \param Battery structure
    //!
    void setBatteryDataStructure(TwoWheelsTypes::Battery&);

    //!
    //! \brief setIndicatorsDataStructure()
    //! \param Indicators structure
    //!
    void setIndicatorsDataStructure(TwoWheelsTypes::Indicators&);

    //!
    //! \brief shutdown
    //!
    virtual void shutdown();

    //!
    //! \brief m_settingHandler
    //!
    std::shared_ptr<SettingHandler> m_settingHandler;

    //To not be re-created every loop
    TwoWheelsTypes::Speedo m_speedStructure;

    bool m_isSideStandDown{false};
    bool m_isBrakeActive{false};
    bool m_isReversedSpeed{false};
    bool m_isPositionSensorFault{false};
    uint m_speedStatus{0};
    QString m_speedStatusString{""};

};
} /* namespace sdl */

#endif // GUICONTROLLER_H
