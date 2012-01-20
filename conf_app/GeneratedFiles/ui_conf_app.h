/********************************************************************************
** Form generated from reading UI file 'conf_app.ui'
**
** Created: Thu 19. Jan 17:30:03 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONF_APP_H
#define UI_CONF_APP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_conf_appClass
{
public:
    QAction *actionExit;
    QAction *actionShow_startup_message;
    QAction *actionCreate_backup;
    QAction *actionRestore_backup;
    QAction *actionShow_SQL_message;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QToolBox *toolBox;
    QWidget *page_3;
    QGridLayout *gridLayout;
    QLabel *lbHost;
    QLineEdit *lineHost;
    QLabel *lbDataSource;
    QLineEdit *lineDatabase;
    QLabel *lbUsername;
    QLineEdit *lineUsername;
    QLabel *lbPassword;
    QLineEdit *linePassword;
    QLabel *lbDriver;
    QComboBox *cmbDriver;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushConnect;
    QPushButton *pushDisconnect;
    QWidget *page_4;
    QGridLayout *gridLayout_2;
    QGroupBox *groupSettings;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *cmbCountry;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *cmbCity;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushApply;
    QWidget *page;
    QGridLayout *gridLayout_4;
    QGroupBox *groupTables;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QComboBox *cmbTables;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushInsert;
    QPushButton *pushRemove;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushApply_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuOptions;
    QMenu *menuBackups;
    QToolBar *toolbar;
    QStatusBar *m_statusBar;

    void setupUi(QMainWindow *conf_appClass)
    {
        if (conf_appClass->objectName().isEmpty())
            conf_appClass->setObjectName(QString::fromUtf8("conf_appClass"));
        conf_appClass->resize(514, 400);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/conf_app/conf_app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        conf_appClass->setWindowIcon(icon);
        actionExit = new QAction(conf_appClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/conf_app/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionShow_startup_message = new QAction(conf_appClass);
        actionShow_startup_message->setObjectName(QString::fromUtf8("actionShow_startup_message"));
        actionShow_startup_message->setCheckable(true);
        actionShow_startup_message->setChecked(false);
        actionCreate_backup = new QAction(conf_appClass);
        actionCreate_backup->setObjectName(QString::fromUtf8("actionCreate_backup"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/conf_app/folder_outbox.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_backup->setIcon(icon2);
        actionRestore_backup = new QAction(conf_appClass);
        actionRestore_backup->setObjectName(QString::fromUtf8("actionRestore_backup"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/conf_app/folder_inbox.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRestore_backup->setIcon(icon3);
        actionShow_SQL_message = new QAction(conf_appClass);
        actionShow_SQL_message->setObjectName(QString::fromUtf8("actionShow_SQL_message"));
        actionShow_SQL_message->setCheckable(true);
        actionShow_SQL_message->setChecked(true);
        centralWidget = new QWidget(conf_appClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        toolBox = new QToolBox(centralWidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        page_3->setGeometry(QRect(0, 0, 496, 251));
        gridLayout = new QGridLayout(page_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lbHost = new QLabel(page_3);
        lbHost->setObjectName(QString::fromUtf8("lbHost"));
        lbHost->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbHost, 0, 0, 1, 1);

        lineHost = new QLineEdit(page_3);
        lineHost->setObjectName(QString::fromUtf8("lineHost"));

        gridLayout->addWidget(lineHost, 0, 1, 1, 1);

        lbDataSource = new QLabel(page_3);
        lbDataSource->setObjectName(QString::fromUtf8("lbDataSource"));
        lbDataSource->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbDataSource, 1, 0, 1, 1);

        lineDatabase = new QLineEdit(page_3);
        lineDatabase->setObjectName(QString::fromUtf8("lineDatabase"));

        gridLayout->addWidget(lineDatabase, 1, 1, 1, 1);

        lbUsername = new QLabel(page_3);
        lbUsername->setObjectName(QString::fromUtf8("lbUsername"));
        lbUsername->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lbUsername, 2, 0, 1, 1);

        lineUsername = new QLineEdit(page_3);
        lineUsername->setObjectName(QString::fromUtf8("lineUsername"));

        gridLayout->addWidget(lineUsername, 2, 1, 1, 1);

        lbPassword = new QLabel(page_3);
        lbPassword->setObjectName(QString::fromUtf8("lbPassword"));

        gridLayout->addWidget(lbPassword, 3, 0, 1, 1);

        linePassword = new QLineEdit(page_3);
        linePassword->setObjectName(QString::fromUtf8("linePassword"));
        linePassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(linePassword, 3, 1, 1, 1);

        lbDriver = new QLabel(page_3);
        lbDriver->setObjectName(QString::fromUtf8("lbDriver"));

        gridLayout->addWidget(lbDriver, 4, 0, 1, 1);

        cmbDriver = new QComboBox(page_3);
        cmbDriver->setObjectName(QString::fromUtf8("cmbDriver"));

        gridLayout->addWidget(cmbDriver, 4, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushConnect = new QPushButton(page_3);
        pushConnect->setObjectName(QString::fromUtf8("pushConnect"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/conf_app/encrypted.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushConnect->setIcon(icon4);

        horizontalLayout->addWidget(pushConnect);

        pushDisconnect = new QPushButton(page_3);
        pushDisconnect->setObjectName(QString::fromUtf8("pushDisconnect"));
        pushDisconnect->setEnabled(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/conf_app/decrypted.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushDisconnect->setIcon(icon5);

        horizontalLayout->addWidget(pushDisconnect);


        gridLayout->addLayout(horizontalLayout, 5, 1, 1, 1);

        toolBox->addItem(page_3, QString::fromUtf8("Connection Properties"));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 161, 121));
        gridLayout_2 = new QGridLayout(page_4);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupSettings = new QGroupBox(page_4);
        groupSettings->setObjectName(QString::fromUtf8("groupSettings"));
        verticalLayout = new QVBoxLayout(groupSettings);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        cmbCountry = new QComboBox(groupSettings);
        cmbCountry->setObjectName(QString::fromUtf8("cmbCountry"));

        horizontalLayout_2->addWidget(cmbCountry);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupSettings);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        cmbCity = new QComboBox(groupSettings);
        cmbCity->setObjectName(QString::fromUtf8("cmbCity"));

        horizontalLayout_3->addWidget(cmbCity);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushApply = new QPushButton(groupSettings);
        pushApply->setObjectName(QString::fromUtf8("pushApply"));

        horizontalLayout_4->addWidget(pushApply);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout_2->addWidget(groupSettings, 0, 0, 1, 1);

        toolBox->addItem(page_4, QString::fromUtf8("Global Settings"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 190, 162));
        gridLayout_4 = new QGridLayout(page);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupTables = new QGroupBox(page);
        groupTables->setObjectName(QString::fromUtf8("groupTables"));
        verticalLayout_3 = new QVBoxLayout(groupTables);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupTables);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        cmbTables = new QComboBox(groupTables);
        cmbTables->setObjectName(QString::fromUtf8("cmbTables"));
        cmbTables->setEditable(true);

        horizontalLayout_5->addWidget(cmbTables);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushInsert = new QPushButton(groupTables);
        pushInsert->setObjectName(QString::fromUtf8("pushInsert"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/conf_app/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushInsert->setIcon(icon6);

        verticalLayout_2->addWidget(pushInsert);

        pushRemove = new QPushButton(groupTables);
        pushRemove->setObjectName(QString::fromUtf8("pushRemove"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/conf_app/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushRemove->setIcon(icon7);

        verticalLayout_2->addWidget(pushRemove);


        horizontalLayout_6->addLayout(verticalLayout_2);

        tableView = new QTableView(groupTables);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout_6->addWidget(tableView);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        pushApply_2 = new QPushButton(groupTables);
        pushApply_2->setObjectName(QString::fromUtf8("pushApply_2"));

        horizontalLayout_7->addWidget(pushApply_2);


        verticalLayout_3->addLayout(horizontalLayout_7);


        gridLayout_4->addWidget(groupTables, 0, 0, 1, 1);

        toolBox->addItem(page, QString::fromUtf8("Edit Tables"));

        gridLayout_3->addWidget(toolBox, 0, 0, 1, 1);

        conf_appClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(conf_appClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 514, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuOptions = new QMenu(menuTools);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuBackups = new QMenu(menuTools);
        menuBackups->setObjectName(QString::fromUtf8("menuBackups"));
        conf_appClass->setMenuBar(menuBar);
        toolbar = new QToolBar(conf_appClass);
        toolbar->setObjectName(QString::fromUtf8("toolbar"));
        conf_appClass->addToolBar(Qt::TopToolBarArea, toolbar);
        m_statusBar = new QStatusBar(conf_appClass);
        m_statusBar->setObjectName(QString::fromUtf8("m_statusBar"));
        m_statusBar->setMinimumSize(QSize(0, 18));
        conf_appClass->setStatusBar(m_statusBar);
#ifndef QT_NO_SHORTCUT
        lbHost->setBuddy(lineHost);
        lbDataSource->setBuddy(lineDatabase);
        lbUsername->setBuddy(lineUsername);
        lbPassword->setBuddy(linePassword);
        lbDriver->setBuddy(cmbDriver);
        label_2->setBuddy(cmbCountry);
        label->setBuddy(cmbCity);
        label_3->setBuddy(cmbTables);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineHost, lineDatabase);
        QWidget::setTabOrder(lineDatabase, lineUsername);
        QWidget::setTabOrder(lineUsername, linePassword);
        QWidget::setTabOrder(linePassword, cmbDriver);
        QWidget::setTabOrder(cmbDriver, pushConnect);
        QWidget::setTabOrder(pushConnect, pushDisconnect);
        QWidget::setTabOrder(pushDisconnect, cmbCountry);
        QWidget::setTabOrder(cmbCountry, cmbCity);
        QWidget::setTabOrder(cmbCity, pushApply);
        QWidget::setTabOrder(pushApply, cmbTables);
        QWidget::setTabOrder(cmbTables, tableView);
        QWidget::setTabOrder(tableView, pushInsert);
        QWidget::setTabOrder(pushInsert, pushRemove);
        QWidget::setTabOrder(pushRemove, pushApply_2);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuFile->addAction(actionExit);
        menuTools->addAction(menuOptions->menuAction());
        menuTools->addAction(menuBackups->menuAction());
        menuOptions->addAction(actionShow_startup_message);
        menuOptions->addAction(actionShow_SQL_message);
        menuBackups->addAction(actionCreate_backup);
        menuBackups->addAction(actionRestore_backup);

        retranslateUi(conf_appClass);
        QObject::connect(actionExit, SIGNAL(triggered()), conf_appClass, SLOT(close()));
        QObject::connect(pushConnect, SIGNAL(clicked()), conf_appClass, SLOT(connectDB()));
        QObject::connect(pushDisconnect, SIGNAL(clicked()), conf_appClass, SLOT(disconnectDB()));
        QObject::connect(cmbCountry, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(filterModel(QString)));
        QObject::connect(pushApply, SIGNAL(clicked()), conf_appClass, SLOT(apply()));
        QObject::connect(cmbCountry, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(enableApply()));
        QObject::connect(cmbCity, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(enableApply()));
        QObject::connect(cmbTables, SIGNAL(currentIndexChanged(QString)), conf_appClass, SLOT(showTable(QString)));
        QObject::connect(pushInsert, SIGNAL(clicked()), conf_appClass, SLOT(insertRow()));
        QObject::connect(pushRemove, SIGNAL(clicked()), conf_appClass, SLOT(removeRow()));
        QObject::connect(pushApply_2, SIGNAL(clicked()), conf_appClass, SLOT(applyChanges2Table()));
        QObject::connect(actionShow_SQL_message, SIGNAL(triggered(bool)), conf_appClass, SLOT(showSqlMessages(bool)));

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(conf_appClass);
    } // setupUi

    void retranslateUi(QMainWindow *conf_appClass)
    {
        conf_appClass->setWindowTitle(QApplication::translate("conf_appClass", "Medfisis Configurator", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("conf_appClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("conf_appClass", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        actionShow_startup_message->setText(QApplication::translate("conf_appClass", "Show startup message", 0, QApplication::UnicodeUTF8));
        actionCreate_backup->setText(QApplication::translate("conf_appClass", "Create backup", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCreate_backup->setStatusTip(QApplication::translate("conf_appClass", "Create backup from file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionCreate_backup->setWhatsThis(QApplication::translate("conf_appClass", "Creates backup from file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionRestore_backup->setText(QApplication::translate("conf_appClass", "Restore backup", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionRestore_backup->setStatusTip(QApplication::translate("conf_appClass", "Restore backup from file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionRestore_backup->setWhatsThis(QApplication::translate("conf_appClass", "Restores backup from file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        actionShow_SQL_message->setText(QApplication::translate("conf_appClass", "Show SQL messages", 0, QApplication::UnicodeUTF8));
        lbHost->setText(QApplication::translate("conf_appClass", "Host", 0, QApplication::UnicodeUTF8));
        lbDataSource->setText(QApplication::translate("conf_appClass", "Database", 0, QApplication::UnicodeUTF8));
        lbUsername->setText(QApplication::translate("conf_appClass", "Username", 0, QApplication::UnicodeUTF8));
        lbPassword->setText(QApplication::translate("conf_appClass", "Password", 0, QApplication::UnicodeUTF8));
        lbDriver->setText(QApplication::translate("conf_appClass", "Driver", 0, QApplication::UnicodeUTF8));
        pushConnect->setText(QString());
        pushDisconnect->setText(QString());
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("conf_appClass", "Connection Properties", 0, QApplication::UnicodeUTF8));
        groupSettings->setTitle(QString());
        label_2->setText(QApplication::translate("conf_appClass", "Country", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("conf_appClass", "City", 0, QApplication::UnicodeUTF8));
        pushApply->setText(QApplication::translate("conf_appClass", "Apply", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("conf_appClass", "Global Settings", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupTables->setToolTip(QApplication::translate("conf_appClass", "This control allows the edition of any database table, including inserting and removing records.\n"
" Choose a table listed in the combo box, edit it by changing values and using the bottoms on the left to add/remove rows, and submit changes by pressing apply.\n"
" To enable edition again, you just have to select another table.\n"
" *Attention*: this function operates directly on the database, so there are no undos - be carefull with any changes you make! ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        groupTables->setStatusTip(QApplication::translate("conf_appClass", "This control allows the edition of any database table, including inserting and removing records. ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        groupTables->setWhatsThis(QApplication::translate("conf_appClass", "This control allows the edition of any database table, including inserting and removing records.\n"
" Choose a table listed in the combo box, edit it by changing values and using the bottoms on the left to add/remove rows, and submit changes by pressing apply.\n"
" To enable edition again, you just have to select another table.\n"
" *Attention*: this function operates directly on the database, so there are no undos - be carefull with any changes you make! ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupTables->setTitle(QString());
        label_3->setText(QApplication::translate("conf_appClass", "Choose Table:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmbTables->setToolTip(QApplication::translate("conf_appClass", "Database tables", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        cmbTables->setStatusTip(QApplication::translate("conf_appClass", "Database tables", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        cmbTables->setWhatsThis(QApplication::translate("conf_appClass", "This control lists database tables.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        pushInsert->setToolTip(QApplication::translate("conf_appClass", "Insert row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushInsert->setStatusTip(QApplication::translate("conf_appClass", "Insert row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushInsert->setWhatsThis(QApplication::translate("conf_appClass", "Inserts row into table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushInsert->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushRemove->setToolTip(QApplication::translate("conf_appClass", "Remove row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushRemove->setStatusTip(QApplication::translate("conf_appClass", "Remove row", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushRemove->setWhatsThis(QApplication::translate("conf_appClass", "Removes row into table", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushRemove->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushApply_2->setToolTip(QApplication::translate("conf_appClass", "Apply changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushApply_2->setStatusTip(QApplication::translate("conf_appClass", "Apply changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushApply_2->setWhatsThis(QApplication::translate("conf_appClass", "Applies changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushApply_2->setText(QApplication::translate("conf_appClass", "Apply", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("conf_appClass", "Edit Tables", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("conf_appClass", "File", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("conf_appClass", "Tools", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("conf_appClass", "Options", 0, QApplication::UnicodeUTF8));
        menuBackups->setTitle(QApplication::translate("conf_appClass", "Backups", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class conf_appClass: public Ui_conf_appClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONF_APP_H
