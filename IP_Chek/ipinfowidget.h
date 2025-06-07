#pragma once

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtSql/QSqlDatabase>

namespace Ui {
class IpInfoWidget;
}

/**
 * @brief Виджет для получения и отображения информации об IP-адресах.
 */
class IpInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IpInfoWidget(QWidget *parent = nullptr);
    ~IpInfoWidget() override;

private slots:
    // Обработчик нажатия кнопки «Поиск»
    void handleSearchButton();

    // Обработчик любого ответа от API
    void handleApiResponse(QNetworkReply *reply);

private:
    Ui::IpInfoWidget *ui;
    QNetworkAccessManager *m_networkManager;
    QSqlDatabase m_database;

    /// Запрос текущего внешнего IP
    void requestCurrentIp();

    /**
     * @brief Логирование в локальную БД
     * @param ip — IP или "current"
     * @param status — "success", "error" или "invalid"
     */
    void logToDatabase(const QString &ip, const QString &status);
};
