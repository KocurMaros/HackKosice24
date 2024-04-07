#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_C_button_clicked()
{
    if(is_recording){
        std::cout << "C" << ui->Octave_combobox->currentIndex()+1 << std::endl;
        std::cout << "Duration: " << note_type[ui->Duration_combobox->currentIndex()] << std::endl;
        std::cout << "BPM: " << ui->BPM_lineedit->text().toInt() << std::endl;
        recorded_melody.push_back(Tone(C[ui->Octave_combobox->currentIndex()],note_type[ui->Duration_combobox->currentIndex()],ui->BPM_lineedit->text().toInt()));
    }
}


void MainWindow::on_D_button_clicked()
{

}


void MainWindow::on_E_button_clicked()
{

}


void MainWindow::on_F_button_clicked()
{

}


void MainWindow::on_G_button_clicked()
{

}


void MainWindow::on_A_button_clicked()
{

}


void MainWindow::on_B_button_clicked()
{

}


void MainWindow::on_Pause_button_clicked()
{

}


void MainWindow::on_Record_button_clicked()
{
    if(!is_recording){
        is_recording = true;
        recorded_melody.clear();
    }
    else{
        is_recording = false;
    }
}


void MainWindow::on_Erase_button_clicked()
{
    recorded_melody.clear();
}


void MainWindow::on_Save_button_clicked()
{

}


void MainWindow::on_Load_button_clicked()
{

}


void MainWindow::on_Send_button_clicked()
{

}


void MainWindow::on_BPM_lineedit_textEdited(const QString &arg1)
{

}


void MainWindow::on_BPM_lineedit_textChanged(const QString &arg1)
{
}


void MainWindow::on_BPM_lineedit_editingFinished()
{
    QRegExp rx("[^0-9]"); // Regular expression to match any character that is not a digit
    if (ui->BPM_lineedit->text().contains(rx)) {
        //set the text to the last bpm
        ui->BPM_lineedit->setText(QString::number(last_bpm));
    }
    else{
        //check if it isnt lower than 1

        if(ui->BPM_lineedit->text().toInt() < 1){
            ui->BPM_lineedit->setText(QString::number(1));
            last_bpm = 1;
        }
        else if(ui->BPM_lineedit->text().toInt() > 300){
            ui->BPM_lineedit->setText(QString::number(300));
            last_bpm = 300;
        }
        else{
            last_bpm = ui->BPM_lineedit->text().toInt();
        }
    }
}

