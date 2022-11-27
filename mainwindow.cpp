#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addStandards();
    loadStudents();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addStandards()
{
    mStandards.append("1CE Identify patterns of same and different phrases in simple poems and songs.");
    mStandards.append("2CE Identify rounds and canons.");
    mStandards.append("3CE Listen to and identify music of various styles, composers, periods andcultures.");
    mStandards.append("4CE Identify elements of music using developmentally appropriate vocabulary (e.g., rhythm, syllables and solfege).");
    mStandards.append("5CE Explore selected musical instruments visually and aurally.");
    mStandards.append("6CE Attend live music performances with emphasis on instrument and voice identification.");

    mStandards.append("1PR Demonstrate rounds and canons.");
    mStandards.append("2PR Sing (using head voice and appropriate posture) and move to music of various styles, composers and cultures with accurate pitch and rhythm.");
    mStandards.append("3PR Read, write and perform using eighth notes, quarter notes, half notes and quarter rests in 2/4 and 4/4 meter.");
    mStandards.append("4PR Improvise and compose simple rhythmic and melodic phrases.");
    mStandards.append("5PR Read, write and perform using pentatonic (la-sol-mi-re-do) melodies on the treble staff in G-do, F-do, and C-do using a system (e.g., solfege, numbers or letters).");
    mStandards.append("6PR Play a variety of classroom instruments, alone and with others, and demonstrate proper technique.");

    mStandards.append("1RE Explain how music is used for a variety of purposes and occasions.");
    mStandards.append("2RE Discuss music of various composers, periods, cultures and contrasting styles.");
    mStandards.append("3RE Discuss how music communicates feelings, moods, images and meaning.");
    mStandards.append("4RE Interpret music through dance, drama and visual art.");
    mStandards.append("5RE Respond to patterns of same and different phrases in simple poems and songs.");
    mStandards.append("6RE Discuss similarities and differences among the arts including connections between music and other curricular subjects.");
    mStandards.append("7RE Discuss and write about their observations of types of voices and instruments heard in performances");

    ui->standardDropdown->addItems(mStandards);
    mCurrentStandard = mStandards[0];
}

void MainWindow::setupConnections()
{
    connect(ui->nextStandardBtn, SIGNAL(clicked()), this, SLOT(incrementStandard()));
    connect(ui->prevStandardBtn, SIGNAL(clicked()), this, SLOT(decrementStandard()));

    connect(ui->nextStudentBtn, SIGNAL(clicked()), this, SLOT(incrementStudent()));
    connect(ui->prevStudentBtn, SIGNAL(clicked()), this, SLOT(decrementStudent()));

    connect(ui->standardDropdown, SIGNAL(currentTextChanged(QString)), this, SLOT(setNewStandard(QString)));
    connect(ui->studentDropdown, SIGNAL(currentTextChanged(QString)), this, SLOT(setNewStudent(QString)));

    connect(ui->zeroBtn, &QRadioButton::clicked, this, [this] { setRating(0); });
    connect(ui->oneBtn, &QRadioButton::clicked, this, [this] { setRating(1); });
    connect(ui->twoBtn, &QRadioButton::clicked, this, [this] { setRating(2); });
    connect(ui->threeBtn, &QRadioButton::clicked, this, [this] { setRating(3); });
    connect(ui->fourBtn, &QRadioButton::clicked, this, [this] { setRating(4); });

    connect(ui->zeroLineEdit, &QLineEdit::textChanged, this, [this] { ui->zeroBtn->setChecked(true); setRating(0); });
    connect(ui->oneLineEdit, &QLineEdit::textChanged, this, [this] { ui->oneBtn->setChecked(true); setRating(1); });
    connect(ui->twoLineEdit, &QLineEdit::textChanged, this, [this] { ui->twoBtn->setChecked(true); setRating(2); });
    connect(ui->threeLineEdit, &QLineEdit::textChanged, this, [this] { ui->threeBtn->setChecked(true); setRating(3); });
    connect(ui->fourLineEdit, &QLineEdit::textChanged, this, [this] { ui->fourBtn->setChecked(true); setRating(4); });

    connect(ui->commentBox, SIGNAL(textChanged()), this, SLOT(setComment()));

    connect(ui->finishBtn, SIGNAL(clicked(bool)), this, SLOT(exportData()));
}

void MainWindow::loadStudents()
{
    QFile studentsFile("C:\\Users\\kgill\\Documents\\Projects\\StudentAssessment\\build\\students.txt");
    studentsFile.open(QIODevice::ReadOnly);

    QTextStream in(&studentsFile);

    while (!in.atEnd())
    {
        QString studentName = in.readLine();

        if (mCurrentStudent == "")
        {
            mCurrentStudent = studentName;
        }

        ui->studentDropdown->addItem(studentName);

        QMap<QString, QString> studentStandardMap;

        for (const QString &standard : mStandards)
        {
            studentStandardMap.insert(standard, "");
        }

        mStandardsMap.insert(studentName, studentStandardMap);
    }
}

