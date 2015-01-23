
#include "mainwindow.h"

#include "src/ui/main/mainwidget.h"
#include "src/ui/onekeycheck/onekeycheckwidget.h"
#include "src/ui/common/sysbuttongroup.h"
#include "src/ui/base/staticbutton.h"
#include <src/state/onekeycheckstate.h>
#include <src/util/toolutil.h>
#include <src/util/interfacefortool.h>
#include <src/ui/main/mainwindow.h>
#include <QApplication>
#include <QFile>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QWindow>
#include <QIcon>
#include <QDebug>
#include <QEvent>
#include <QThread>
#include <QDBusConnection>
#include <QDBusError>
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent)
    : ShadowWidget(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    this->initDBus();
    this->initUI();
    this->initAnim();
    this->initConnect();
}

void MainWindow::initUI()
{
    //this->setFixedSize(900, 600);
    setMaximumWidth(900);
    setMaximumHeight(600);
    this->setWindowTitle(tr("保密检查工具"));
    this->setWindowIcon(QIcon(":image/common/title/logo"));
    mainWidget = new MainWidget(this);
    mainWidget->setObjectName("mainwidget");

    oneKeyCheckWidget = new OneKeyCheckWidget(this);
    oneKeyCheckWidget->setObjectName("onekeycheckwidget");
    oneKeyCheckWidget->hide();

    widgetSwitchAnimation = new QParallelAnimationGroup(this);

    sysButtonGroup = new SysButtonGroup(this);
    sysButtonGroup->raise();
    sysButtonGroup->move(840, 1);

    //closeButton = new QPushButton("Hello",this);
    //connect(closeButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
}

void MainWindow::initConnect()
{
    connect(sysButtonGroup->minButton, SIGNAL(buttonClicked()), this, SLOT(showMin()));
    connect(sysButtonGroup->closeButton, SIGNAL(buttonClicked()), this, SLOT(closeWidget()));
    connect(mainWidget->onekeychecklogo, SIGNAL(buttonClicked()), this, SLOT(maintoonekeycheck()));
    connect(oneKeyCheckWidget->returnbtn, SIGNAL(buttonClicked()), this, SLOT(onekeychecktomain()));
}

void MainWindow::initAnim() {}

void MainWindow::maintoonekeycheck()
{
    switchWidgetToLeft(mainWidget, oneKeyCheckWidget);
}

void MainWindow::onekeychecktomain()
{
    switchWidgetToRight(oneKeyCheckWidget , mainWidget);
}

void MainWindow::switchWidgetToLeft(QWidget* currentWidget, QWidget* showWidget)
{

    showWidget->move(QPoint(900, 0));
    showWidget->show();

    widgetSwitchAnimation->clear();

    QPropertyAnimation* currentAnimation = new QPropertyAnimation(currentWidget, "pos");
    currentAnimation->setDuration(500);
    currentAnimation->setStartValue(currentWidget->pos());
    currentAnimation->setEndValue(QPoint(currentWidget->pos().x() - 900, currentWidget->pos().y()));

    QPropertyAnimation* showAnimation = new QPropertyAnimation(showWidget, "pos");
    showAnimation->setDuration(500);
    showAnimation->setStartValue(showWidget->pos());
    showAnimation->setEndValue(QPoint(showWidget->pos().x() - 900, showWidget->pos().y()));

    widgetSwitchAnimation->addAnimation(currentAnimation);
    widgetSwitchAnimation->addAnimation(showAnimation);
    widgetSwitchAnimation->start();
}

void MainWindow::switchWidgetToRight(QWidget* currentWidget, QWidget* showWidget)
{

    showWidget->move(QPoint(-900, 0));
    showWidget->show();

    widgetSwitchAnimation->clear();

    QPropertyAnimation* currentAnimation = new QPropertyAnimation(currentWidget, "pos");
    currentAnimation->setDuration(500);
    currentAnimation->setStartValue(currentWidget->pos());
    currentAnimation->setEndValue(QPoint(currentWidget->pos().x() + 900, currentWidget->pos().y()));

    QPropertyAnimation* showAnimation = new QPropertyAnimation(showWidget, "pos");
    showAnimation->setDuration(500);
    showAnimation->setStartValue(showWidget->pos());
    showAnimation->setEndValue(QPoint(showWidget->pos().x() + 900, showWidget->pos().y()));

    widgetSwitchAnimation->addAnimation(currentAnimation);
    widgetSwitchAnimation->addAnimation(showAnimation);
    widgetSwitchAnimation->start();
}

void MainWindow::showMin()
{
    showMinimized();
}

void MainWindow::closeWidget()
{
    qApp->quit();
}

void MainWindow::initDBus()
{
    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "Please check your system settings and try again.\n");
    }

    if (!connection.registerService("com.example.bmjc")) {
        qDebug() << connection.lastError().message();
    }

    //Init State In Other Thread
    statethread = new QThread(this);
    interfaceForTool = new InterfaceForTool();
    if (!connection.registerObject("/bmjc/ui", interfaceForTool, QDBusConnection::ExportAllSlots)) {
        qDebug() << "connection.lastError().message()";
    }
    interfaceForTool->moveToThread(statethread);
    oneKeyCheckState = new OneKeyCheckState();
    oneKeyCheckState->moveToThread(statethread);
    statethread->start();
}
