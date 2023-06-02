#ifndef INDICATORLISTMODEL_H
#define INDICATORLISTMODEL_H

// Qt include
#include <QAbstractListModel>
#include <QColor>
#include <QObject>
#include <QString>
#include <QTimer>

// 2W include
#include "GuiController.h"
#include "IndicatorIcon.h"
#include "MagicNumbers.h"
#include "SocketManager.h"

class IndicatorListModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum IndicatorIconRoles {
        NameRole = Qt::UserRole,
        ImageSourceRole,
        ColorBgIconInactiveRole,
        ColorBorderBgIconInactiveRole,
        ColorBgIconActiveRole,
        ColorBorderBgIconActiveRole,
        ColorShadowBorderBgIconRole,
        VisibleRole,
        StateIndicatorIconRole
    };

    explicit IndicatorListModel(QObject* parent = nullptr
        , std::shared_ptr<sdl::GuiController> guiCtrl = nullptr
        , std::shared_ptr<SocketManager> socketManager = nullptr
            );
    ~IndicatorListModel() override;

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex& index, const QVariant& value,
        int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addIndicatorIcon(IndicatorIcon* indicatorIcon);
    void setIndicatorList(QList<IndicatorIcon*> list);

    void removeIndicatorIcon(int index);
    void removeLastIndicatorIcon();

    Q_INVOKABLE void changeVisibility(QString screen);

    //!
    //! \brief forwardStateIconFromCAN
    //!
    void forwardStateIconfromCAN();

    //!
    //! \brief forwardStateIconFromSocket
    //!
    void forwardStateIconFromSocket();

private:
    // Dummy to change state until could be binding from CAN
    void addIndicatorStructData(int turn_left,
        bool side_stand,
        int reverse_mode,
        int head_light,
        int engine_trouble,
        int oil_lower,
        int coolant_tempt,
        int abs,
        int turn_right
        );

    enum IndicatorPosition {
        TURN_LEFT = 0,
        SIDE_STAND,
        REVERSE_MODE,
        HEAD_LIGHT,
        ENGINE_TROUBLE,
        OIL,
        COOL_LANT,
        ABS,
        TURN_RIGHT
    };


    //!
    //! \brief m_guiController
    //!
    std::shared_ptr<sdl::GuiController> m_guiController;

    //!
    //! \brief m_socketManager
    //!
    std::shared_ptr<SocketManager> m_socketManager;

    //!
    //! \brief m_indicatorStructData
    //!
    TwoWheelsTypes::Indicators m_indicatorStructData;

    //!
    //! \brief m_indicatorIconList
    //!
    QList<IndicatorIcon*> m_indicatorIconList;
};

#endif // INDICATORLISTMODEL_H
