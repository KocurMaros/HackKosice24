#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pitches.h"
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_C_button_clicked();

    void on_D_button_clicked();

    void on_E_button_clicked();

    void on_F_button_clicked();

    void on_G_button_clicked();

    void on_A_button_clicked();

    void on_B_button_clicked();

    void on_Pause_button_clicked();

    void on_Record_button_clicked();

    void on_Erase_button_clicked();

    void on_Save_button_clicked();

    void on_Load_button_clicked();

    void on_Send_button_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<int> C = {NOTE_C1, NOTE_C2,NOTE_C3,NOTE_C4,NOTE_C5,NOTE_C6,NOTE_C7};
    std::vector<int> D = {NOTE_D1, NOTE_D2,NOTE_D3,NOTE_D4,NOTE_D5,NOTE_D6,NOTE_D7};
    std::vector<int> E = {NOTE_E1, NOTE_E2,NOTE_E3,NOTE_E4,NOTE_E5,NOTE_E6,NOTE_E7};
    std::vector<int> F = {NOTE_F1, NOTE_F2,NOTE_F3,NOTE_F4,NOTE_F5,NOTE_F6,NOTE_F7};
    std::vector<int> G = {NOTE_G1, NOTE_G2,NOTE_G3,NOTE_G4,NOTE_G5,NOTE_G6,NOTE_G7};
    std::vector<int> A = {NOTE_A1, NOTE_A2,NOTE_A3,NOTE_A4,NOTE_A5,NOTE_A6,NOTE_A7};
    std::vector<int> B = {NOTE_B1, NOTE_B2,NOTE_B3,NOTE_B4,NOTE_B5,NOTE_B6,NOTE_B7};
    std::vector<int> note_type = {4,8,16};
    std::vector<Tone> recorded_melody;
    int recorded_melody_bpm;
    bool is_recording = false;
};
#endif // MAINWINDOW_H
