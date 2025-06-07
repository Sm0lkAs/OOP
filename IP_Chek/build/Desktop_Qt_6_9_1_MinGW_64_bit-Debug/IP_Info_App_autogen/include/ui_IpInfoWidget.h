/********************************************************************************
** Form generated from reading UI file 'ipinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPINFOWIDGET_H
#define UI_IPINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IpInfoWidget
{
public:
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QLabel *labelCurrent;
    QLineEdit *lineEditCurrent;
    QLabel *labelSearch;
    QLineEdit *lineEditSearch;
    QPushButton *buttonSearch;
    QTextEdit *textResult;

    void setupUi(QWidget *IpInfoWidget)
    {
        if (IpInfoWidget->objectName().isEmpty())
            IpInfoWidget->setObjectName("IpInfoWidget");
        mainLayout = new QVBoxLayout(IpInfoWidget);
        mainLayout->setObjectName("mainLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelCurrent = new QLabel(IpInfoWidget);
        labelCurrent->setObjectName("labelCurrent");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelCurrent);

        lineEditCurrent = new QLineEdit(IpInfoWidget);
        lineEditCurrent->setObjectName("lineEditCurrent");
        lineEditCurrent->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditCurrent);

        labelSearch = new QLabel(IpInfoWidget);
        labelSearch->setObjectName("labelSearch");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelSearch);

        lineEditSearch = new QLineEdit(IpInfoWidget);
        lineEditSearch->setObjectName("lineEditSearch");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditSearch);


        mainLayout->addLayout(formLayout);

        buttonSearch = new QPushButton(IpInfoWidget);
        buttonSearch->setObjectName("buttonSearch");

        mainLayout->addWidget(buttonSearch);

        textResult = new QTextEdit(IpInfoWidget);
        textResult->setObjectName("textResult");
        textResult->setReadOnly(true);

        mainLayout->addWidget(textResult);


        retranslateUi(IpInfoWidget);

        QMetaObject::connectSlotsByName(IpInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *IpInfoWidget)
    {
        IpInfoWidget->setWindowTitle(QCoreApplication::translate("IpInfoWidget", "IP Info App", nullptr));
        labelCurrent->setText(QCoreApplication::translate("IpInfoWidget", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 IP:", nullptr));
        labelSearch->setText(QCoreApplication::translate("IpInfoWidget", "IP \320\264\320\273\321\217 \320\277\320\276\320\270\321\201\320\272\320\260:", nullptr));
        buttonSearch->setText(QCoreApplication::translate("IpInfoWidget", "\320\237\320\276\320\270\321\201\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IpInfoWidget: public Ui_IpInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPINFOWIDGET_H
