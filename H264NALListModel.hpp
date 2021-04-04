#ifndef H264NALLISTMODEL_H
#define H264NALLISTMODEL_H

#include <QAbstractTableModel>
#include <QByteArray>
#include <h264_stream.h>
#include <QVector>
#include <QFile>

class H264NALListModel : public QAbstractTableModel
{
    Q_OBJECT

    using NalReadBuffer = std::vector<uint8_t>;

    struct H264Deleter
    {
        static void cleanup(h264_stream_t *p) { h264_free(p); }
    };

    struct H264NALIndexEntry
    {
        int type;
        int ref_idc;
        ptrdiff_t offset;
        size_t size;
        size_t parsed_size;
    };

    QVector<H264NALIndexEntry> _nalListIndex;

    mutable QFile _bitstream;
    mutable NalReadBuffer _readBuffer;

    mutable QScopedPointer<h264_stream_t, H264Deleter> _parser;

public:
    H264NALListModel(QObject *parent = nullptr);

    bool setFile(const QString &filename);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;

signals:
    void parsingProgress(qreal percent);

private:
    void parseBitstream();
};

#endif // H264NALLISTMODEL_H
