#ifndef MEDIAITEMDATAMODEL_H
#define MEDIAITEMDATAMODEL_H

// Qt includes
#include <QObject>
#include <QUrl>

class MediaItemDataModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl mediaDir READ mediaDir WRITE setMediaDir NOTIFY mediaDirChanged)
    Q_PROPERTY(QString mediaFileName READ mediaFileName WRITE setMediaFileName NOTIFY mediaFileNameChanged)
    Q_PROPERTY(QString mediaTitle READ mediaTitle WRITE setMediaTitle NOTIFY mediaTitleChanged)
    Q_PROPERTY(QString mediaSinger READ mediaSinger WRITE setMediaSinger NOTIFY mediaSingerChanged)
    Q_PROPERTY(int mediaDuration READ mediaDuration WRITE setMediaDuration NOTIFY mediaDurationChanged)

public:
    explicit MediaItemDataModel(QObject *parent = nullptr);

    QUrl mediaDir() const;
    void setMediaDir(const QUrl &newMediaDir);

    QString mediaFileName() const;
    void setMediaFileName(const QString &newMediaFileName);

    QString mediaTitle() const;
    void setMediaTitle(const QString &newMediaTitle);

    QString mediaSinger() const;
    void setMediaSinger(const QString &newMediaSinger);

    int mediaDuration() const;
    void setMediaDuration(int newMediaDuration);

signals:
    void mediaDirChanged();
    void mediaFileNameChanged();
    void mediaTitleChanged();
    void mediaSingerChanged();
    void mediaDurationChanged();

private:
    QUrl m_mediaDir;
    QString m_mediaFileName;
    QString m_mediaTitle;
    QString m_mediaSinger;
    int m_mediaDuration;
};
#endif // MEDIAITEMDATAMODEL_H
