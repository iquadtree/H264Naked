#ifndef H264NALLISTMODEL_H
#define H264NALLISTMODEL_H

#include <QAbstractTableModel>
#include <QByteArray>
#include <h264_stream.h>
#include <QVector>
#include <QPair>


class H264NALListModel : public QAbstractTableModel
{
    Q_OBJECT

    struct H264Deleter
    {
        static void cleanup(h264_stream_t *p) { h264_free(p); }
    };

    struct H264NALIndexEntry
    {
        int type;
        int ref_idc;
        uint8_t *data;
        int size;
        int parsed_size;
    };

    QString m_filename;
    QByteArray m_fileBuffer;
    QVector<H264NALIndexEntry> m_nalListIndex;

    mutable QScopedPointer<h264_stream_t, H264Deleter> m_bitstream;

public:
    H264NALListModel(const QString &filename, QObject *parent = NULL);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    void load();
    void parse();
};

#endif // H264NALLISTMODEL_H
