#ifndef ONEKEYCHECKSTATE_H
#define ONEKEYCHECKSTATE_H

#include <QObject>
class CheckTask;
class CheckTaskGroup;
class MainWindow;
class InterfaceForTool;
class ToolUtil;

class OneKeyCheckState : public QObject {
    Q_OBJECT

public:
    explicit OneKeyCheckState(QObject* parent , MainWindow* mainwindow, InterfaceForTool* interfaceForTool,
                              ToolUtil* toolUtil);
    ~OneKeyCheckState();
    void inittasks(ToolUtil* toolUtil);
    void initConStateGroup();
    void initConInterfaceTask( InterfaceForTool* interfaceForTool);
    void initConUIState(MainWindow * mainwindow);

signals:
    void errorFindSig();// To UI
    void completeSig();// To UI

    //void progressUpdateSig(const int completeunit ,const QString & status);
    void completerateUpdateSig(const int completerate ,const QString & status);// To UI

    void dataCountUpdateSig(const int totalproblems ,const int totalinfomations );// To UI
    void startSig();// To Task/Group
    void stopSig();// To Task/Group
    void disableSig();// To Task/Group
public slots:
    //Call UI
    void startexcute();
    void stopexcute();
    void disablescene();
    //From Task

    void progressUpdate(const int completeunit ,const QString & status);
    void dataCountUpdate(const int totalproblems ,const int totalinfomations);

private:
    bool enabled;
    bool start;

    QString currentstatus;
    bool errorfind;

    int totalproblems;
    int totalinfomations;

    int totalcompleteunit;
    int currentcompleteunit;

public:

    CheckTaskGroup* basicInfo;
    CheckTask* operatingSystemInfo;
    CheckTask* cpuInfo;
    CheckTask* biosInfo;
    CheckTask* motherboardInfo;
    CheckTask* memoryInfo;
    CheckTask* graphicsCardInfo;

    CheckTaskGroup* deviceConnection;
    CheckTask* hardDiskInfo;
    CheckTask* virtualMachineInfo;
    CheckTask* netConfig;
    CheckTask* adapterDevice;
    CheckTask* printDevice;
    CheckTask* blueToothDevice;

    CheckTaskGroup* systemSecurity;
    CheckTask* patchNotInstalled;
    CheckTask* systemService;
    CheckTask* systemProcess;
    CheckTask* evenProduct;
    CheckTask* timeSwitchMachine;
    CheckTask* securitySoftware;

    CheckTaskGroup* securityThreat;
    CheckTask* securityPolicy;
    CheckTask* openPort;
    CheckTask* sharingInfo;
    CheckTask* networkSoftware;
    CheckTask* groupInfo;
    CheckTask* userInfo;
    CheckTask* databaseInfo;
    CheckTask* eventLog;
    CheckTask* userAuthentication;

    CheckTaskGroup* usbCheck;
    CheckTask* usbRoutineCheck;
    //CheckTask*	usbDepthCheck

    CheckTaskGroup* netRecordsCheck;
    CheckTask* netRecordsRoutineCheck;
   // CheckTask* netRecordsDepthCheck;

    CheckTaskGroup* fileCheck;
    CheckTask* fileRoutineCheck;
   // CheckTask* deletedFileRecovery;
   // CheckTask* fileFragmentsCheck;

    CheckTaskGroup* trojanCheck;
    //CheckTask*	networkWeapon
    CheckTask* threatDocument;


};

#endif // ONEKEYCHECKSTATE_H
