#include "IpInfoWidget.h"
#include "ui_IpInfoWidget.h"

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include <QHostAddress>

IpInfoWidget::IpInfoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IpInfoWidget)
    , m_networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    // Настройка SQLite
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("requests.db");
    if (!m_database.open()) {
        ui->textResult->append("Ошибка открытия БД: " + m_database.lastError().text());
    } else {
        QSqlQuery q;
        q.exec(R"(
            CREATE TABLE IF NOT EXISTS logs (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                timestamp TEXT,
                ip TEXT,
                status TEXT
            )
        )");
    }

    // Сигналы и слоты
    connect(ui->buttonSearch, &QPushButton::clicked,
            this, &IpInfoWidget::handleSearchButton);
    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &IpInfoWidget::handleApiResponse);

    // Первичный запрос текущего IP
    requestCurrentIp();
}

IpInfoWidget::~IpInfoWidget()
{
    delete ui;
}

void IpInfoWidget::requestCurrentIp()
{
    QUrl url("http://ip-api.com/json/");
    m_networkManager->get(QNetworkRequest(url));
}



void IpInfoWidget::handleSearchButton()
{
    const QString ipText = ui->lineEditSearch->text().trimmed();

    // Проверим через QHostAddress
    QHostAddress addr;
    if (!addr.setAddress(ipText)) {
        ui->textResult->append("Некорректный IP-адрес: " + ipText);
        logToDatabase(ipText, "invalid");
        return;
    }

    // Всё ок, формируем URL и шлём запрос
    QUrl url(QString("http://ip-api.com/json/%1").arg(ipText));
    m_networkManager->get(QNetworkRequest(url));
}


void IpInfoWidget::handleApiResponse(QNetworkReply *reply)
{
    // Разбор URL-пути: "/json" → текущий, "/json/1.2.3.4" → конкретный
    const QString path = reply->request().url().path();
    const QStringList parts = path.split('/', Qt::SkipEmptyParts);
    const bool isCurrent = (parts.size() == 1 && parts[0] == "json");
    const QString ip = isCurrent ? QString("current") : parts.value(1);

    const QByteArray payload = reply->readAll();
    if (reply->error() != QNetworkReply::NoError) {
        ui->textResult->append("Сетевая ошибка: " + reply->errorString());
        logToDatabase(ip, "error");
    } else {
        const QJsonDocument doc = QJsonDocument::fromJson(payload);
        if (!doc.isObject()) {
            ui->textResult->append("Ошибка формата ответа");
            logToDatabase(ip, "error");
        } else {
            const QJsonObject obj = doc.object();
            const QString queryIp = obj.value("query").toString();
            const QString country = obj.value("country").toString();
            const QString city = obj.value("city").toString();
            const QString timezone = obj.value("timezone").toString();
            const QString isp = obj.value("isp").toString();

            if (isCurrent) {
                ui->lineEditCurrent->setText(queryIp);
                ui->textResult->append("Текущий IP: " + queryIp);
                logToDatabase("current", "success");
            } else {
                const QString result = QStringLiteral(
                                           "IP: %1\nСтрана: %2\nГород: %3\nЧасовой пояс: %4\nISP: %5\n"
                                           ).arg(queryIp, country, city, timezone, isp);
                ui->textResult->append(result);
                logToDatabase(ip, "success");
            }
        }
    }
    reply->deleteLater();
}

void IpInfoWidget::logToDatabase(const QString &ip, const QString &status)
{
    QSqlQuery q;
    q.prepare("INSERT INTO logs (timestamp, ip, status) VALUES (?, ?, ?)");
    q.addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));
    q.addBindValue(ip);
    q.addBindValue(status);
    if (!q.exec()) {
        ui->textResult->append("Ошибка логирования: " + q.lastError().text());
    }
}


//Боже, какая же это фигняяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяяя
