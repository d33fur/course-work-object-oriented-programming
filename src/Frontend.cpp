#include "Frontend.h"
#include <QGridLayout>
#include <QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScrollArea>
#include <iostream>
#include <QPalette>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <fstream>

Login::Login(QWidget *parent) : QWidget(parent) {
    LoginPage();

}

void Login::LoginPage() {
    QFont f("Montserrat", 10, QFont::Normal);

    QPixmap logoPicture(":/Img/logo.png");
    logoLabel = new QLabel(this);
    logoLabel->move(-120, 0);
    logoLabel->resize(1000, 1000);
    logoLabel->setPixmap(logoPicture);
    logoLabel->setVisible(true);

    QImage logoText(":/Img/PresetShareText.png");
    textPresetShare = new QLabel(this);
    textPresetShare->move(290, 90);
    textPresetShare->setPixmap(QPixmap::fromImage(logoText));
    textPresetShare->setVisible(true);

    warnLoginText = new QLabel(this);
    warnLoginText->move(280, 390);
    warnLoginText->resize(300, 30);
    warnLoginText->setVisible(true);
    warnLoginText->setFont(f);

    textLogin = new QLabel("Login", this);
    textLogin->move(150, 200);
    textLogin->resize(200, 30);
    textLogin->setVisible(true);
    textLogin->setFont(f);

    textPassword = new QLabel("Password/Token", this);
    textPassword->move(150, 240);
    textPassword->resize(200, 30);
    textPassword->setVisible(true);
    textPassword->setFont(f);

    loginLineEdit = new QLineEdit("", this);
    loginLineEdit->move(300, 200);
    loginLineEdit->resize(200, 30);
    loginLineEdit->setVisible(true);
    loginLineEdit->setFont(f);

    passwordLineEdit = new QLineEdit("", this);
    passwordLineEdit->move(300, 240);
    passwordLineEdit->resize(200, 30);
    passwordLineEdit->setVisible(true);
    passwordLineEdit->setFont(f);

    loginButton = new QPushButton("Sign in", this);
    loginButton->move(300, 290);
    loginButton->resize(200, 30);
    loginButton->setVisible(true);
    loginButton->setFont(f);

    rememberMeText = new QLabel("Remember me", this);
    rememberMeText->move(150, 330);
    rememberMeText->resize(200, 30);
    rememberMeText->setVisible(true);
    rememberMeText->setFont(f);

    rememberMeCheckBox = new QCheckBox(this);
    rememberMeCheckBox->move(300, 330);
    rememberMeCheckBox->resize(30, 30);
    rememberMeCheckBox->setVisible(true);
    rememberMeCheckBox->setFont(f);

    QPalette palette;
    palette.setColor(QPalette::Base, QColor("#1b1e20"));
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::ButtonText, QColor("#a395cc"));
    palette.setColor(QPalette::Window, QColor("#a395cc"));
    palette.setColor(QPalette::Button, QColor("#a395cc"));

    loginLineEdit->setPalette(palette);
    passwordLineEdit->setPalette(palette);
    textLogin->setPalette(palette);
    textPassword->setPalette(palette);
    warnLoginText->setPalette(palette);
    loginButton->setAutoFillBackground(true);
    loginButton->setPalette(palette);
    loginButton->update();

    connect(loginButton, &QPushButton::clicked, this, &Login::Authorization);

    std::ifstream inputStream("temp.txt");
    if (!inputStream)
        qDebug() << "Can't open user settings file!";
    else {
        std::string line;
        getline(inputStream, line);
        loginLineEdit->setText(QString::fromStdString(line));
        getline(inputStream, line);
        passwordLineEdit->setText(QString::fromStdString(line));
        loginButton->click();
    }
}

void Login::Authorization() {
    managerAuthorization = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "json");
    tokenByte = passwordLineEdit->text().toUtf8();
    request.setRawHeader("Authorization", tokenByte);
    request.setUrl(QUrl("https://presetshare.com/app/check"));

    qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
    managerAuthorization->get(request);
    if(rememberMeCheckBox->checkState()) {
        std::ofstream outputStream;
        outputStream.open("temp.txt");
        outputStream << loginLineEdit->text().toStdString() << std::endl;
        outputStream << passwordLineEdit->text().toStdString() << std::endl;
        outputStream.close();
    }
    connect(managerAuthorization, &QNetworkAccessManager::finished, this, &Login::LoginResult);
}

