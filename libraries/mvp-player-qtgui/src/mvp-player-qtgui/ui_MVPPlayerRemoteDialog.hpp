/********************************************************************************
** Form generated from reading UI file 'MVPPlayerRemoteDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MVPPLAYERREMOTEDIALOG_H
#define MVPPLAYERREMOTEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
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

class Ui_MVPPlayerRemoteDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *layoutButtonsBar;
    QSpacerItem *horizontalSpacer;
    QToolButton *btnServer;
    QFrame *line_2;
    QCheckBox *cbMute;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *lblCurrentTrack;
    QLabel *label_2;
    QListWidget *playlist;

    void setupUi(QDialog *MVPPlayerRemoteDialog)
    {
        if (MVPPlayerRemoteDialog->objectName().isEmpty())
            MVPPlayerRemoteDialog->setObjectName(QStringLiteral("MVPPlayerRemoteDialog"));
        MVPPlayerRemoteDialog->resize(556, 300);
        verticalLayout_3 = new QVBoxLayout(MVPPlayerRemoteDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 0, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        layoutButtonsBar = new QHBoxLayout();
        layoutButtonsBar->setObjectName(QStringLiteral("layoutButtonsBar"));

        horizontalLayout->addLayout(layoutButtonsBar);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnServer = new QToolButton(MVPPlayerRemoteDialog);
        btnServer->setObjectName(QStringLiteral("btnServer"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/mvpplayer/toolbar/connection.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnServer->setIcon(icon);
        btnServer->setIconSize(QSize(32, 32));
        btnServer->setCheckable(true);

        horizontalLayout->addWidget(btnServer);


        verticalLayout_2->addLayout(horizontalLayout);

        line_2 = new QFrame(MVPPlayerRemoteDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        cbMute = new QCheckBox(MVPPlayerRemoteDialog);
        cbMute->setObjectName(QStringLiteral("cbMute"));
        cbMute->setChecked(true);

        verticalLayout_2->addWidget(cbMute);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(MVPPlayerRemoteDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lblCurrentTrack = new QLabel(MVPPlayerRemoteDialog);
        lblCurrentTrack->setObjectName(QStringLiteral("lblCurrentTrack"));

        horizontalLayout_2->addWidget(lblCurrentTrack);


        verticalLayout->addLayout(horizontalLayout_2);

        label_2 = new QLabel(MVPPlayerRemoteDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        playlist = new QListWidget(MVPPlayerRemoteDialog);
        playlist->setObjectName(QStringLiteral("playlist"));
        playlist->setDragDropMode(QAbstractItemView::DropOnly);

        verticalLayout->addWidget(playlist);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        QWidget::setTabOrder(btnServer, cbMute);
        QWidget::setTabOrder(cbMute, playlist);

        retranslateUi(MVPPlayerRemoteDialog);

        QMetaObject::connectSlotsByName(MVPPlayerRemoteDialog);
    } // setupUi

    void retranslateUi(QDialog *MVPPlayerRemoteDialog)
    {
        MVPPlayerRemoteDialog->setWindowTitle(QApplication::translate("MVPPlayerRemoteDialog", "MVPPlayer - Remote", 0));
        btnServer->setText(QApplication::translate("MVPPlayerRemoteDialog", "C", 0));
        cbMute->setText(QApplication::translate("MVPPlayerRemoteDialog", "Mute", 0));
        label->setText(QApplication::translate("MVPPlayerRemoteDialog", "Current track:", 0));
        lblCurrentTrack->setText(QString());
        label_2->setText(QApplication::translate("MVPPlayerRemoteDialog", "Playlist:", 0));
    } // retranslateUi

};

namespace Ui {
    class MVPPlayerRemoteDialog: public Ui_MVPPlayerRemoteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MVPPLAYERREMOTEDIALOG_H
