#ifndef CHECKTASK_H
#define CHECKTASK_H
#include <QString>
#include <QMap>

#include <QObject>

class CheckTask : public QObject {

Q_OBJECT

public:
    CheckTask(QObject* parent, const QString & tname, const QString & sname, bool bCheck, int weight );
    ~CheckTask();
public slots:
    //Call From UI/Goup/State
    void startexecute();
    void stopexecute();
    void disabletask();
    void setParameters(const QString& key,const QString& val);

    //From DBus
    void progressUpdate(const int currentcompletion, const QString& currentstatus);
    void errorUpdate(const QString& errordescrition);
    void dataUpdate(const QVariantList& result);

signals:

    void errorFindSig();// To UI & Group
    void completeSig();// To UI & Group


    void dataUpdateSig(const QVariantList& result);// To UI
    void dataCountUpdateSig(const int totalproblems ,const int totalinfomations );//To Group

    void completerateUpdateSig(const int completerate ,const QString & status);//To UI
    void progressUpdateSig(const int completeunit ,const QString & status);//To Group





    //To Dus
    void startTaskSig(const QString& scenename, const QString& taskname, const QMap<QString,QString>& parameters );
    void stopTaskSig(const QString& scenename, const QString& taskname);
public:
    bool enabled;
    bool badinfoCheck;
    int weight;
    QString taskname;
    QString scenename;

    bool start;
    int completerate;

    bool error;
    QString currentstatus;

    bool errorfind;
    int totalproblems;
    int totalinfomations;

    QMap<QString,QString> parameters;

};

#endif // CHECKTASK_H