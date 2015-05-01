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
#include <QtWidgets/QSlider>
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
    QHBoxLayout *horizontalLayout_4;
    QSlider *sliderVolume;
    QLabel *lblVol;
    QToolButton *btnServer;
    QFrame *line_2;
    QCheckBox *cbMute;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *lblCurrentTrack;
    QLabel *lblTrackLength;
    QHBoxLayout *horizontalLayout_3;
    QSlider *sliderPosition;
    QLabel *label_2;
    QListWidget *playlist;

    void setupUi(QDialog *MVPPlayerRemoteDialog)
    {
        if (MVPPlayerRemoteDialog->objectName().isEmpty())
            MVPPlayerRemoteDialog->setObjectName(QStringLiteral("MVPPlayerRemoteDialog"));
        MVPPlayerRemoteDialog->resize(510, 356);
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

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        sliderVolume = new QSlider(MVPPlayerRemoteDialog);
        sliderVolume->setObjectName(QStringLiteral("sliderVolume"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sliderVolume->sizePolicy().hasHeightForWidth());
        sliderVolume->setSizePolicy(sizePolicy);
        sliderVolume->setMinimumSize(QSize(128, 0));
        sliderVolume->setMaximum(100);
        sliderVolume->setValue(100);
        sliderVolume->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(sliderVolume);

        lblVol = new QLabel(MVPPlayerRemoteDialog);
        lblVol->setObjectName(QStringLiteral("lblVol"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblVol->sizePolicy().hasHeightForWidth());
        lblVol->setSizePolicy(sizePolicy1);
        lblVol->setPixmap(QPixmap(QString::fromUtf8(":/mvpplayer/app/icon.png")));
        lblVol->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(lblVol);


        horizontalLayout->addLayout(horizontalLayout_4);

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
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblCurrentTrack->sizePolicy().hasHeightForWidth());
        lblCurrentTrack->setSizePolicy(sizePolicy2);
        lblCurrentTrack->setWordWrap(true);

        horizontalLayout_2->addWidget(lblCurrentTrack);

        lblTrackLength = new QLabel(MVPPlayerRemoteDialog);
        lblTrackLength->setObjectName(QStringLiteral("lblTrackLength"));
        lblTrackLength->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lblTrackLength);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        sliderPosition = new QSlider(MVPPlayerRemoteDialog);
        sliderPosition->setObjectName(QStringLiteral("sliderPosition"));
        sliderPosition->setMaximum(100);
        sliderPosition->setOrientation(Qt::Horizontal);
        sliderPosition->setInvertedAppearance(false);
        sliderPosition->setInvertedControls(false);
        sliderPosition->setTickPosition(QSlider::TicksBelow);
        sliderPosition->setTickInterval(1);

        horizontalLayout_3->addWidget(sliderPosition);


        verticalLayout->addLayout(horizontalLayout_3);

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
        QWidget::setTabOrder(cbMute, sliderPosition);
        QWidget::setTabOrder(sliderPosition, playlist);

        retranslateUi(MVPPlayerRemoteDialog);

        QMetaObject::connectSlotsByName(MVPPlayerRemoteDialog);
    } // setupUi

    void retranslateUi(QDialog *MVPPlayerRemoteDialog)
    {
        MVPPlayerRemoteDialog->setWindowTitle(QApplication::translate("MVPPlayerRemoteDialog", "MVPPlayer - Remote", 0));
        lblVol->setText(QString());
        btnServer->setText(QApplication::translate("MVPPlayerRemoteDialog", "C", 0));
        cbMute->setText(QApplication::translate("MVPPlayerRemoteDialog", "Mute", 0));
        label->setText(QApplication::translate("MVPPlayerRemoteDialog", "Current track:", 0));
        lblCurrentTrack->setText(QString());
        lblTrackLength->setText(QString());
        label_2->setText(QApplication::translate("MVPPlayerRemoteDialog", "Playlist:", 0));
    } // retranslateUi

};

namespace Ui {
    class MVPPlayerRemoteDialog: public Ui_MVPPlayerRemoteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MVPPLAYERREMOTEDIALOG_H
