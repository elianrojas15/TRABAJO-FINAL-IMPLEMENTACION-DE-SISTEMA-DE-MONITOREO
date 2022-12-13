#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
using namespace std;


MainWindow::MainWindow(QWidget *parent) // vent
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("VALORES DEL MOTOR");
    ui->pushButton->setEnabled(false);
    dirFile=ui->lineEdit->text() + ui->lineEdit_2->text();

    qDebug() << dirFile;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_2_clicked()
{
    readWrite = true;
    ui->pushButton->setText("LEER");
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_radioButton_clicked()
{
    readWrite = false;
    ui->pushButton->setText("VALORES MOTOR");
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_pushButton_clicked()
{
    QString text;
    QFile file(dirFile);
    if(readWrite){
        //Leer
         if(file.open(QFile::ReadOnly | QFile::Text)){
             QTextStream in(&file);
             text = in.readAll();
             file.close();
        }
        else{
            qDebug() << "Error al Abrir el Archivo: No se puede leer!";
        }
    }

    QString valores[10];
    int cont = 0;
    QString str = text;

        QStringList List;

        List = str.split(";");
        foreach(QString item, List)
        {
            QString numeros = item;
            QStringList List2;
            List2 = numeros.split(":");
            foreach(QString vals, List2)
            {
                valores[cont] = vals;
                cont++;
            }
        }
        QFile h("/home/alse/Downloads/val_final.txt");
            if(!h.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                cout << "Open failed." << endl;
            }
            QTextStream txtOutput(&h);
            //VALORES INSTANTANEOS
            txtOutput << valores[1] << endl; //VELOCIDAD
            txtOutput << valores[3] << endl; //FRECUENIA
            txtOutput << valores[5] << endl; //VOLTAJE
            txtOutput << valores[7] << endl; //TEMPERATURA
            txtOutput << valores[9] << endl; //TIEMPO DE OPERACION

            h.close();

            QFile t("/home/alse/Downloads/val_final.txt");
                if(!t.open(QIODevice::ReadOnly))
                    QMessageBox::information(0,"info",file.errorString());

                QTextStream in(&t);

                ui->plainTextEdit->setPlainText(in.readAll());

    double v_act = valores[1].toDouble();
    double f_act = valores[3].toDouble();
    double vol_act = valores[5].toDouble();
    double t_act = valores[7].toDouble();

    if(1710 < v_act && v_act < 1890)
    {
        QPalette color = ui->velocidad->palette();
        color.setColor(QPalette::Base,Qt::green);
        ui->velocidad->setPalette(color);
    }
    else
    {
        QPalette color = ui->velocidad->palette();
        color.setColor(QPalette::Base,Qt::red);
        ui->velocidad->setPalette(color);
    }
    if(57 < f_act && f_act < 63)
    {
        QPalette color = ui->frecuencia->palette();
        color.setColor(QPalette::Base,Qt::green);
        ui->frecuencia->setPalette(color);
    }
    else
    {
        QPalette color = ui->frecuencia->palette();
        color.setColor(QPalette::Base,Qt::red);
        ui->frecuencia->setPalette(color);
    }
    if(198 < vol_act && vol_act < 242)
    {
        QPalette color = ui->voltaje->palette();
        color.setColor(QPalette::Base,Qt::green);
        ui->voltaje->setPalette(color);
    }
    else
    {
        QPalette color = ui->voltaje->palette();
        color.setColor(QPalette::Base,Qt::red);
        ui->voltaje->setPalette(color);
    }
    if(57 < t_act && t_act < 63)
    {
        QPalette color = ui->temperatura->palette();
        color.setColor(QPalette::Base,Qt::green);
        ui->temperatura->setPalette(color);
    }
    else
    {
        QPalette color = ui->temperatura->palette();
        color.setColor(QPalette::Base,Qt::red);
        ui->temperatura->setPalette(color);
    }

}


