#ifndef FRONTEND_H
#define FRONTEND_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QtNetwork/QNetworkAccessManager>
#include <QSlider>
#include <vector>
#include <QJsonArray>
#include <QJsonObject>
#include <QSignalMapper>
#include <QDesktopWidget>
#include <QApplication>
#include <QComboBox>
#include <QCheckBox>
#include <QScrollArea>
#include <QGridLayout>

class Login : public QWidget {
Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);

private slots:
    void LoginPage();
    void Authorization();
    void LoginResult(QNetworkReply* reply);
    void Logout();
    void ChangeLayoutToApp();
    void ToPresets(int i);
    void ToMy();
    void GetPresetsList(QNetworkReply* reply);
    void DownloadPresetFile();
    void SavePresetFile(QNetworkReply* reply);
    void ChangePresetsPage();
    void GetInstruments();
    void DownloadInstruments(QNetworkReply* reply);
    void ChangePath();
    void ChangePathTextButton();

private:
    QRectF const screenSize = QApplication::desktop()->screenGeometry();
    QByteArray tokenByte;
    QJsonArray jsonArr;
    QJsonArray jsonArrInstruments;
    QString currentId;
    int currentIndex;
    int lastPage;
    int currentPage;
    QString username;
    QString defaultPath = "C:/";
    QString currentPathDownload;
    QVector<QString> pathsList;

    QScrollArea* scrollArea;
    QGridLayout* gridLayout;
    QGridLayout* gridChangePageLayout;
    QGridLayout* gridHeaderLayout;
    QGridLayout* gridPresetsLayout;
    QGridLayout* gridMyLayout;
    //QGridLayout* gridPresetWidgetLayout;

    QWidget *containerForPresets;
    QWidget *containerForHeader;
    QWidget *containerForChangePageButtons;
    QWidget *containerForMy;
    QLabel *emptyWidget;

    QNetworkAccessManager* managerAuthorization;
    QNetworkAccessManager* manager1;
    QNetworkAccessManager* manager2;
    QNetworkAccessManager* manager3;

    QLabel* logoLabel;
    QLabel* textPresetShare;
    QLabel* textPage;
    QLabel* textLogin;
    QLabel* textPassword;
    QLabel* warnLoginText;
    QLineEdit* loginLineEdit;
    QLineEdit*  passwordLineEdit;
    QPushButton *loginButton;

    QPushButton *logoutButton;
    QComboBox *pathComboBox;
    QPushButton *pathPushButton;
    QCheckBox *openExplorerCheckBox;
    QLabel *openExplorerLabel;

    QPushButton *mainButton;
    QPushButton *presetsButton;
    QPushButton *bundlesButton;
    QPushButton *questButton;
    QPushButton *trackButton;
    QPushButton *communityButton;
    QPushButton *myButton;
    QSlider *volumeSlider;
    QLineEdit *presetsSearch;
    QPushButton *searchButton;

    QVector<QLabel*> presetsNamesList;
    QVector<QLabel*> presetsAuthorsList;
    QVector<QPushButton*> presetsButtonsList;
    QVector<QLabel*> presetsSynthNamesList;
    QVector<QLabel*> presetsGenreNamesList;
    QVector<QLabel*> presetsTypeNamesList;
    QVector<QString> presetsIdsList;
    QVector<QString> presetsIdsSynthsList;
    QVector<QPushButton*> presetsPageButtonsList;



};
#endif // FRONTEND_H
