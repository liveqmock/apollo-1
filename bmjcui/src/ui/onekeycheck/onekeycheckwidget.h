#ifndef ONEKEYCHECKWIDGET_H
#define ONEKEYCHECKWIDGET_H
#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/taskscene.h"
class QStandardItemModel;
class QTableView;
class StaticButton;
class QLabel;
class TabButton;


class OneKeyCheckWidget : public BaseStyleWidget
{
    Q_OBJECT
public:
    explicit OneKeyCheckWidget(QWidget* parent = 0);
    ~OneKeyCheckWidget();
    QString getSupportedScene();
    QList<QString> getSupportedFunctions();

private:
    void initUI();
    void initConnect();
    void initModel();

signals:

public slots:

    void startCheck();
    void cancelCheck();
    void updateCheckingElapsedTime();
    void completerateUpdate(const int completerate, const QString& status);
    void dataCountUpdate(const int totalproblems ,const int totalinfomations);

public:

    TabButton* deviceconnectionbtn;
    TabButton* netbrowserbtn;
    TabButton* systemsecuritybtn;
    TabButton* securitythreatbtn;
    TabButton* usbcheckbtn;
    TabButton* filecheckbtn;
    TabButton* tjcheckbtn;

    QStandardItemModel * cpumodel ;

    QTableView *    checkresult ;

    StaticButton* returnbtn;
    StaticButton* startcheckbtn;
    StaticButton* cancelcheckbtn;

    QLabel* onekeychecklogo;
    QLabel* descriptiontitle;
    QLabel* description;

    QLabel* progressbar_background;
    QLabel* progressbar_front;
    QLabel* checkingElapsedTime;

    QTimer *checkingElapsedTimer;
    //QLabel* vline;
    //QLabel* hline;

    unsigned int checkingStartTime;
};

#endif // ONEKEYCHECKWIDGET_H
