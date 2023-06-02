#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

// 2W include
#include "GuiController.h"
#include "SettingHandler.h"

// Qt include
#include <QObject>
#include <QTimer>
#include <QString>

class Speedometer : public QObject {
    Q_OBJECT

    //!
    //! \brief Expose the speed member to qml
    //!
    Q_PROPERTY(float speed READ speed WRITE setSpeed NOTIFY speedChanged)

    //!
    //! \brief Expose the mileAge member to qml
    //!
    Q_PROPERTY(float mileAge MEMBER m_mileAge NOTIFY mileAgeChanged)

    //!
    //! \brief Expose the speedStatus member to qml
    //!
    Q_PROPERTY(QString speedStatus MEMBER m_speedStatus NOTIFY speedStatusChanged)

public:
    //!
    //! \brief Speedometer
    //! \param parent
    //! \param guiCtrl
    //!
    explicit Speedometer(QObject* parent = nullptr, std::shared_ptr<sdl::GuiController> guiCtrl = nullptr);

    //!
    //! \brief ~Speedometer
    //!
    ~Speedometer();

    //!
    //! \brief speed
    //! \return
    //!
    int speed() const;

    //!
    //! \brief getMileAge
    //! \return
    //!
    float getMileAge() const;

    //!
    //! \brief getSpeedStatus
    //! \return
    //!
    QString getSpeedStatus() const;

    //!
    //! \brief setSpeed
    //! \param newSpeed
    //!
    void setSpeed(const float& newSpeed);

    //!
    //! \brief setMileAge
    //! \param mileAge
    //!
    void setMileAge(const float& mileAge);

    //!
    //! \brief setSpeedUnit
    //! \param speedUnit
    //!
    void setSpeedUnit(const int& speedUnit);

    //!
    //! \brief setSpeedStatus
    //! \param speedStatus
    //!
    void setSpeedStatus(const QString& speedStatus);

signals:
    //!
    //! \brief speedChanged
    //!
    void speedChanged();

    //!
    //! \brief mileAgeChanged
    //! \param mileAge
    //!
    void mileAgeChanged();

    //!
    //! \brief speedStatusChanged
    //! \param speedStatus
    //!
    void speedStatusChanged();

private:

    //!
    //! \brief KM_TO_MILE_RATIO
    //!
    float KM_TO_MILE_RATIO;

    //!
    //! \brief m_speed
    //!
    float m_speed;

    //!
    //! \brief m_speedo
    //!
    TwoWheelsTypes::Speedo m_speedo;

    //!
    //! \brief m_guiController
    //!
    std::shared_ptr<sdl::GuiController> m_guiController;

    //!
    //! \brief m_mileAge
    //!
    float m_mileAge;

    //!
    //! \brief m_speedUnit
    //!
    int m_speedUnit;

    //!
    //! \brief m_speedStatus
    //!
    QString m_speedStatus;

    //!
    //! \brief m_settingHandler
    //!
    std::shared_ptr<SettingHandler> m_settingHandler;
};

#endif // SPEEDOMETER_H
