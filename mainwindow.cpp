#include <QtWidgets>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "templateview.h"
#include "dottemplate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    createMenus();

    QRegExp colorRegExp("#[0-9A-Fa-f]{8}");
    colorValidator = new QRegExpValidator(colorRegExp, this);

    ui->previewWidget->setModel(&tmpl);
    ui->borderColorEdit->setText(tmpl.pagePenColor().name(QColor::HexArgb));
    ui->borderColorEdit->setValidator(colorValidator);
    ui->cutColorEdit->setText(tmpl.cutPenColor().name(QColor::HexArgb));
    ui->cutColorEdit->setValidator(colorValidator);

    createConnections();

    ui->pageWidthWidget->setSuffix(tr("mm"));
    ui->pageWidthWidget->setRange(0.25, 2.50);
    ui->pageWidthWidget->setValue(tmpl.pagePenWidth());
    ui->cutWidthWidget->setSuffix(tr("mm"));
    ui->cutWidthWidget->setRange(0.25, 2.50);
    ui->cutWidthWidget->setValue(tmpl.cutPenWidth());
    ui->dotSizeWidget->setSuffix(tr("mm"));
    ui->dotSizeWidget->setRange(0.25, 2.50);
    ui->dotSizeWidget->setValue(tmpl.dotSize());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print()
{
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Rejected)
        return;

    QPainter printerPainter;
    printerPainter.begin(&printer);
    tmpl.render(&printerPainter);
    printerPainter.end();
}

void MainWindow::cutColorChanged(QString colorStr)
{
    int pos = 0;
    if(colorValidator->validate(colorStr, pos) == QValidator::Acceptable)
    {
        tmpl.setCutPenColor(QColor(colorStr));
    }
}

void MainWindow::pageColorChanged(QString colorStr)
{
    int pos = 0;
    if(colorValidator->validate(colorStr, pos) == QValidator::Acceptable)
    {
        tmpl.setPagePenColor(QColor(colorStr));
    }
}

void MainWindow::createActions()
{
    printAction = new QAction(tr("&Print"), this);
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createMenus()
{
    auto fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);
}

void MainWindow::createConnections()
{
    connect(ui->cutColorEdit, SIGNAL(textChanged(QString)),
            this, SLOT(cutColorChanged(QString)));
    connect(ui->borderColorEdit, SIGNAL(textChanged(QString)),
            this, SLOT(pageColorChanged(QString)));
    connect(ui->pageWidthWidget, SIGNAL(valueChanged(double)),
            &tmpl, SLOT(setPagePenWidth(double)));
    connect(ui->cutWidthWidget, SIGNAL(valueChanged(double)),
            &tmpl, SLOT(setCutPenWidth(double)));
    connect(ui->dotSizeWidget, SIGNAL(valueChanged(double)),
            &tmpl, SLOT(setDotSize(double)));
}