void MainWindow::incrementStandard()
{
    int currentIndex = ui->standardDropdown->currentIndex();

    if (currentIndex < ui->standardDropdown->count() - 1)
    {
        ++currentIndex;
        ui->standardDropdown->setCurrentIndex(currentIndex);
    }

    if (currentIndex == ui->standardDropdown->count() - 1)
    {
        ui->nextStandardBtn->setDisabled(true);
    }
    else if (currentIndex > 0)
    {
        ui->prevStandardBtn->setEnabled(true);
    }
}

void MainWindow::decrementStandard()
{
    int currentIndex = ui->standardDropdown->currentIndex();

    if (currentIndex != 0)
    {
        --currentIndex;
        ui->standardDropdown->setCurrentIndex(currentIndex);
    }

    if (currentIndex == 0)
    {
        ui->prevStandardBtn->setDisabled(true);
    }
    else if (currentIndex != ui->standardDropdown->count() - 1)
    {
        ui->nextStandardBtn->setEnabled(true);
    }
}

void MainWindow::incrementStudent()
{
    int currentIndex = ui->studentDropdown->currentIndex();

    if (currentIndex < ui->studentDropdown->count() - 1)
    {
        ++currentIndex;
        ui->studentDropdown->setCurrentIndex(currentIndex);
    }

    if (currentIndex == ui->studentDropdown->count() - 1)
    {
        ui->nextStudentBtn->setDisabled(true);
    }
    else if (currentIndex > 0)
    {
        ui->prevStudentBtn->setEnabled(true);
    }
}

void MainWindow::decrementStudent()
{
    int currentIndex = ui->studentDropdown->currentIndex();

    if (currentIndex != 0)
    {
        --currentIndex;
        ui->studentDropdown->setCurrentIndex(currentIndex);
    }

    if (currentIndex == 0)
    {
        ui->prevStudentBtn->setDisabled(true);
    }
    else if (currentIndex != ui->studentDropdown->count() - 1)
    {
        ui->nextStudentBtn->setEnabled(true);
    }
}

void MainWindow::setRating(int rating)
{
    switch (rating)
    {
        case 0:
        {
            // First, check to see if there is already a standard
            QString savedStandard = mStandardsMap[mCurrentStudent][mCurrentStandard];

            // If it is blank, create it
            if (savedStandard == "")
            {
                QString standardString = QString("0 - %1 | ").arg(ui->zeroLineEdit->text());
                mStandardsMap[mCurrentStudent][mCurrentStandard] = standardString;
            }
            // If it isn't blank, replace the current rating with the new rating
            else
            {
                QStringList currentStandardStringSplit =  mStandardsMap[mCurrentStudent][mCurrentStandard].split(" | ");
                QString newStandardString = QString("0 - %1 | %2").arg(ui->zeroLineEdit->text(), currentStandardStringSplit[1]);
                mStandardsMap[mCurrentStudent][mCurrentStandard] = newStandardString;
            }
            break;
        }

        case 1:
        {
            QString savedStandard = mStandardsMap[mCurrentStudent][mCurrentStandard];

            if (savedStandard == "")
            {
                QString standardString = QString("1 - %1 | ").arg(ui->oneLineEdit->text());
                mStandardsMap[mCurrentStudent][mCurrentStandard] = standardString;
            }
            else
            {
                QStringList currentStandardStringSplit =  mStandardsMap[mCurrentStudent][mCurrentStandard].split(" | ");
                QString newStandardString = QString("1 - %1 | %2").arg(ui->oneLineEdit->text(), currentStandardStringSplit[1]);
                mStandardsMap[mCurrentStudent][mCurrentStandard] = newStandardString;
            }
            break;
        }

        case 2:
        {
            QString savedStandard = mStandardsMap[mCurrentStudent][mCurrentStandard];

            if (savedStandard == "")
            {
                QString standardString = QString("2 - %1 | ").arg(ui->twoLineEdit->text());
                mStandardsMap[mCurrentStudent][mCurrentStandard] = standardString;
            }
            else
            {
                QStringList currentStandardStringSplit =  mStandardsMap[mCurrentStudent][mCurrentStandard].split(" | ");
                QString newStandardString = QString("2 - %1 | %2").arg(ui->twoLineEdit->text(), currentStandardStringSplit[1]);
                mStandardsMap[mCurrentStudent][mCurrentStandard] = newStandardString;
            }
            break;
        }

        case 3:
        {
            QString savedStandard = mStandardsMap[mCurrentStudent][mCurrentStandard];

            if (savedStandard == "")
            {
                QString standardString = QString("3 - %1 | ").arg(ui->threeLineEdit->text());
                mStandardsMap[mCurrentStudent][mCurrentStandard] = standardString;
            }
            else
            {
                QStringList currentStandardStringSplit =  mStandardsMap[mCurrentStudent][mCurrentStandard].split(" | ");
                QString newStandardString = QString("3 - %1 | %2").arg(ui->threeLineEdit->text(), currentStandardStringSplit[1]);
                mStandardsMap[mCurrentStudent][mCurrentStandard] = newStandardString;
            }
            break;
        }

        case 4:
        {
            QString savedStandard = mStandardsMap[mCurrentStudent][mCurrentStandard];

            if (savedStandard == "")
            {
                QString standardString = QString("4 - %1 | ").arg(ui->fourLineEdit->text());
                mStandardsMap[mCurrentStudent][mCurrentStandard] = standardString;
            }
            else
            {
                QStringList currentStandardStringSplit =  mStandardsMap[mCurrentStudent][mCurrentStandard].split(" | ");
                QString newStandardString = QString("4 - %1 | %2").arg(ui->fourLineEdit->text(), currentStandardStringSplit[1]);
                mStandardsMap[mCurrentStudent][mCurrentStandard] = newStandardString;
            }
            break;
        }
    }
}

