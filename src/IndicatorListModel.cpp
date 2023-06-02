#include "include/IndicatorListModel.h"
#include <QDebug>
#include <cstdlib>

IndicatorListModel::IndicatorListModel(QObject* parent
    , std::shared_ptr<sdl::GuiController> guiCtrl
    , std::shared_ptr<SocketManager> socketManager
                                       )
    : QAbstractListModel(parent)
    , m_guiController(guiCtrl)
    , m_socketManager(socketManager)
{

    setIndicatorList(guiCtrl->getIndicatorList());
    forwardStateIconfromCAN();
    forwardStateIconFromSocket();

    connect(m_guiController.get(), &sdl::GuiController::onIndicatorsDataStructureChanged, this, [&](const TwoWheelsTypes::Indicators& indicator) {
        m_indicatorStructData.abs = indicator.abs;
        m_indicatorStructData.oil_lower = indicator.oil_lower;
        m_indicatorStructData.side_stand = indicator.side_stand;
        m_indicatorStructData.reverse_mode = indicator.reverse_mode;
        m_indicatorStructData.coolant_tempt = indicator.coolant_tempt;
        m_indicatorStructData.engine_trouble = indicator.engine_trouble;
        forwardStateIconfromCAN();
    });

    connect(m_socketManager.get(), &SocketManager::onIndicatorsDataStructureChanged, this, [&](const TwoWheelsTypes::Indicators& indicator) {
        m_indicatorStructData.turn_left = indicator.turn_left;
        m_indicatorStructData.turn_right = indicator.turn_right;
        m_indicatorStructData.head_light = indicator.head_light;
        forwardStateIconFromSocket();
    });
}

IndicatorListModel::~IndicatorListModel()
{
    disconnect(m_guiController.get(), &sdl::GuiController::onIndicatorsDataStructureChanged, this, nullptr);
    disconnect(m_socketManager.get(), &SocketManager::onIndicatorsDataStructureChanged, this, nullptr);
}

int IndicatorListModel::rowCount(const QModelIndex& parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return parent.isValid() ? 0 : m_indicatorIconList.count();
}

QVariant IndicatorListModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_indicatorIconList.count())
        return QVariant();

    IndicatorIcon* indicatoricon = m_indicatorIconList[index.row()];

    switch (role) {
    case NameRole:
        return indicatoricon->nameIcon();
    case ImageSourceRole:
        return indicatoricon->imageSource();
    case ColorBgIconInactiveRole:
        return indicatoricon->colorBgIconInactive();
    case ColorBorderBgIconInactiveRole:
        return indicatoricon->colorBorderBgIconInactive();
    case ColorBgIconActiveRole:
        return indicatoricon->colorBgIconActive();
    case ColorBorderBgIconActiveRole:
        return indicatoricon->colorBorderBgIconActive();
    case ColorShadowBorderBgIconRole:
        return indicatoricon->colorShadowBorderBgIcon();
    case VisibleRole:
        return indicatoricon->visible();
    case StateIndicatorIconRole:
        return indicatoricon->stateIcon();
    default:
        return QVariant();
    }
}

bool IndicatorListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    IndicatorIcon* indicatoricon = m_indicatorIconList[index.row()];

    switch (role) {
    case NameRole:
        if (indicatoricon->nameIcon() != value.toString()) {
            indicatoricon->setNameIcon(value.toString());
            qDebug() << "Changing nameIcon for" << indicatoricon->nameIcon();
        }
        break;
    case ImageSourceRole:
        if (indicatoricon->imageSource() != value.toString()) {
            indicatoricon->setImageSource(value.toString());
            qDebug() << "Changing imageSource for" << indicatoricon->imageSource();
        }
        break;
    case ColorBgIconInactiveRole:
        if (indicatoricon->colorBgIconInactive() != value.Color) {
            indicatoricon->setColorBgIconInactive(value.Color);
            qDebug() << "Changing colorBgIconInactive for" << indicatoricon->colorBgIconInactive();
        }
        break;
    case ColorBorderBgIconInactiveRole:
        if (indicatoricon->colorBgIconInactive() != value.Color) {
            indicatoricon->setColorBgIconInactive(value.Color);
            qDebug() << "Changing colorBgIconInactive for" << indicatoricon->colorBgIconInactive();
        }
        break;
    case ColorBgIconActiveRole:
        if (indicatoricon->colorBgIconActive() != value.Color) {
            indicatoricon->setColorBgIconActive(value.Color);
            qDebug() << "Changing colorBgIconActive for" << indicatoricon->colorBgIconActive();
        }
        break;
    case ColorBorderBgIconActiveRole:
        if (indicatoricon->colorBorderBgIconActive() != value.Color) {
            indicatoricon->setColorBorderBgIconActive(value.Color);
            qDebug() << "Changing colorBorderBgIconActive for" << indicatoricon->colorBorderBgIconActive();
        }
        break;
    case ColorShadowBorderBgIconRole:
        if (indicatoricon->colorShadowBorderBgIcon() != value.Color) {
            indicatoricon->setColorShadowBorderBgIcon(value.Color);
            qDebug() << "Changing colorShadowBorderBgIcon for" << indicatoricon->colorShadowBorderBgIcon();
        }
        break;
    case VisibleRole:
        if (indicatoricon->visible() != value.toBool()) {
            indicatoricon->setVisible(value.toBool());
            qDebug() << "Changing visible for" << indicatoricon->nameIcon() << indicatoricon->visible();
        }
        break;
    case StateIndicatorIconRole:
        if (indicatoricon->stateIcon() != value.toString()) {
            indicatoricon->setStateIcon(value.toString());
            qDebug() << "Changing stateIcon for" << indicatoricon->nameIcon() << indicatoricon->stateIcon();
        }
        break;
    }

    if (data(index, role) != value) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags IndicatorListModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> IndicatorListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names.insert(NameRole, "nameIcon");
    names.insert(ImageSourceRole, "imageSource");
    names.insert(ColorBgIconInactiveRole, "colorBgIconInactive");
    names.insert(ColorBorderBgIconInactiveRole, "colorBorderBgIconInactive");
    names.insert(ColorBgIconActiveRole, "colorBgIconActive");
    names.insert(ColorBorderBgIconActiveRole, "colorBorderBgIconActive");
    names.insert(ColorShadowBorderBgIconRole, "colorShadowBorderBgIcon");
    names.insert(VisibleRole, "visible");
    names.insert(StateIndicatorIconRole, "stateIcon");
    return names;
}

