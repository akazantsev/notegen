#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include "dottemplate.h"

namespace Ui
{
class MainWindow;
}

class QRegExpValidator;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void print();
    void cutColorChanged(QString colorStr);
    void pageColorChanged(QString colorStr);

private:
    void createActions();
    void createMenus();
    void createConnections();

    QAction *printAction;
    QAction *quitAction;
    DotTemplate tmpl;
    Ui::MainWindow *ui;
    QRegExpValidator *colorValidator;
};

#endif // MAINWINDOW_H
