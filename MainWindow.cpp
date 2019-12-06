#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_currentH264Model(NULL),
    fileChooser(this, tr("Open H264 file"), QString(), tr("H264 Files (*.h264 *.264)")),
    openShortcut(QKeySequence::Open, &fileChooser, SLOT(open())),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&fileChooser, SIGNAL(fileSelected(const QString&)), this, SLOT(openFile(const QString &)));
    connect(ui->openPushButton, SIGNAL(clicked()), &fileChooser, SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(const QString& filename)
{
    if (filename.isEmpty()) return;

    QFileInfo fileInfo(filename);

    ui->filePathLineEdit->setText(fileInfo.absoluteFilePath());

    H264NALListModel *oldModel = NULL;
    if (m_currentH264Model)
    {
        oldModel = m_currentH264Model;
    }

    m_currentH264Model = new H264NALListModel(filename, this);

    ui->nalTableView->setModel(m_currentH264Model);
/*
    for (int c = 0; c < ui->nalTableView->horizontalHeader()->count(); ++c)
    {
        ui->nalTableView->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
*/
    if (oldModel)
    {
        ui->nalTableView->selectionModel()->disconnect();
        delete oldModel;
    }

    connect(ui->nalTableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(onNalTableItemSelected(const QItemSelection &, const QItemSelection &)));
}

void MainWindow::onNalTableItemSelected(const QItemSelection &selected, const QItemSelection &deselected)
 {
    auto index = selected.indexes().first();

    Q_UNUSED(deselected);

    if (m_currentH264Model)
    {
        ui->nalPlainTextEdit->setPlainText(m_currentH264Model->data(index, Qt::UserRole).toString());
    }
}