void Login::LoginResult(QNetworkReply* reply) {
    if(reply->error()) {
        warnLoginText->setText("Wrong login or password/token");
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        QString strReply = (QString) reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObj = jsonDoc.object();
        qDebug() << "Downloading user info is completed";
        if(jsonObj["username"].toString() == loginLineEdit->text()) {
            username = jsonObj["username"].toString();
            ChangeLayoutToApp();
            qDebug() << "LOGGED IN";
        } else {
            warnLoginText->setText("Wrong login or password/token");
            qDebug() << "NOT LOGGED IN";
        }
    }
}

void Login::ChangeLayoutToApp() {
    resize(800, 600);
    setMinimumSize(800, 600);
    setMaximumSize(screenSize.width(), screenSize.height());
    warnLoginText->setVisible(false);
    textLogin->setVisible(false);
    textPassword->setVisible(false);
    loginLineEdit->setVisible(false);
    passwordLineEdit->setVisible(false);
    loginButton->setVisible(false);
    logoLabel->setVisible(false);
    textPresetShare->setVisible(false);
    rememberMeText->setVisible(false);
    rememberMeCheckBox->setVisible(false);
    QFont f("Montserrat", 10, QFont::Normal);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    QPalette palette1;
    palette1.setColor(QPalette::WindowText, QColor("#a395cc"));
    palette1.setColor(QPalette::ButtonText, QColor("#a395cc"));
    QPalette palette2;
    palette2.setColor(QPalette::WindowText, QColor("#35aa66"));
    QPalette palette3;
    palette3.setColor(QPalette::WindowText, QColor("#86898c"));
    QPalette palette4;
    palette4.setColor(QPalette::ButtonText, Qt::white);
    containerForPresets = new QWidget();
    containerForPresets->setMinimumSize(150,1500);
    containerForPresets->setMaximumSize(screenSize.width(), 1500);
    containerForChangePageButtons = new QWidget(this);
    containerForChangePageButtons->setMaximumSize(screenSize.width() / 4 , 100);
    containerForHeader = new QWidget(this);
    containerForHeader->setMaximumSize(screenSize.width(), 50);
    containerForHeader->setStyleSheet("background-color:#454a4f");
    containerForMy = new QWidget(this);
    containerForMy->setVisible(false);
    scrollArea = new QScrollArea();
    scrollArea->setVisible(false);
    scrollArea->setWidgetResizable(true);
    emptyWidget = new QLabel("", this);

    gridLayout = new QGridLayout(this);
    gridMyLayout = new QGridLayout(containerForMy);
    gridChangePageLayout = new QGridLayout(containerForChangePageButtons);
    gridHeaderLayout = new QGridLayout(containerForHeader);
    gridPresetsLayout = new QGridLayout(containerForPresets);

    mainButton = new QPushButton("main", this);
    gridHeaderLayout->addWidget(mainButton, 0, 0);
    mainButton->setFont(f);
    mainButton->setPalette(palette4);
    presetsButton = new QPushButton("Library", this);
    gridHeaderLayout->addWidget(presetsButton, 0, 1);
    presetsButton->setFont(f);
    presetsButton->setPalette(palette4);
    bundlesButton = new QPushButton("Bundles", this);
    gridHeaderLayout->addWidget(bundlesButton, 0, 2);
    bundlesButton->setFont(f);
    bundlesButton->setPalette(palette4);
    questButton = new QPushButton("Quests", this);
    gridHeaderLayout->addWidget(questButton, 0, 3);
    questButton->setFont(f);
    questButton->setPalette(palette4);
    trackButton = new QPushButton("Tracks", this);
    gridHeaderLayout->addWidget(trackButton, 0, 4);
    trackButton->setFont(f);
    trackButton->setPalette(palette4);
    communityButton = new QPushButton("Community", this);
    gridHeaderLayout->addWidget(communityButton, 0, 5);
    communityButton->setFont(f);
    communityButton->setPalette(palette4);
    presetsSearch = new QLineEdit(this);
    gridHeaderLayout->addWidget(presetsSearch, 0, 6);

    searchButton = new QPushButton("search", this);
    gridHeaderLayout->addWidget(searchButton, 0, 7);
    searchButton->setFont(f);
    searchButton->setPalette(palette4);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    gridHeaderLayout->addWidget(volumeSlider, 0, 8);

    myButton = new QPushButton(username, this);
    gridHeaderLayout->addWidget(myButton, 0, 9);
    myButton->setFont(f);
    myButton->setPalette(palette1);
    connect(myButton, &QPushButton::clicked, this, &Login::ToMy);
    connect(presetsButton, &QPushButton::clicked, this, &Login::ChangePresetsPage);

    logoutButton = new QPushButton("Logout", this);
    logoutButton->setMaximumSize(100, 30);
    gridMyLayout->addWidget(logoutButton, 3, 0);
    logoutButton->setFont(f);

    pathComboBox = new QComboBox(this);
    pathComboBox->setMaximumSize(180, 30);
    gridMyLayout->addWidget(pathComboBox, 0, 0);
    pathComboBox->setFont(f);

    pathPushButton = new QPushButton(this);
    gridMyLayout->addWidget(pathPushButton, 0, 1);
    pathPushButton->setFont(f);

    openExplorerCheckBox = new QCheckBox(this);
    gridMyLayout->addWidget(openExplorerCheckBox, 1, 1);
    openExplorerCheckBox->setFont(f);

    openExplorerLabel = new QLabel("Not open explorer every download?", this);
    gridMyLayout->addWidget(openExplorerLabel, 1, 0);
    openExplorerLabel->setFont(f);

    saveSettingsButton = new QPushButton("Save settings", this);
    gridMyLayout->addWidget(saveSettingsButton, 2, 0);
    saveSettingsButton->setFont(f);


    presetsPageButtonsList.resize(4);
    presetsPageButtonsList[0] = new QPushButton("<<",this);
    presetsPageButtonsList[1] = new QPushButton("<",this);
    presetsPageButtonsList[2] = new QPushButton(">",this);
    presetsPageButtonsList[3] = new QPushButton(">>",this);
    for (int i = 0; i < 4; i++) {
        presetsPageButtonsList[i]->setFont(f);
        connect(presetsPageButtonsList[i], &QPushButton::clicked, this, &Login::ChangePresetsPage);
        gridChangePageLayout->addWidget(presetsPageButtonsList[i], 0, i);
    }

    openExplorerLabel->setPalette(palette);
    textPage = new QLabel(this);
    textPage->setPalette(palette);
    textPage->setFont(f);
    gridChangePageLayout->addWidget(textPage, 0, 5);

    presetsNamesList.resize(30);
    presetsButtonsList.resize(30);
    presetsIdsList.resize(30);
    presetsIdsSynthsList.resize(30);
    presetsAuthorsList.resize(30);
    presetsSynthNamesList.resize(30);
    presetsGenreNamesList.resize(30);
    presetsTypeNamesList.resize(30);

    gridPresetsLayout->addWidget(emptyWidget, 0, 0);
    gridPresetsLayout->addWidget(containerForChangePageButtons, 10, 2);
    for (int i = 0; i < 30; i++) {
        QWidget* tempConteiner = new QWidget(this);
        QWidget* tempConteinerSynth = new QWidget(this);
        QGridLayout* tempGridLayout = new QGridLayout(tempConteiner);
        QGridLayout* tempGridLayoutSynth = new QGridLayout(tempConteinerSynth);
        tempConteiner->setStyleSheet("background-color:#454a4f");

        QLabel* signNew0 = new QLabel(">", this);
        QLabel* signNew1 = new QLabel(">", this);
        signNew0->setPalette(palette3);
        signNew1->setPalette(palette3);
        tempGridLayoutSynth->addWidget(signNew0, 0, 1);
        tempGridLayoutSynth->addWidget(signNew1, 0, 3);
        presetsNamesList[i] = new QLabel(this);
        presetsNamesList[i]->setPalette(palette);
        presetsNamesList[i]->setFont(f);
        tempGridLayout->addWidget(presetsNamesList[i], 0, 0);
        presetsSynthNamesList[i] = new QLabel(this);
        presetsSynthNamesList[i]->setFont(f);
        tempGridLayoutSynth->addWidget(presetsSynthNamesList[i], 0, 0);
        presetsSynthNamesList[i]->setPalette(palette2);
        presetsGenreNamesList[i] = new QLabel(this);
        presetsGenreNamesList[i]->setFont(f);
        tempGridLayoutSynth->addWidget(presetsGenreNamesList[i], 0, 2);
        presetsGenreNamesList[i]->setPalette(palette3);
        presetsTypeNamesList[i] = new QLabel(this);
        presetsTypeNamesList[i]->setFont(f);
        tempGridLayoutSynth->addWidget(presetsTypeNamesList[i], 0, 4);
        presetsTypeNamesList[i]->setPalette(palette3);
        presetsButtonsList[i] = new QPushButton(this);
        presetsButtonsList[i]->setFixedSize(30, 30);
        tempGridLayout->addWidget(presetsButtonsList[i], 2, 2);
        presetsButtonsList[i]->setStyleSheet("background-color:#bbbbbc");
        presetsAuthorsList[i] = new QLabel(this);
        presetsAuthorsList[i]->setFont(f);
        tempGridLayout->addWidget(presetsAuthorsList[i], 2, 0);
        presetsAuthorsList[i]->setPalette(palette1);
        tempGridLayout->addWidget(tempConteinerSynth, 1, 0);
        gridPresetsLayout->addWidget(tempConteiner, i/3, i%3 + 1);
        connect(presetsButtonsList[i], &QPushButton::clicked, this, &Login::DownloadPresetFile);
    }
    scrollArea->setWidget(containerForPresets);
    gridLayout->addWidget(containerForHeader, 1, 0);
    gridLayout->addWidget(scrollArea, 2, 0);
    gridLayout->addWidget(containerForMy, 2, 0);

    GetInstruments();
    this->setLayout(gridLayout);

    connect(saveSettingsButton, &QPushButton::clicked, this, &Login::SaveUserSettings);
    connect(logoutButton, &QPushButton::clicked, this, &Login::Logout);
}

