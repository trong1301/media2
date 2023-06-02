#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

// Qt include
#include <QObject>

//!
//! \brief The ViewManager class manage the screen Id
//!
class ViewManager : public QObject {
    Q_OBJECT

    //!
    //! \brief Expose the m_viewState member to qml
    //!
    Q_PROPERTY(QString viewState READ getViewState NOTIFY viewStateChanged)

    //!
    //! \brief Expose the m_lastViewState member to qml
    //!
    Q_PROPERTY(QString lastViewState READ getLastViewState WRITE setLastViewState NOTIFY lastViewStateChanged)

public:
    //!
    //! \brief ViewManager
    //! \param parent
    //!
    explicit ViewManager(QObject* parent = nullptr);
    ~ViewManager();

    //!
    //! \brief getViewState
    //! \return
    //!
    QString getViewState();

    //!
    //! \brief getLastViewState
    //! \return
    //!
    QString getLastViewState();

    //!
    //! \brief setLastViewState
    //! \param viewState
    //!
    void setLastViewState(const QString& viewState);

    //!
    //! \brief Expose the requestChangeViewState to qml
    //! \param from
    //! \param to
    //!
    Q_INVOKABLE void requestChangeViewState(QString from, QString to);

    //!
    //! \brief isNativeBuild
    //! \return
    //!
    Q_INVOKABLE bool isNativeBuild();

    //!
    //! \brief isRotated180
    //! \return
    //!
    Q_INVOKABLE bool isRotated180();

    //!
    //! \brief getSystemPicturesPath
    //! \return
    //!
    Q_INVOKABLE QString getSystemPicturesPath();

signals:
    //!
    //! \brief Emit this signal in order to inform QML about changes
    //! \param viewState
    //!
    void viewStateChanged(QString viewState);

    //!
    //! \brief Emit this signal in order to inform QML about changes
    //! \param viewState
    //!
    void lastViewStateChanged(QString viewState);

private:
    //!
    //! \brief setViewState
    //! \param viewState
    //!
    void setViewState(const QString& viewState);

    //!
    //! \brief m_viewState stores the current viewState
    //!
    QString m_viewState;

    //!
    //! \brief m_lastViewState stores the previous viewState
    //!
    QString m_lastViewState;

    //!
    //! \brief IMG_PATH
    //!
    const std::string IMG_PATH;
};

#endif // VIEWMANAGER_H
