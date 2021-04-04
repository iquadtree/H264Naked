#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QShortcut>
#include <QProgressBar>
#include <QItemSelection>
#include "H264NALListModel.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    H264NALListModel _streamModel;
    QFileDialog _fileChooser;
    QShortcut _openShortcut;
    Ui::MainWindow *_ui;

private slots:
    void openFile(const QString& filename);
    void onNalTableItemSelected(const QItemSelection &, const QItemSelection &);
};

#endif // MAINWINDOW_H