void Login::GetInstruments() {
    manager3 = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "json");
    request.setUrl(QUrl("https://presetshare.com/app/instruments"));
    manager3->get(request);

    connect(manager3, &QNetworkAccessManager::finished, this, &Login::DownloadInstruments);
    connect(pathPushButton, &QPushButton::clicked, this, &Login::ChangePath);
    connect(pathComboBox, &QComboBox::currentTextChanged, this, &Login::ChangePathTextButton);
}

void Login::ChangePathTextButton() {
    QString currentSynth = pathComboBox->currentText();
    if(currentSynth == "Default")
        pathPushButton->setText(defaultPath);
    else
        for (int i = 0; i < jsonArrInstruments.size(); i++) {
            if(jsonArrInstruments[i].toObject()["name"].toString() == currentSynth) {
                pathPushButton->setText(pathsList[i]);
                break;
            }
        }
}

void Login::ChangePath() {
    QString currentSynth = pathComboBox->currentText();
    QString currentPath = QFileDialog::getExistingDirectory(0, tr("Set Path"), defaultPath);
    if(currentSynth == "Default")
        defaultPath = currentPath;
    else
        for (int i = 0; i < jsonArrInstruments.size(); i++) {
            if(jsonArrInstruments[i].toObject()["name"].toString() == currentSynth) {
                pathsList[i] = currentPath;
                break;
            }
        }
    ChangePathTextButton();
}

