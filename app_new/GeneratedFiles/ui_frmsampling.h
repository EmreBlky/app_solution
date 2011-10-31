/********************************************************************************
** Form generated from reading UI file 'frmsampling.ui'
**
** Created: Mon 31. Oct 16:15:02 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSAMPLING_H
#define UI_FRMSAMPLING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrmSampling
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *lbSource;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *cmbSchema;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushBack;
    QPushButton *pushApply;

    void setupUi(QWidget *FrmSampling)
    {
        if (FrmSampling->objectName().isEmpty())
            FrmSampling->setObjectName(QString::fromUtf8("FrmSampling"));
        FrmSampling->resize(630, 434);
        verticalLayout = new QVBoxLayout(FrmSampling);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(FrmSampling);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lbSource = new QLabel(FrmSampling);
        lbSource->setObjectName(QString::fromUtf8("lbSource"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbSource->sizePolicy().hasHeightForWidth());
        lbSource->setSizePolicy(sizePolicy);
        lbSource->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(220, 220, 220, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));\n"
"font: 75 10pt \"Fixedsys\";"));
        lbSource->setFrameShape(QFrame::StyledPanel);
        lbSource->setFrameShadow(QFrame::Raised);
        lbSource->setScaledContents(true);

        horizontalLayout_2->addWidget(lbSource);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(FrmSampling);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        cmbSchema = new QComboBox(FrmSampling);
        cmbSchema->setObjectName(QString::fromUtf8("cmbSchema"));

        horizontalLayout_3->addWidget(cmbSchema);


        verticalLayout->addLayout(horizontalLayout_3);

        tableView = new QTableView(FrmSampling);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setAlternatingRowColors(true);

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(308, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushBack = new QPushButton(FrmSampling);
        pushBack->setObjectName(QString::fromUtf8("pushBack"));

        horizontalLayout->addWidget(pushBack);

        pushApply = new QPushButton(FrmSampling);
        pushApply->setObjectName(QString::fromUtf8("pushApply"));

        horizontalLayout->addWidget(pushApply);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FrmSampling);
        QObject::connect(pushApply, SIGNAL(clicked()), FrmSampling, SLOT(apply()));
        QObject::connect(pushBack, SIGNAL(clicked()), FrmSampling, SLOT(back()));
        QObject::connect(cmbSchema, SIGNAL(currentIndexChanged(int)), FrmSampling, SLOT(initRecords(int)));

        QMetaObject::connectSlotsByName(FrmSampling);
    } // setupUi

    void retranslateUi(QWidget *FrmSampling)
    {
        FrmSampling->setWindowTitle(QApplication::translate("FrmSampling", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FrmSampling", "Source", 0, QApplication::UnicodeUTF8));
        lbSource->setText(QApplication::translate("FrmSampling", "[SOURCE]", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FrmSampling", "Choose Sampling Schema", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushBack->setToolTip(QApplication::translate("FrmSampling", "Go back", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushBack->setStatusTip(QApplication::translate("FrmSampling", "Go back to previous form", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushBack->setWhatsThis(QApplication::translate("FrmSampling", "Goes back to previous form", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushBack->setText(QApplication::translate("FrmSampling", "Back", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushApply->setToolTip(QApplication::translate("FrmSampling", "Apply changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushApply->setStatusTip(QApplication::translate("FrmSampling", "Apply", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        pushApply->setWhatsThis(QApplication::translate("FrmSampling", "Applies changes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushApply->setText(QApplication::translate("FrmSampling", "Apply", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FrmSampling: public Ui_FrmSampling {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSAMPLING_H
