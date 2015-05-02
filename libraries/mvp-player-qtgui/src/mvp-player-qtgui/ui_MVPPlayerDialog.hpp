/********************************************************************************
** Form generated from reading UI file 'MVPPlayerDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MVPPLAYERDIALOG_H
#define MVPPLAYERDIALOG_H

#include <QtCore/QLocale>
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
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MVPPlayerDialog
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QToolButton *btnOpen;
    QToolButton *btnSettings;
    QToolButton *btnServer;
    QLabel *lblVol;
    QSlider *sliderVolume;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QFrame *frameImage;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *layoutButtonsBar;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *lblCurrentTrack;
    QHBoxLayout *horizontalLayout_3;
    QSlider *sliderPosition;
    QLabel *lblTrackLength;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *btnClearPlaylist;
    QLabel *lblPlaylist;
    QListWidget *playlist;

    void setupUi(QDialog *MVPPlayerDialog)
    {
        if (MVPPlayerDialog->objectName().isEmpty())
            MVPPlayerDialog->setObjectName(QStringLiteral("MVPPlayerDialog"));
        MVPPlayerDialog->resize(537, 373);
        QIcon icon;
        icon.addFile(QStringLiteral(":/mvpplayer/app/splashscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        MVPPlayerDialog->setWindowIcon(icon);
        MVPPlayerDialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        MVPPlayerDialog->setSizeGripEnabled(true);
        MVPPlayerDialog->setModal(true);
        horizontalLayout_5 = new QHBoxLayout(MVPPlayerDialog);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        btnOpen = new QToolButton(MVPPlayerDialog);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/mvpplayer/action/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOpen->setIcon(icon1);
        btnOpen->setIconSize(QSize(32, 32));

        verticalLayout_3->addWidget(btnOpen);

        btnSettings = new QToolButton(MVPPlayerDialog);
        btnSettings->setObjectName(QStringLiteral("btnSettings"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/mvpplayer/toolbar/applications-settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSettings->setIcon(icon2);
        btnSettings->setIconSize(QSize(32, 32));

        verticalLayout_3->addWidget(btnSettings);

        btnServer = new QToolButton(MVPPlayerDialog);
        btnServer->setObjectName(QStringLiteral("btnServer"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/mvpplayer/toolbar/connection.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnServer->setIcon(icon3);
        btnServer->setIconSize(QSize(32, 32));
        btnServer->setCheckable(true);

        verticalLayout_3->addWidget(btnServer);

        lblVol = new QLabel(MVPPlayerDialog);
        lblVol->setObjectName(QStringLiteral("lblVol"));
        lblVol->setPixmap(QPixmap(QString::fromUtf8(":/mvpplayer/app/icon.png")));
        lblVol->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lblVol);

        sliderVolume = new QSlider(MVPPlayerDialog);
        sliderVolume->setObjectName(QStringLiteral("sliderVolume"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sliderVolume->sizePolicy().hasHeightForWidth());
        sliderVolume->setSizePolicy(sizePolicy);
        sliderVolume->setMinimumSize(QSize(0, 128));
        sliderVolume->setMaximum(100);
        sliderVolume->setValue(100);
        sliderVolume->setOrientation(Qt::Vertical);

        verticalLayout_3->addWidget(sliderVolume);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frameImage = new QFrame(MVPPlayerDialog);
        frameImage->setObjectName(QStringLiteral("frameImage"));
        frameImage->setFrameShape(QFrame::Panel);
        frameImage->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frameImage);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        layoutButtonsBar = new QHBoxLayout();
        layoutButtonsBar->setObjectName(QStringLiteral("layoutButtonsBar"));

        horizontalLayout->addLayout(layoutButtonsBar);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        line_2 = new QFrame(MVPPlayerDialog);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(MVPPlayerDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        horizontalLayout_2->addWidget(label);

        lblCurrentTrack = new QLabel(MVPPlayerDialog);
        lblCurrentTrack->setObjectName(QStringLiteral("lblCurrentTrack"));

        horizontalLayout_2->addWidget(lblCurrentTrack);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        sliderPosition = new QSlider(MVPPlayerDialog);
        sliderPosition->setObjectName(QStringLiteral("sliderPosition"));
        sliderPosition->setMaximum(100);
        sliderPosition->setOrientation(Qt::Horizontal);
        sliderPosition->setInvertedAppearance(false);
        sliderPosition->setInvertedControls(false);
        sliderPosition->setTickPosition(QSlider::TicksBelow);
        sliderPosition->setTickInterval(1);

        horizontalLayout_3->addWidget(sliderPosition);

        lblTrackLength = new QLabel(MVPPlayerDialog);
        lblTrackLength->setObjectName(QStringLiteral("lblTrackLength"));

        horizontalLayout_3->addWidget(lblTrackLength);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btnClearPlaylist = new QToolButton(MVPPlayerDialog);
        btnClearPlaylist->setObjectName(QStringLiteral("btnClearPlaylist"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/mvpplayer/action/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClearPlaylist->setIcon(icon4);

        horizontalLayout_4->addWidget(btnClearPlaylist);

        lblPlaylist = new QLabel(MVPPlayerDialog);
        lblPlaylist->setObjectName(QStringLiteral("lblPlaylist"));

        horizontalLayout_4->addWidget(lblPlaylist);


        verticalLayout->addLayout(horizontalLayout_4);

        playlist = new QListWidget(MVPPlayerDialog);
        playlist->setObjectName(QStringLiteral("playlist"));
        playlist->setAcceptDrops(true);
        playlist->setDragDropMode(QAbstractItemView::DropOnly);

        verticalLayout->addWidget(playlist);


        horizontalLayout_5->addLayout(verticalLayout);

        QWidget::setTabOrder(btnOpen, btnSettings);
        QWidget::setTabOrder(btnSettings, btnServer);
        QWidget::setTabOrder(btnServer, sliderVolume);
        QWidget::setTabOrder(sliderVolume, sliderPosition);
        QWidget::setTabOrder(sliderPosition, playlist);

        retranslateUi(MVPPlayerDialog);

        QMetaObject::connectSlotsByName(MVPPlayerDialog);
    } // setupUi

    void retranslateUi(QDialog *MVPPlayerDialog)
    {
        MVPPlayerDialog->setWindowTitle(QApplication::translate("MVPPlayerDialog", "MVP Media player", 0));
        btnOpen->setText(QApplication::translate("MVPPlayerDialog", "O", 0));
        btnSettings->setText(QApplication::translate("MVPPlayerDialog", "P", 0));
        btnServer->setText(QApplication::translate("MVPPlayerDialog", "C", 0));
        lblVol->setText(QString());
        label->setText(QApplication::translate("MVPPlayerDialog", "Current track:", 0));
        lblCurrentTrack->setText(QString());
        lblTrackLength->setText(QString());
        btnClearPlaylist->setText(QApplication::translate("MVPPlayerDialog", "x", 0));
        lblPlaylist->setText(QApplication::translate("MVPPlayerDialog", "Playlist:", 0));
#ifndef QT_NO_WHATSTHIS
        playlist->setWhatsThis(QApplication::translate("MVPPlayerDialog", "Playlist", 0));
#endif // QT_NO_WHATSTHIS
    } // retranslateUi

};

namespace Ui {
    class MVPPlayerDialog: public Ui_MVPPlayerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MVPPLAYERDIALOG_H