void Login::ReadUserSettings() {
    std::ifstream inputStream("paths.txt");
    if (!inputStream)
        qDebug() << "Can't open user settings file!";
    else {

        int i = 0;
        std::string line;
        getline(inputStream, line);
        if(line == "")
            defaultPath = "C:/";
        else
            defaultPath = QString::fromStdString(line);
        while (getline(inputStream, line)) {
            pathsList[i] = QString::fromStdString(line);
            i++;
        }
    }
}

void Login::SaveUserSettings() {
    std::ofstream outputStream;
    outputStream.open("paths.txt");
    if(!outputStream.is_open())
        qDebug() << "Can't write user settings file!";
    else {
        outputStream << defaultPath.toStdString() << std::endl;
        for(int i = 0; i < jsonArrInstruments.size(); i++)
            outputStream << pathsList[i].toStdString() << std::endl;
        outputStream.close();
    }
}

void Login::DownloadInstruments(QNetworkReply* reply) {
    if(reply->error()){
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        qDebug() << "Downloading instruments is completed";
        QString strReply = (QString) reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(strReply.toUtf8());
        jsonArrInstruments = jsonDoc.array();
        pathsList.resize(jsonArrInstruments.size());
        pathComboBox->addItem("Default");
        for (int i = 0; i < jsonArrInstruments.size(); i++) {
            pathComboBox->addItem(jsonArrInstruments[i].toObject()["name"].toString());
        }

        ReadUserSettings();
    }
}

void Login::ToMy() {
    scrollArea->setVisible(false);
    containerForMy->setVisible(true);
}

