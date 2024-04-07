#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //TODO: osetrit ci to neni blbost
    port = ui->Port_lineedit->text().toStdString();
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
        recorded_melody.push_back(MelodyDataStructure(C[ui->Octave_combobox->currentIndex()],note_type[ui->Duration_combobox->currentIndex()],ui->BPM_lineedit->text().toInt()));
    }
}


void MainWindow::on_D_button_clicked()
{
    if(is_recording){
        std::cout << "D" << ui->Octave_combobox->currentIndex()+1 << std::endl;
        std::cout << "Duration: " << note_type[ui->Duration_combobox->currentIndex()] << std::endl;
        std::cout << "BPM: " << ui->BPM_lineedit->text().toInt() << std::endl;
        recorded_melody.push_back(MelodyDataStructure(D[ui->Octave_combobox->currentIndex()],note_type[ui->Duration_combobox->currentIndex()],ui->BPM_lineedit->text().toInt()));
    }
}


void MainWindow::on_E_button_clicked()
{
    if(is_recording){
        std::cout << "E" << ui->Octave_combobox->currentIndex()+1 << std::endl;
        std::cout << "Duration: " << note_type[ui->Duration_combobox->currentIndex()] << std::endl;
        std::cout << "BPM: " << ui->BPM_lineedit->text().toInt() << std::endl;
        recorded_melody.push_back(MelodyDataStructure(E[ui->Octave_combobox->currentIndex()],note_type[ui->Duration_combobox->currentIndex()],ui->BPM_lineedit->text().toInt()));
    }
}


void MainWindow::on_F_button_clicked()
{
    if(is_recording){
        std::cout << "F" << ui->Octave_combobox->currentIndex()+1 << std::endl;
        std::cout << "Duration: " << note_type[ui->Duration_combobox->currentIndex()] << std::endl;
        std::cout << "BPM: " << ui->BPM_lineedit->text().toInt() << std::endl;
        recorded_melody.push_back(MelodyDataStructure(F[ui->Octave_combobox->currentIndex()],note_type[ui->Duration_combobox->currentIndex()],ui->BPM_lineedit->text().toInt()));
    }
}


void MainWindow::on_G_button_clicked()
{
    if(is_recording){
        std::cout << "G" << ui->Octave_combobox->currentIndex()+1 << std::endl;
        std::cout << "Duration: " << note_type[ui->Duration_combobox->currentIndex()] << std::endl;
        std::cout << "BPM: " << ui->BPM_lineedit->text().toInt() << std::endl;
        recorded_melody.push_back(MelodyDataStructure(G[ui->Octave_combobox->currentIndex()],note_type[ui->Duration_combobox->currentIndex()],ui->BPM_lineedit->text().toInt()));
    }
}


void MainWindow::on_A_button_clicked()
{
    if(is_recording){
        std::cout << "A" << ui->Octave_combobox->currentIndex()+1 << std::endl;
        std::cout << "Duration: " << note_type[ui->Duration_combobox->currentIndex()] << std::endl;
        std::cout << "BPM: " << ui->BPM_lineedit->text().toInt() << std::endl;
        recorded_melody.push_back(MelodyDataStructure(A[ui->Octave_combobox->currentIndex()],note_type[ui->Duration_combobox->currentIndex()],ui->BPM_lineedit->text().toInt()));
    }
}


void MainWindow::on_B_button_clicked()
{
    if(is_recording){
        std::cout << "B" << ui->Octave_combobox->currentIndex()+1 << std::endl;
        std::cout << "Duration: " << note_type[ui->Duration_combobox->currentIndex()] << std::endl;
        std::cout << "BPM: " << ui->BPM_lineedit->text().toInt() << std::endl;
        recorded_melody.push_back(MelodyDataStructure(B[ui->Octave_combobox->currentIndex()],note_type[ui->Duration_combobox->currentIndex()],ui->BPM_lineedit->text().toInt()));
    }
}


void MainWindow::on_Pause_button_clicked()
{
    if(is_recording){
        std::cout << "Pause" << std::endl;
        std::cout << "Duration: " << note_type[ui->Duration_combobox->currentIndex()] << std::endl;
        std::cout << "BPM: " << ui->BPM_lineedit->text().toInt() << std::endl;
        recorded_melody.push_back(MelodyDataStructure(REST,note_type[ui->Duration_combobox->currentIndex()],ui->BPM_lineedit->text().toInt()));
    }
}


