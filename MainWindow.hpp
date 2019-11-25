#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>
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
    Ui::MainWindow *ui;
    QShortcut openShortcut;
    H264NALListModel *m_currentH264Model;

private slots:
    void onOpenFile();
    void onNalTableItemSelected(const QItemSelection &, const QItemSelection &);
};

#endif // MAINWINDOW_H