void Login::Logout() {
    setFixedSize(QSize(800, 600));
    delete layout();
    qDeleteAll(this->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    remove("paths.txt");
    remove("temp.txt");
    defaultPath = "C:/";
    for (int i = 0; i < jsonArrInstruments.size(); i++) {
        pathsList[i] = "";
    }
    LoginPage();
}

void Login::ChangePresetsPage() {
    int number = 1;

    if(presetsPageButtonsList[3] == sender()) {
        number = lastPage;
    } else if(presetsPageButtonsList[2] == sender()) {
        if(currentPage == lastPage) {
            number = lastPage;
        } else {
            number = currentPage + 1;
        }
    } else if(presetsPageButtonsList[1] == sender()) {
        if(currentPage != 1) {
            number = currentPage - 1;
        }
    }
    currentPage = number;
    textPage->setText(QString::fromStdString(std::to_string(currentPage)));
    qDebug() << "PAGE NUMBER: ";
    qDebug() << number;
    ToPresets(number);
}

void Login::ToPresets(int number) {

    manager1 = new QNetworkAccessManager(this);
    QJsonObject body;
    body["page"] = number;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "json");
    request.setRawHeader("Authorization", tokenByte);
    request.setUrl(QUrl("https://presetshare.com/app/list"));
    manager1->post(request, QJsonDocument(body).toJson(QJsonDocument::Compact));

    connect(manager1, &QNetworkAccessManager::finished, this, &Login::GetPresetsList);
}

void Login::GetPresetsList(QNetworkReply* reply) {
    if(reply->error()) {
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        QString strReply = (QString) reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(strReply.toUtf8());
        jsonArr = jsonDoc.array();
        qDebug() << "Downloading list is completed";
        lastPage = reply->rawHeader("X-Pagination-Page-Count").toInt();
        QJsonObject presetJson;
        containerForMy->setVisible(false);
        scrollArea->setVisible(true);
        containerForChangePageButtons->setVisible(true);
        for (int i = 0; i < jsonArr.size(); i++) {
            presetsAuthorsList[i]->setVisible(true);
            presetsNamesList[i]->setVisible(true);
            presetsSynthNamesList[i]->setVisible(true);
            presetsGenreNamesList[i]->setVisible(true);
            presetsTypeNamesList[i]->setVisible(true);
            presetsButtonsList[i]->setVisible(true);
        }
        for (int i = jsonArr.size(); i < 30; i++) {
            presetsAuthorsList[i]->setVisible(false);
            presetsNamesList[i]->setVisible(false);
            presetsSynthNamesList[i]->setVisible(false);
            presetsGenreNamesList[i]->setVisible(false);
            presetsTypeNamesList[i]->setVisible(false);
            presetsButtonsList[i]->setVisible(false);
        }
        for (int i = 0; i < jsonArr.size(); i++) {
            presetJson = jsonArr[i].toObject();
            presetsIdsList[i] = presetJson["id"].toString();
            presetsIdsSynthsList[i] = presetJson["instrument"].toObject()["id"].toString();
            presetsAuthorsList[i]->setText(presetJson["username"].toString());
            presetsNamesList[i]->setText(presetJson["name"].toString());
            presetsSynthNamesList[i]->setText(presetJson["instrument"].toObject()["name"].toString());
            presetsGenreNamesList[i]->setText(presetJson["genre"].toObject()["name"].toString());
            presetsTypeNamesList[i]->setText(presetJson["type"].toObject()["name"].toString());
        }

    }
}

void Login::DownloadPresetFile() {
    QObject* obj = sender();
    for (int i = 0; i < presetsButtonsList.size(); i++)
        if(obj == presetsButtonsList[i]) {
            currentIndex = i;
            break;
        }
    currentId = presetsIdsList[currentIndex];
    manager2 = new QNetworkAccessManager(this);
    QJsonObject body;
    body["id"] = currentId;
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "file");
    request.setRawHeader("Authorization", tokenByte);
    request.setUrl(QUrl("https://presetshare.com/app/download"));
    manager2->post(request, QJsonDocument(body).toJson(QJsonDocument::Compact));

    connect(manager2, &QNetworkAccessManager::finished, this, &Login::SavePresetFile);
}

void Login::SavePresetFile(QNetworkReply *reply) {
    if(reply->error()){
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        std::string fileNameFromReply = reply->rawHeader("Content-Disposition").toStdString();
        std::string fileName = "";
        for (int i = 0; i < fileNameFromReply.length(); i++)
            if(fileNameFromReply[i] == '\"') {
                for (int j = i + 1; j < fileNameFromReply.length() - 1; j++) {
                    fileName+=fileNameFromReply[j];
                }
                break;
            }
        QString tempPath;
        if(pathsList[currentIndex] != "")
            tempPath = pathsList[currentIndex];
        else
            tempPath = defaultPath;
        QString path;
        if(!openExplorerCheckBox->checkState())
            path = QFileDialog::getSaveFileName(0, tr("Save File"), tempPath +'\\'+ QString::fromStdString(fileName));
        else
            path = tempPath +'\\'+ QString::fromStdString(fileName);
        QFile *file = new QFile(path);
        if(file->open(QFile::WriteOnly)){
            file->write(reply->readAll());
            file->close();
            qDebug() << "Downloading file is completed";
        }
    }
}
