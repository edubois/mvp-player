/********************************************************************************
** Form generated from reading UI file 'MVPPlayerDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MVPPlayerDialog
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QToolButton *btnOpen;
    QToolButton *btnSettings;
    QToolButton *btnServer;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QFrame *frameImage;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *layoutButtonsBar;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *lblCurrentTrack;
    QLabel *label_2;
    QListWidget *playlist;

    void setupUi(QDialog *MVPPlayerDialog)
    {
        if (MVPPlayerDialog->objectName().isEmpty())
            MVPPlayerDialog->setObjectName(QStringLiteral("MVPPlayerDialog"));
        MVPPlayerDialog->resize(565, 344);
        MVPPlayerDialog->setSizeGripEnabled(true);
        MVPPlayerDialog->setModal(true);
        horizontalLayout_3 = new QHBoxLayout(MVPPlayerDialog);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        btnOpen = new QToolButton(MVPPlayerDialog);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/mvpplayer/action/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOpen->setIcon(icon);
        btnOpen->setIconSize(QSize(32, 32));

        verticalLayout_3->addWidget(btnOpen);

        btnSettings = new QToolButton(MVPPlayerDialog);
        btnSettings->setObjectName(QStringLiteral("btnSettings"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/mvpplayer/toolbar/applications-settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSettings->setIcon(icon1);
        btnSettings->setIconSize(QSize(32, 32));

        verticalLayout_3->addWidget(btnSettings);

        btnServer = new QToolButton(MVPPlayerDialog);
        btnServer->setObjectName(QStringLiteral("btnServer"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/mvpplayer/toolbar/connection.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnServer->setIcon(icon2);
        btnServer->setIconSize(QSize(32, 32));
        btnServer->setCheckable(true);

        verticalLayout_3->addWidget(btnServer);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 0, -1, -1);
        frameImage = new QFrame(MVPPlayerDialog);
        frameImage->setObjectName(QStringLiteral("frameImage"));
        frameImage->setFrameShape(QFrame::Panel);
        frameImage->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frameImage);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        layoutButtonsBar = new QHBoxLayout();
        layoutButtonsBar->setObjectName(QStringLiteral("layoutButtonsBar"));

        horizontalLayout->addLayout(layoutButtonsBar);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout);

        line_2 = new QFrame(MVPPlayerDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(MVPPlayerDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lblCurrentTrack = new QLabel(MVPPlayerDialog);
        lblCurrentTrack->setObjectName(QStringLiteral("lblCurrentTrack"));

        horizontalLayout_2->addWidget(lblCurrentTrack);


        verticalLayout->addLayout(horizontalLayout_2);

        label_2 = new QLabel(MVPPlayerDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        playlist = new QListWidget(MVPPlayerDialog);
        playlist->setObjectName(QStringLiteral("playlist"));
        playlist->setDragDropMode(QAbstractItemView::DropOnly);

        verticalLayout->addWidget(playlist);


        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout_3->addLayout(verticalLayout_2);

        QWidget::setTabOrder(btnOpen, btnSettings);
        QWidget::setTabOrder(btnSettings, btnServer);
        QWidget::setTabOrder(btnServer, playlist);

        retranslateUi(MVPPlayerDialog);

        QMetaObject::connectSlotsByName(MVPPlayerDialog);
    } // setupUi

    void retranslateUi(QDialog *MVPPlayerDialog)
    {
        MVPPlayerDialog->setWindowTitle(QApplication::translate("MVPPlayerDialog", "MVP Media player", 0));
        btnOpen->setText(QApplication::translate("MVPPlayerDialog", "O", 0));
        btnSettings->setText(QApplication::translate("MVPPlayerDialog", "P", 0));
        btnServer->setText(QApplication::translate("MVPPlayerDialog", "C", 0));
        label->setText(QApplication::translate("MVPPlayerDialog", "Current track:", 0));
        lblCurrentTrack->setText(QString());
        label_2->setText(QApplication::translate("MVPPlayerDialog", "Playlist:", 0));
    } // retranslateUi

};

namespace Ui {
    class MVPPlayerDialog: public Ui_MVPPlayerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MVPPLAYERDIALOG_H
