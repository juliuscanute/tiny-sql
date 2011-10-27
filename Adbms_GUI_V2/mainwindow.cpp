#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BufferManager.h"
#include "iostream"
#include "string"
#include "string.h"
#include <stdlib.h>
#include "malloc.h"

using namespace std;

buffer buf;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setStyleSheet("QLineEdit{background:light grey;}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{background:light grey;}");
    ui->lineEdit_3->setStyleSheet("QLineEdit{background:light grey;}");
    ui->lineEdit_4->setStyleSheet("QLineEdit{background:light grey;}");
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    buffer buf;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enabler()
{

    int op = this->ui->comboBox->currentIndex();
    ui->lineEdit->setStyleSheet("QLineEdit{background:light grey;}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{background:light grey;}");
    ui->lineEdit_3->setStyleSheet("QLineEdit{background:light grey;}");
    ui->lineEdit_4->setStyleSheet("QLineEdit{background:light grey;}");
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    switch(op)
    {
    case 1:
        {
            ui->lineEdit->setStyleSheet("QLineEdit{background: white;}");
            ui->lineEdit_2->setStyleSheet("QLineEdit{background: white;}");
            ui->lineEdit->setReadOnly(false);
            ui->lineEdit_2->setReadOnly(false);
            break;
        }
    case 2:
        {
            ui->lineEdit->setStyleSheet("QLineEdit{background: white;}");
            ui->lineEdit->setReadOnly(false);
            break;
        }
    case 3:
        {
            ui->lineEdit_3->setStyleSheet("QLineEdit{background: white;}");
            ui->lineEdit_4->setStyleSheet("QLineEdit{background: white;}");
            ui->lineEdit_3->setReadOnly(false);
            ui->lineEdit_4->setReadOnly(false);
            break;
        }
    case 4:
        {
            break;
        }
    case 5:
        {
            ui->lineEdit->setStyleSheet("QLineEdit{background: white;}");
            ui->lineEdit->setReadOnly(false);
            break;
        }
    case 6:
        {
            break;
        }
    case 7:
        {
            ui->lineEdit_3->setStyleSheet("QLineEdit{background: white;}");
            ui->lineEdit_4->setStyleSheet("QLineEdit{background: white;}");
            ui->lineEdit_3->setReadOnly(false);
            ui->lineEdit_4->setReadOnly(false);
            break;
        }
    }
}

void MainWindow::handler()
{
    BUF_POOL* page;
    int bid,op;
    char name[MAX_FILE_NAME];
    string name2;
    bool res;
    op = this->ui->comboBox->currentIndex();
    ui->label_7->clear();
    switch(op)
    {
    case 1:
        {
            strcpy(name,ui->lineEdit->text().toStdString().c_str());
            res = buf.createDB(name,ui->lineEdit_2->text().toInt());
            if(res==true)
                ui->label_7->setText("Created Database Successfully");
            else
                cout<<"Failed to create.."<<endl;
            break;
        }
    case 2:
        {

            strcpy(name,ui->lineEdit->text().toStdString().c_str());
            bid = buf.openDB(name);
            if(bid>0)
            {
                ui->label_7->setText("Opened Database.. Bid:"+bid);
                cout<<"Opened..bid:"<<bid<<endl;
            }
            else
                cout<<"Failed to Open.."<<endl;
            break;
        }
    case 3:
        {
            page = (BUF_POOL*)malloc(sizeof(BUF_POOL));
            page->_dirty=0;
            page->_pageno=ui->lineEdit_3->text().toInt();
            page->_pagedata = "Sample Page Data";
            res = buf.writeIntoDB(ui->lineEdit_4->text().toInt(),page,page->_pageno);
            if(res==true)
                ui->label_7->setText("Write Success");
            break;
        }
    case 4:
        {
            break;
        }
    case 5:
        {
            strcpy(name,ui->lineEdit->text().toStdString().c_str());
            res = buf.closeDB(name);
            if(res==true)
                ui->label_7->setText("Database Closed");
            else
                cout<<"Couldn't close the database"<<endl;
            break;
        }
    case 6:
        {
            break;
        }
    case 7:
        {
            BUF_POOL* page;
            page = buf.ReadPage(ui->lineEdit_4->text().toInt(),ui->lineEdit_3->text().toInt());
//            ui->label_7->setText("Read Success");
            if(page!=NULL)
            {

                cout<<"Read Success.."<<endl/*<<page->_pagedata<<endl*/;
                buf.print_details();
            }
            break;
        }
    case 8:
        {
            break;
        }
    case 9:
        {
            buf.buf_init();
            break;
        }
    case 0:
        {
            ui->label_7->setText("Please select a function");
            break;
        }
    }
    ui->comboBox->setCurrentIndex(0);


}

void MainWindow::init()
{
    buf.buf_init();

}
