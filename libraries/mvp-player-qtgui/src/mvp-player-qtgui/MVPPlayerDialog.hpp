#ifndef _MVPPLAYERDIALOG_HPP
#define	_MVPPLAYERDIALOG_HPP

#include "ui_MVPPlayerDialog.hpp"

namespace mvpplayer
{
namespace gui
{
namespace qt
{

/**
 * 
 */
class MVPPlayerDialog : public QDialog
{
    Q_OBJECT
public:
    MVPPlayerDialog( QWidget *parent = NULL );
    virtual ~MVPPlayerDialog();
private:
    Ui::MVPPlayerDialog widget;
};

}
}
}

#endif
