#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _currentH264Model(nullptr),
    _fileChooser(this, tr("Open H264 file"), QString(), tr("H264 Files (*.h264 *.264)")),
    _openShortcut(QKeySequence::Open, &_fileChooser, SLOT(open())),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    connect(&_fileChooser, SIGNAL(fileSelected(const QString&)), this, SLOT(openFile(const QString &)));
    connect(_ui->openPushButton, SIGNAL(clicked()), &_fileChooser, SLOT(open()));

    if (QApplication::arguments().size() > 1)
        openFile(QApplication::arguments().at(1));
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::openFile(const QString& filename)
{
    if (filename.isEmpty()) return;

    QFileInfo fileInfo(filename);

    if (!fileInfo.isReadable())
    {
        QMessageBox::critical(this, tr("Error"), tr("Can't open file %1.").arg(filename));
        return;
    }

    _ui->filePathLineEdit->setText(fileInfo.absoluteFilePath());

    H264NALListModel *oldModel = nullptr;
    if (_currentH264Model)
    {
        oldModel = _currentH264Model;
    }

    _currentH264Model = new H264NALListModel(this);
    _currentH264Model->setFile(filename);

    _ui->nalTableView->setModel(_currentH264Model);

    if (oldModel)
    {
        _ui->nalTableView->selectionModel()->disconnect();
        delete oldModel;
    }

    connect(_ui->nalTableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(onNalTableItemSelected(const QItemSelection &, const QItemSelection &)));
}

void MainWindow::onNalTableItemSelected(const QItemSelection &selected, const QItemSelection &deselected)
 {
    auto index = selected.indexes().first();

    Q_UNUSED(deselected)

    if (_currentH264Model)
    {
        _ui->nalPlainTextEdit->setPlainText(_currentH264Model->data(index, Qt::UserRole).toString());
    }
}