void IndicatorListModel::addIndicatorIcon(IndicatorIcon* indicatorIcon)
{
    const int index = m_indicatorIconList.size();
    beginInsertRows(QModelIndex(), index, index);
    m_indicatorIconList.append(indicatorIcon);
    endInsertRows();
}

void IndicatorListModel::removeIndicatorIcon(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_indicatorIconList.removeAt(index);
    endRemoveRows();
}

void IndicatorListModel::removeLastIndicatorIcon()
{
    removeIndicatorIcon(m_indicatorIconList.size() - 1);
}

void IndicatorListModel::changeVisibility(QString screen)
{
    if (screen == "MainGauge") {
        // Display all
        setData(index(IndicatorPosition::REVERSE_MODE), true, VisibleRole);
        setData(index(IndicatorPosition::ENGINE_TROUBLE), true, VisibleRole);
        setData(index(IndicatorPosition::OIL), true, VisibleRole);
        setData(index(IndicatorPosition::COOL_LANT), true, VisibleRole);
        setData(index(IndicatorPosition::ABS), true, VisibleRole);

    } else {
        setData(index(IndicatorPosition::REVERSE_MODE), false, VisibleRole);
        setData(index(IndicatorPosition::ENGINE_TROUBLE), false, VisibleRole);
        setData(index(IndicatorPosition::OIL), false, VisibleRole);
        setData(index(IndicatorPosition::COOL_LANT), false, VisibleRole);
        setData(index(IndicatorPosition::ABS), false, VisibleRole);
    }
}

void IndicatorListModel::setIndicatorList(QList<IndicatorIcon *> list)
{
    for (auto item : list)
    {
        addIndicatorIcon(item);
    }
}

void IndicatorListModel::forwardStateIconfromCAN()
{
    if (m_indicatorStructData.side_stand) {
        setData(index(IndicatorPosition::SIDE_STAND), "Active", StateIndicatorIconRole);
    } else {
        setData(index(IndicatorPosition::SIDE_STAND), "Inactive", StateIndicatorIconRole);
    }

    if (m_indicatorStructData.reverse_mode) {
        setData(index(IndicatorPosition::REVERSE_MODE), "Active", StateIndicatorIconRole);
    } else {
        setData(index(IndicatorPosition::REVERSE_MODE), "Inactive", StateIndicatorIconRole);
    }

    if (m_indicatorStructData.engine_trouble) {
        setData(index(IndicatorPosition::ENGINE_TROUBLE), "Active", StateIndicatorIconRole);
    } else {
        setData(index(IndicatorPosition::ENGINE_TROUBLE), "Inactive", StateIndicatorIconRole);
    }

    if (m_indicatorStructData.oil_lower > OIL_LOWER_LIMIT) {
        setData(index(IndicatorPosition::OIL), "Active", StateIndicatorIconRole);
    } else {
        setData(index(IndicatorPosition::OIL), "Inactive", StateIndicatorIconRole);
    }

    if (m_indicatorStructData.coolant_tempt > COOLANT_TEMP_LIMIT) {
        setData(index(IndicatorPosition::COOL_LANT), "Active", StateIndicatorIconRole);
    } else {
        m_indicatorIconList[6]->setStateIcon("Inactive");
        setData(index(IndicatorPosition::COOL_LANT), "Inactive", StateIndicatorIconRole);
    }

    if (m_indicatorStructData.abs) {
        setData(index(IndicatorPosition::ABS), "Active", StateIndicatorIconRole);
    } else {
        setData(index(IndicatorPosition::ABS), "Inactive", StateIndicatorIconRole);
    }

    const QModelIndex startIndex = index(0);
    const QModelIndex endIndex = index(m_indicatorIconList.count() - 1);

    // Only the StateIndicatorIconRole field
    emit dataChanged(startIndex, endIndex, QVector<int>() << StateIndicatorIconRole);
}

void IndicatorListModel::forwardStateIconFromSocket()
{
    if (m_indicatorStructData.turn_left) {
        setData(index(IndicatorPosition::TURN_LEFT), "Active", StateIndicatorIconRole);
    } else {
        setData(index(IndicatorPosition::TURN_LEFT), "Inactive", StateIndicatorIconRole);
    }

    if (m_indicatorStructData.head_light) {
        setData(index(IndicatorPosition::HEAD_LIGHT), "Active", StateIndicatorIconRole);
    } else {
        setData(index(IndicatorPosition::HEAD_LIGHT), "Inactive", StateIndicatorIconRole);
    }

    if (m_indicatorStructData.turn_right) {
        setData(index(IndicatorPosition::TURN_RIGHT), "Active", StateIndicatorIconRole);
    } else {
        setData(index(IndicatorPosition::TURN_RIGHT), "Inactive", StateIndicatorIconRole);
    }

    const QModelIndex startIndex = index(0);
    const QModelIndex endIndex = index(m_indicatorIconList.count() - 1);

    // Only the StateIndicatorIconRole field
    emit dataChanged(startIndex, endIndex, QVector<int>() << StateIndicatorIconRole);
}
