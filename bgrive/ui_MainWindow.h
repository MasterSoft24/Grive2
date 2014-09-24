/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *m_action_exit;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTreeView *m_dir;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *m_title;
    QLabel *m_icon;
    QLabel *label_2;
    QLineEdit *m_filename;
    QLabel *label_4;
    QLineEdit *m_mime_type;
    QLabel *label_3;
    QDateTimeEdit *m_last_update;
    QGraphicsView *m_preview;
    QMenuBar *m_menubar;
    QMenu *m_menu_file;
    QStatusBar *m_statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        m_action_exit = new QAction(MainWindow);
        m_action_exit->setObjectName(QString::fromUtf8("m_action_exit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        m_dir = new QTreeView(splitter);
        m_dir->setObjectName(QString::fromUtf8("m_dir"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_dir->sizePolicy().hasHeightForWidth());
        m_dir->setSizePolicy(sizePolicy);
        splitter->addWidget(m_dir);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_title = new QLineEdit(widget);
        m_title->setObjectName(QString::fromUtf8("m_title"));

        gridLayout->addWidget(m_title, 0, 1, 1, 1);

        m_icon = new QLabel(widget);
        m_icon->setObjectName(QString::fromUtf8("m_icon"));

        gridLayout->addWidget(m_icon, 0, 2, 2, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        m_filename = new QLineEdit(widget);
        m_filename->setObjectName(QString::fromUtf8("m_filename"));

        gridLayout->addWidget(m_filename, 1, 1, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        m_mime_type = new QLineEdit(widget);
        m_mime_type->setObjectName(QString::fromUtf8("m_mime_type"));

        gridLayout->addWidget(m_mime_type, 2, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        m_last_update = new QDateTimeEdit(widget);
        m_last_update->setObjectName(QString::fromUtf8("m_last_update"));

        gridLayout->addWidget(m_last_update, 3, 1, 1, 2);

        m_preview = new QGraphicsView(widget);
        m_preview->setObjectName(QString::fromUtf8("m_preview"));

        gridLayout->addWidget(m_preview, 4, 0, 1, 3);

        splitter->addWidget(widget);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        m_menubar = new QMenuBar(MainWindow);
        m_menubar->setObjectName(QString::fromUtf8("m_menubar"));
        m_menubar->setGeometry(QRect(0, 0, 800, 23));
        m_menu_file = new QMenu(m_menubar);
        m_menu_file->setObjectName(QString::fromUtf8("m_menu_file"));
        MainWindow->setMenuBar(m_menubar);
        m_statusbar = new QStatusBar(MainWindow);
        m_statusbar->setObjectName(QString::fromUtf8("m_statusbar"));
        MainWindow->setStatusBar(m_statusbar);

        m_menubar->addAction(m_menu_file->menuAction());
        m_menu_file->addAction(m_action_exit);

        retranslateUi(MainWindow);
        QObject::connect(m_action_exit, SIGNAL(activated()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Grive", 0, QApplication::UnicodeUTF8));
        m_action_exit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Title:", 0, QApplication::UnicodeUTF8));
        m_icon->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Filename:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Mime type:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Last Updated:", 0, QApplication::UnicodeUTF8));
        m_menu_file->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
