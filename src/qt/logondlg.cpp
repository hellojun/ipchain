#include "logondlg.h"
#include "ui_logondlg.h"
#include "logon.h"
#include "setrecovery.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include "log/log.h"
logondlg::logondlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logondlg)
{
     ui->setupUi(this);
     setWindowTitle(tr("IPC"));
     m_plogon = new logon(this);
     connect(m_plogon,SIGNAL(createwallet()),this,SLOT(createwallet()));
     connect(m_plogon,SIGNAL(gotoRestorePage()),this,SLOT(gotoRestorePage()));
     ui->stackedWidget->addWidget(m_plogon);
     m_pSetRecovery = new SetRecovery(this);
     ui->stackedWidget->addWidget(m_pSetRecovery);
     connect(m_pSetRecovery,SIGNAL(next()),this,SLOT(createwallet()));
     connect(m_pSetRecovery,SIGNAL(back()),this,SLOT(backcreatewallet()));
     ui->stackedWidget->setCurrentWidget(m_plogon);
     setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
     setWindowIcon(QIcon(":icons/bitcoin"));
}

logondlg::~logondlg()
{
    delete ui;
}
void logondlg::setDlgParams()
{
    resize(1000,660);
    QDesktopWidget* desktop = QApplication::desktop();
    QRect screenRect = desktop->screenGeometry();
    move((screenRect.width() - this->width())/2, (screenRect.height() - this->height())/2);
}

void logondlg::createwallet()
{

    this->accept();
}
void logondlg::slotFinish(QWidget*)
{
    m_plogon->stopLoadingTimer();
    hide();
}
void logondlg::showwindowwithwait()
{
    backcreatewallet();
    m_plogon->showwaitpic();
    show();
}
void logondlg::backcreatewallet()
{
    ui->stackedWidget->setCurrentWidget(m_plogon);
}
void logondlg::gotoRestorePage()
{
    m_pSetRecovery->setDestSourcePath(m_plogon->getdatapath());
    ui->stackedWidget->setCurrentWidget(m_pSetRecovery);
}
void logondlg::setdatapath(QString path)
{
    m_plogon->setdatapath(path);
}

QString logondlg::getdatapath()
{
    return m_plogon->getdatapath();
}
