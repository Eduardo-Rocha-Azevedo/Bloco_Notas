#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessagebox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include<QColorDialog>
#include <QPrintDialog>
#include <QPrinter>

//construtor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}
//finaliza
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNovo_triggered()
{
    local_arquivo = "";
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}


void MainWindow::on_actionAbrir_2_triggered()
{
    QString filtro = "Todos arquivos(*.*);; Arquivos de texto(*.txt)";
    QString nome_arquivo = QFileDialog::getOpenFileName(this,"Abrir",QDir::homePath(),filtro);
    QFile arquivo(nome_arquivo);
    local_arquivo = nome_arquivo;

    //abre o arquivo
    if(!arquivo.open(QFile::ReadOnly| QFile::Text)){
        QMessageBox::warning(this,"Information","O arquivo não foi aberto");
            return;
    }

    QTextStream entrada(&arquivo);
    QString texto = entrada.readAll();
    ui->textEdit->setText(texto);
    arquivo.close();
}


void MainWindow::on_actionSalvar_como_triggered()
{
    QString filtro = "Todos arquivos(*.*);; Arquivos de texto(*.txt)";
    QString nome_arquivo = QFileDialog::getSaveFileName(this,"Salvar como",QDir::homePath(),filtro);
    //recebe o nome do arquivo
    local_arquivo = nome_arquivo;
    QFile arquivo(nome_arquivo);

    //abre o arquivo
    if(!arquivo.open(QFile::WriteOnly| QFile::Text)){
            QMessageBox::warning(this,"Information","O arquivo não foi salvo");
                return;
    }
    QTextStream saida(&arquivo);
    QString texto = ui->textEdit->toPlainText();
    saida << texto;
    arquivo.flush();
    arquivo.close();
}


void MainWindow::on_actionSalvar_triggered()
{
    QFile arquivo(local_arquivo);

    //abre o arquivo
    if(!arquivo.open(QFile::WriteOnly| QFile::Text)){
                QMessageBox::warning(this,"Information","O arquivo não foi salvo");
                    return;
    }
    QTextStream saida(&arquivo);
    QString texto = ui->textEdit->toPlainText();
    saida << texto;
    arquivo.flush();
    arquivo.close();

}


void MainWindow::on_actionFechar_triggered()
{
    close();
}


void MainWindow::on_actionCopiar_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionRecortar_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionColar_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionDesfazer_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRefazer_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionFonte_triggered()
{
    bool font_ok;
    QFont fonte = QFontDialog::getFont(&font_ok,this);
    if(font_ok){
       ui->textEdit->setFont(fonte);
    }else{
       return;
    }

}


void MainWindow::on_actionCor_triggered()
{
    QColor cor = QColorDialog::getColor(Qt::black, this, "Escolha uma Cor");
    if(cor.isValid()){
       ui->textEdit->setTextColor(cor);
    }
}


void MainWindow::on_actionCor_do_Fundo_triggered()
{
    QColor cor = QColorDialog::getColor(Qt::black, this, "Escolha uma Cor");
    if(cor.isValid()){
       ui->textEdit->setTextBackgroundColor(cor);
    }

}


void MainWindow::on_actionImprimir_triggered()
{
    QPrinter imp;
    imp.setPrinterName("Impressora");
    QPrintDialog cx_imp(&imp,this);
    if(cx_imp.exec()==QDialog::Rejected){
       return;
    }
    ui->textEdit->print(&imp);
}

