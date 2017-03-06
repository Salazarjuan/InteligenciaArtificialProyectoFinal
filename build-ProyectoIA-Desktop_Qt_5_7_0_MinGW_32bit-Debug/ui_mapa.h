/********************************************************************************
** Form generated from reading UI file 'mapa.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPA_H
#define UI_MAPA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mapa
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *busquedas_cb;
    QPushButton *buscarSolucion_btn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Mapa)
    {
        if (Mapa->objectName().isEmpty())
            Mapa->setObjectName(QStringLiteral("Mapa"));
        Mapa->resize(1207, 786);
        centralWidget = new QWidget(Mapa);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 0, 1011, 731));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(1020, -1, 181, 161));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        busquedas_cb = new QComboBox(verticalLayoutWidget);
        busquedas_cb->setObjectName(QStringLiteral("busquedas_cb"));

        verticalLayout->addWidget(busquedas_cb);

        buscarSolucion_btn = new QPushButton(verticalLayoutWidget);
        buscarSolucion_btn->setObjectName(QStringLiteral("buscarSolucion_btn"));

        verticalLayout->addWidget(buscarSolucion_btn);

        Mapa->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Mapa);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1207, 21));
        Mapa->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Mapa);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Mapa->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Mapa);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Mapa->setStatusBar(statusBar);

        retranslateUi(Mapa);

        QMetaObject::connectSlotsByName(Mapa);
    } // setupUi

    void retranslateUi(QMainWindow *Mapa)
    {
        Mapa->setWindowTitle(QApplication::translate("Mapa", "Mapa", 0));
        busquedas_cb->clear();
        busquedas_cb->insertItems(0, QStringList()
         << QApplication::translate("Mapa", "Preferente por amplitud", 0)
         << QApplication::translate("Mapa", "Preferente por costo", 0)
         << QApplication::translate("Mapa", "Preferente por profundidad", 0)
         << QApplication::translate("Mapa", "A*", 0)
         << QApplication::translate("Mapa", "B\303\272squeda \303\201vara", 0)
        );
        buscarSolucion_btn->setText(QApplication::translate("Mapa", "Buscar Soluci\303\263n", 0));
    } // retranslateUi

};

namespace Ui {
    class Mapa: public Ui_Mapa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPA_H
