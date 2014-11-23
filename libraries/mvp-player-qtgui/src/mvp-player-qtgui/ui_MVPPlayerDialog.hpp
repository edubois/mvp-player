/********************************************************************************
** Form generated from reading UI file 'MVPPlayerDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MVPPLAYERDIALOG_H
#define MVPPLAYERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MVPPlayerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *btnOpen;
    QLabel *label;
    QLabel *lblCurrentTrack;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnPrevious;
    QPushButton *btnPlay;
    QPushButton *btnNext;

    void setupUi(QDialog *MVPPlayerDialog)
    {
        if (MVPPlayerDialog->objectName().isEmpty())
            MVPPlayerDialog->setObjectName(QStringLiteral("MVPPlayerDialog"));
        MVPPlayerDialog->resize(517, 100);
        MVPPlayerDialog->setModal(true);
        verticalLayout = new QVBoxLayout(MVPPlayerDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnOpen = new QToolButton(MVPPlayerDialog);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        btnOpen->setMinimumSize(QSize(32, 32));
        btnOpen->setBaseSize(QSize(32, 32));

        horizontalLayout_2->addWidget(btnOpen);

        label = new QLabel(MVPPlayerDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lblCurrentTrack = new QLabel(MVPPlayerDialog);
        lblCurrentTrack->setObjectName(QStringLiteral("lblCurrentTrack"));

        horizontalLayout_2->addWidget(lblCurrentTrack);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnPrevious = new QPushButton(MVPPlayerDialog);
        btnPrevious->setObjectName(QStringLiteral("btnPrevious"));
        btnPrevious->setMinimumSize(QSize(32, 32));

        horizontalLayout->addWidget(btnPrevious);

        btnPlay = new QPushButton(MVPPlayerDialog);
        btnPlay->setObjectName(QStringLiteral("btnPlay"));

        horizontalLayout->addWidget(btnPlay);

        btnNext = new QPushButton(MVPPlayerDialog);
        btnNext->setObjectName(QStringLiteral("btnNext"));

        horizontalLayout->addWidget(btnNext);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MVPPlayerDialog);

        QMetaObject::connectSlotsByName(MVPPlayerDialog);
    } // setupUi

    void retranslateUi(QDialog *MVPPlayerDialog)
    {
        MVPPlayerDialog->setWindowTitle(QApplication::translate("MVPPlayerDialog", "MVPPlayer", 0));
        btnOpen->setText(QApplication::translate("MVPPlayerDialog", "...", 0));
        label->setText(QApplication::translate("MVPPlayerDialog", "Current track:", 0));
        lblCurrentTrack->setText(QString());
        btnPrevious->setText(QApplication::translate("MVPPlayerDialog", "<<", 0));
        btnPlay->setText(QApplication::translate("MVPPlayerDialog", "|>", 0));
        btnNext->setText(QApplication::translate("MVPPlayerDialog", ">>", 0));
    } // retranslateUi

};

namespace Ui {
    class MVPPlayerDialog: public Ui_MVPPlayerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MVPPLAYERDIALOG_H