void MainWindow::on_Record_button_clicked()
{
    if(!is_recording){
        is_recording = true;
        recorded_melody.clear();
        ui->Record_button->setText("Stop recording");
    }
    else{
        is_recording = false;
        ui->Record_button->setText("Start recording");
    }
}


void MainWindow::on_Erase_button_clicked()
{
    recorded_melody.clear();
}


void MainWindow::on_Save_button_clicked()
{
    if (recorded_melody.empty()) {
        std::cout << "No melody to save" << std::endl;
        return;
    }
    print_melody();
    is_recording = false;
    ui->Record_button->setText("Start recording");

    QString currentDir = QDir::currentPath();

    // Get the directory one level under the current directory
    QDir baseDir(currentDir);
    baseDir.cdUp(); // Navigate one level up

    QString subDir = baseDir.filePath("MyComposer/Melodies");
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", subDir, "Text Files (*.txt)");

    // Check if a file was selected
    if (!filePath.isEmpty()) {
        // Open the selected file for writing
        QFile file(filePath);

        // Open the file in read-only mode
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            // Write some text to the file
            //TODO: write the melody to the file
            QTextStream out(&file);
            for (auto tone : recorded_melody) {
                out << tone.toText() << "\n";
            }
            std::cout << "Saved" << std::endl;
            file.close();
        } else {
            std::cout<< "Failed" <<std::endl;
        }
    }
}


void MainWindow::on_Load_button_clicked()
{
    QString currentDir = QDir::currentPath();

    // Get the directory one level under the current directory
    QDir baseDir(currentDir);
    baseDir.cdUp(); // Navigate one level up

    QString subDir = baseDir.filePath("MyComposer/Melodies");
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", subDir, "Text Files (*.txt)");

    // Check if a file was selected
    if (!filePath.isEmpty()) {
        recorded_melody.clear();
        is_recording = false;
        ui->Record_button->setText("Start recording");
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine(); // Read a line from the file
                MelodyDataStructure tone;
                tone.fromText(line); // Deserialize the Tone object from the text
                recorded_melody.push_back(tone); // Store the read Tone object in the vector
            }
            std::cout << "Loaded" << std::endl;
            file.close();
            print_melody();
        }
        else{
            std::cout << "Failed" << std::endl;
        }
    }
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

void MainWindow::print_melody(){
    for(auto tone : recorded_melody){
        std::cout << tone.getFrequency() << " " << tone.getType() << " " << tone.getBpm() << std::endl;
    }
}


void MainWindow::on_Play_button_clicked()
{
    QString currentDir = QDir::currentPath();

    // Get the directory one level under the current directory
    QDir baseDir(currentDir);
    baseDir.cdUp(); // Navigate one level up
    QString pythonPath = baseDir.filePath("MyComposer/Scripts/play_melody.py");
    QString subDir = baseDir.filePath("MyComposer/Melodies");
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", subDir, "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        if (!QFile::exists(pythonPath)) {
            std::cout << "Python script not found at:" << pythonPath.toStdString() << std::endl;
        }
        else {
            QProcess pythonProcess;
            pythonProcess.start("python", QStringList() << pythonPath << filePath << QString::fromStdString(port));
            if (!pythonProcess.waitForStarted()) {
                std::cout << "Failed to start Python script."<< std::endl;
                return;
            }

            // Wait for the Python process to finish and read its output
            pythonProcess.waitForFinished();
            std::cout << "Python script finished with exit code:" << pythonProcess.exitCode() << std::endl;
            std::cout << "Output:" << QString::fromUtf8(pythonProcess.readAllStandardOutput()).toStdString() << std::endl;
            std::cout << "Error:" << QString::fromUtf8(pythonProcess.readAllStandardError()).toStdString() << std::endl;
        }
    }
    else{
        std::cout << "Failed" << std::endl;
    }

}


void MainWindow::on_Port_lineedit_editingFinished()
{
    port = ui->Port_lineedit->text().toStdString();
}

