/********************************************************************************
** Form generated from reading UI file 'MVPPlayerSettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MVPPLAYERSETTINGSDIALOG_H
#define MVPPLAYERSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MVPPlayerSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *lblDefaultInput;
    QComboBox *comboDefaultInput;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *MVPPlayerSettingsDialog)
    {
        if (MVPPlayerSettingsDialog->objectName().isEmpty())
            MVPPlayerSettingsDialog->setObjectName(QStringLiteral("MVPPlayerSettingsDialog"));
        MVPPlayerSettingsDialog->resize(355, 126);
        QIcon icon;
        icon.addFile(QStringLiteral(":/mvpplayer/toolbar/applications-settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        MVPPlayerSettingsDialog->setWindowIcon(icon);
        MVPPlayerSettingsDialog->setModal(true);
        verticalLayout = new QVBoxLayout(MVPPlayerSettingsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        lblDefaultInput = new QLabel(MVPPlayerSettingsDialog);
        lblDefaultInput->setObjectName(QStringLiteral("lblDefaultInput"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblDefaultInput);

        comboDefaultInput = new QComboBox(MVPPlayerSettingsDialog);
        comboDefaultInput->setObjectName(QStringLiteral("comboDefaultInput"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboDefaultInput);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(-1, 12, -1, -1);
        pushButton = new QPushButton(MVPPlayerSettingsDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setDefault(true);
        pushButton->setFlat(false);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(MVPPlayerSettingsDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MVPPlayerSettingsDialog);

        QMetaObject::connectSlotsByName(MVPPlayerSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *MVPPlayerSettingsDialog)
    {
        MVPPlayerSettingsDialog->setWindowTitle(QApplication::translate("MVPPlayerSettingsDialog", "MVP Player - Settings", 0));
        lblDefaultInput->setText(QApplication::translate("MVPPlayerSettingsDialog", "Default input", 0));
        pushButton->setText(QApplication::translate("MVPPlayerSettingsDialog", "&Ok", 0));
        pushButton_2->setText(QApplication::translate("MVPPlayerSettingsDialog", "&Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class MVPPlayerSettingsDialog: public Ui_MVPPlayerSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MVPPLAYERSETTINGSDIALOG_H