void MainWindow::setComment()
{
    if (mStandardsMap[mCurrentStudent][mCurrentStandard] == "")
    {
        ui->zeroBtn->setChecked(true);
        setRating(0);
    }

    QStringList currentStandardStringSplit = mStandardsMap[mCurrentStudent][mCurrentStandard].split(" | ");
    mStandardsMap[mCurrentStudent][mCurrentStandard] = QString("%1 | %2").arg(currentStandardStringSplit[0], ui->commentBox->toPlainText());
}

void MainWindow::loadData()
{
    QString currentStandardString = mStandardsMap[mCurrentStudent][mCurrentStandard];
    QStringList currentStandardStringSplit = currentStandardString.split(" | ");

    if (currentStandardString != "")
    {
        // Set the rating
        int rating = QString(currentStandardString[0]).toInt();
        QString ratingText = currentStandardStringSplit[0].split(" - ")[1];

        switch (rating)
        {
            case 0:
            {
                ui->zeroBtn->setChecked(true);
                ui->zeroLineEdit->setText(ratingText);
                break;
            }
            case 1:
            {
                ui->oneBtn->setChecked(true);
                ui->oneLineEdit->setText(ratingText);
                break;
            }
            case 2:
            {
                ui->twoBtn->setChecked(true);
                ui->twoLineEdit->setText(ratingText);
                break;
            }
            case 3:
            {
                ui->threeBtn->setChecked(true);
                ui->threeLineEdit->setText(ratingText);
                break;
            }
            case 4:
            {
                ui->fourBtn->setChecked(true);
                ui->fourLineEdit->setText(ratingText);
                break;
            }
        }

        ui->commentBox->setText(currentStandardStringSplit[1]);
    }
    else
    {
        ui->commentBox->setText("");
    }
}

void MainWindow::setNewStandard(QString standard)
{
    mCurrentStandard = standard;
    loadData();

    if (ui->standardDropdown->currentIndex() == 0)
    {
        ui->prevStandardBtn->setEnabled(false);
        ui->nextStandardBtn->setEnabled(true);
    }
    else if (ui->standardDropdown->currentIndex() == ui->standardDropdown->count() - 1)
    {
        ui->prevStandardBtn->setEnabled(true);
        ui->nextStandardBtn->setEnabled(false);
    }
    else
    {
        ui->prevStandardBtn->setEnabled(true);
        ui->nextStandardBtn->setEnabled(true);
    }
}

void MainWindow::setNewStudent(QString student)
{
    mCurrentStudent = student;
    loadData();

    if (ui->studentDropdown->currentIndex() == 0)
    {
        ui->nextStudentBtn->setEnabled(true);
        ui->prevStudentBtn->setEnabled(false);
    }
    else if (ui->studentDropdown->currentIndex() == ui->studentDropdown->count() - 1)
    {
        ui->prevStudentBtn->setEnabled(true);
        ui->nextStudentBtn->setEnabled(false);
    }
    else
    {
        ui->prevStudentBtn->setEnabled(true);
        ui->nextStudentBtn->setEnabled(true);
    }
}

void MainWindow::exportData()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export File", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)) + ".md";

    QFile outFile(fileName);

    outFile.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream outStream(&outFile);

    for (QString student : mStandardsMap.keys())
    {
        outStream << "# **" << student << "**";
        for (QString standard : mStandardsMap[student].keys())
        {
            outStream << "\n\t## " << standard << "\n\t\t ###" << mStandardsMap[student][standard] << "\n";
        }
    }

    outFile.close();
}

