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
/**
 * @brief Класс Login, наследующий функционал класса QWidget
 */
class Login : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса Login, он запускает функцию LoginPage()
     */
    explicit Login(QWidget *parent = 0);

private slots:
    /**
     * @brief Создание всех нужные элементы для интерфейса авторизации
     */
    void LoginPage();
    /**
     * @brief Отправка запроса на сервер с введёнными пользователем данными
     */
    void Authorization();
    /**
     * @brief Обработка ответа от сервера
     */
    void LoginResult(QNetworkReply* reply);
    /**
     * @brief Выход из аккаунта
     * @param reply Ответ от сервера
     */
    void Logout();
    /**
     * @brief Смена элементов интерфейса после успешного входа в аккаунт
     */
    void ChangeLayoutToApp();
    /**
     * @brief Переход на вкладку пресетов
     */
    void ToPresets(int i);
    /**
     * @brief Переход на вкладку пользователя
     */
    void ToMy();
    /**
     * @brief Отправка запроса серверу на список пресетов
     */
    void GetPresetsList(QNetworkReply* reply);
    /**
     * @brief Отправка запроса на загрузку файла пресета
     * @param reply Ответ от сервера
     */
    void DownloadPresetFile();
    /**
     * @brief Сохранение файла пресета
     */
    void SavePresetFile(QNetworkReply* reply);
    /**
     * @brief Смена страницы пресетов
     * @param reply Ответ от сервера
     */
    void ChangePresetsPage();
    /**
     * @brief Отправка запроса серверу на список синтезаторов
     */
    void GetInstruments();
    /**
     * @brief Обработка ответа от сервера
     */
    void DownloadInstruments(QNetworkReply* reply);
    /**
     * @brief Смена пути загрузки конкретного синтезатора
     * @param reply Ответ от сервера
     */
    void ChangePath();
    /**
     * @brief Отображение пользователю, что путь загрузки сменился
     */
    void ChangePathTextButton();
    /**
     * @brief Загрузка пользовательских настроек загрузки из файла
     */
    void ReadUserSettings();
    /**
     * @brief Сохранение пользовательских настрок загрузки в файл
     */
    void SaveUserSettings();

private:
    //! Размер экрана пользователя
    QRectF const screenSize = QApplication::desktop()->screenGeometry();
    //! Токен/пароль пользователя
    QByteArray tokenByte;
    //! Json с данными синтезаторов
    QJsonArray jsonArr;
    QJsonArray jsonArrInstruments;
    //! Текущий ID пресета
    QString currentId;
    //! Текущий индекс пресета
    int currentIndex;
    //! Последняя страница пресетов
    int lastPage;
    //! Текущая страница пресетов
    int currentPage;
    //! Имя пользователя
    QString username;
    //! Стандартный путь загрузки пресетов
    QString defaultPath = "C:/";
    //! Текущий путь загрузки пресетов
    QString currentPathDownload;
    //! Список путей загрузки пресетов
    QVector<QString> pathsList;

    /*! \defgroup group1 Объекты для расстановки элементов в интерфейсе
    @{ */
    QScrollArea* scrollArea;
    QGridLayout* gridLayout;
    QGridLayout* gridChangePageLayout;
    QGridLayout* gridHeaderLayout;
    QGridLayout* gridPresetsLayout;
    QGridLayout* gridMyLayout;
    /*! }@ */

    //! Контейнеры для элементов интерфейса
    QWidget *containerForPresets;
    QWidget *containerForHeader;
    QWidget *containerForChangePageButtons;
    QWidget *containerForMy;
    QLabel *emptyWidget;

    //! Объекты для запросов к серверу
    QNetworkAccessManager* managerAuthorization;
    QNetworkAccessManager* manager1;
    QNetworkAccessManager* manager2;
    QNetworkAccessManager* manager3;

    //! Элементы интерфейса авторизации
    QLabel* logoLabel;
    QLabel* textPresetShare;
    QLabel* textPage;
    QLabel* textLogin;
    QLabel* textPassword;
    QLabel* warnLoginText;
    QLabel* rememberMeText;
    QCheckBox* rememberMeCheckBox;
    QLineEdit* loginLineEdit;
    QLineEdit*  passwordLineEdit;
    QPushButton* loginButton;

    //! Элементы интерфейса вкладки пользователя
    QPushButton* logoutButton;
    QComboBox* pathComboBox;
    QPushButton* pathPushButton;
    QCheckBox* openExplorerCheckBox;
    QLabel *openExplorerLabel;
    QPushButton* saveSettingsButton;

    //! Элементы переключений между вкладками
    QPushButton* mainButton;
    QPushButton* presetsButton;
    QPushButton* bundlesButton;
    QPushButton* questButton;
    QPushButton* trackButton;
    QPushButton* communityButton;
    QPushButton* myButton;
    QSlider* volumeSlider;
    QLineEdit* presetsSearch;
    QPushButton *searchButton;

    //! Элементы интерфейса вкладки пресетов
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
