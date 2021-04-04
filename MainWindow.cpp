#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QProgressBar>
#include <QFileInfo>
#include <QDebug>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _fileChooser(this, tr("Open H264 file"), QString(), tr("H264 Files (*.h264 *.264)")),
    _openShortcut(QKeySequence::Open, &_fileChooser, SLOT(open())),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    connect(&_streamModel, &H264NALListModel::parsingProgress, [this](qreal progress) {
        auto val = static_cast<int>(progress * 100);
        _ui->progressBar->setVisible(!(val == 100));
        _ui->progressBar->setValue(val);
    });

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

    _ui->progressBar->setTextVisible(true);

    _ui->filePathLineEdit->setText(fileInfo.absoluteFilePath());
    _streamModel.setFile(filename);
    _ui->nalTableView->setModel(&_streamModel);

    connect(_ui->nalTableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(onNalTableItemSelected(const QItemSelection &, const QItemSelection &)));
}

void MainWindow::onNalTableItemSelected(const QItemSelection &selected, const QItemSelection &deselected)
 {
    auto index = selected.indexes().first();

    Q_UNUSED(deselected)

    _ui->nalPlainTextEdit->setPlainText(_streamModel.data(index, Qt::UserRole).toString());
}
