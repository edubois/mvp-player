#ifndef __MVPPLAYER_MVPPLAYERSETTINGSDIALOG_H_
#define	__MVPPLAYER_MVPPLAYERSETTINGSDIALOG_H_

#include "ui_MVPPlayerSettingsDialog.hpp"

namespace mvpplayer
{
namespace gui
{
namespace qt
{

class MVPPlayerSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    MVPPlayerSettingsDialog( QDialog *parent = NULL );
    virtual ~MVPPlayerSettingsDialog();

private:
    Ui::MVPPlayerSettingsDialog widget;
};

}
}
}

#endif
