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
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QFrame *frameImage;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *btnOpen;
    QToolButton *btnServer;
    QToolButton *btnSettings;
    QSpacerItem *horizontalSpacer;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QToolButton *btnRecord;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *btnPrevious;
    QToolButton *btnPlayStop;
    QToolButton *btnNext;
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
        MVPPlayerDialog->resize(537, 344);
        MVPPlayerDialog->setSizeGripEnabled(true);
        MVPPlayerDialog->setModal(true);
        horizontalLayout_4 = new QHBoxLayout(MVPPlayerDialog);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 0, -1, -1);
        frameImage = new QFrame(MVPPlayerDialog);
        frameImage->setObjectName(QStringLiteral("frameImage"));
        frameImage->setFrameShape(QFrame::Panel);
        frameImage->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frameImage);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        btnOpen = new QToolButton(MVPPlayerDialog);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/mvpplayer/action/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOpen->setIcon(icon);
        btnOpen->setIconSize(QSize(32, 32));

        horizontalLayout_3->addWidget(btnOpen);

        btnServer = new QToolButton(MVPPlayerDialog);
        btnServer->setObjectName(QStringLiteral("btnServer"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/mvpplayer/toolbar/connection.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnServer->setIcon(icon1);
        btnServer->setIconSize(QSize(32, 32));
        btnServer->setCheckable(true);

        horizontalLayout_3->addWidget(btnServer);

        btnSettings = new QToolButton(MVPPlayerDialog);
        btnSettings->setObjectName(QStringLiteral("btnSettings"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/mvpplayer/toolbar/applications-settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSettings->setIcon(icon2);
        btnSettings->setIconSize(QSize(32, 32));

        horizontalLayout_3->addWidget(btnSettings);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        line = new QFrame(MVPPlayerDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnRecord = new QToolButton(MVPPlayerDialog);
        btnRecord->setObjectName(QStringLiteral("btnRecord"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/mvpplayer/action/record.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRecord->setIcon(icon3);
        btnRecord->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(btnRecord);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btnPrevious = new QToolButton(MVPPlayerDialog);
        btnPrevious->setObjectName(QStringLiteral("btnPrevious"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/mvpplayer/action/backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPrevious->setIcon(icon4);
        btnPrevious->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(btnPrevious);

        btnPlayStop = new QToolButton(MVPPlayerDialog);
        btnPlayStop->setObjectName(QStringLiteral("btnPlayStop"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/mvpplayer/action/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPlayStop->setIcon(icon5);
        btnPlayStop->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(btnPlayStop);

        btnNext = new QToolButton(MVPPlayerDialog);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/mvpplayer/action/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNext->setIcon(icon6);
        btnNext->setIconSize(QSize(32, 32));
        btnNext->setPopupMode(QToolButton::DelayedPopup);

        horizontalLayout->addWidget(btnNext);

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


        horizontalLayout_4->addLayout(verticalLayout_2);

        QWidget::setTabOrder(btnOpen, btnServer);
        QWidget::setTabOrder(btnServer, btnSettings);
        QWidget::setTabOrder(btnSettings, btnRecord);
        QWidget::setTabOrder(btnRecord, btnPrevious);
        QWidget::setTabOrder(btnPrevious, btnPlayStop);
        QWidget::setTabOrder(btnPlayStop, btnNext);
        QWidget::setTabOrder(btnNext, playlist);

        retranslateUi(MVPPlayerDialog);

        QMetaObject::connectSlotsByName(MVPPlayerDialog);
    } // setupUi

    void retranslateUi(QDialog *MVPPlayerDialog)
    {
        MVPPlayerDialog->setWindowTitle(QApplication::translate("MVPPlayerDialog", "MVP Media player", 0));
        btnOpen->setText(QApplication::translate("MVPPlayerDialog", "O", 0));
        btnServer->setText(QApplication::translate("MVPPlayerDialog", "C", 0));
        btnSettings->setText(QApplication::translate("MVPPlayerDialog", "P", 0));
#ifndef QT_NO_TOOLTIP
        btnRecord->setToolTip(QApplication::translate("MVPPlayerDialog", "Record from input device", 0));
#endif // QT_NO_TOOLTIP
        btnRecord->setText(QApplication::translate("MVPPlayerDialog", "O", 0));
        btnPrevious->setText(QApplication::translate("MVPPlayerDialog", "<<", 0));
        btnPlayStop->setText(QApplication::translate("MVPPlayerDialog", "|>", 0));
        btnNext->setText(QApplication::translate("MVPPlayerDialog", ">>", 0));
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
