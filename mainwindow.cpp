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
    mStandards.insert("K", {});
    mStandards["K"].append("1CE Identify same and different (e.g., fast/slow, loud/soft, high/low and long/short).");
    mStandards["K"].append("2CE Explore steady beat and rhythm.");
    mStandards["K"].append("3CE Listen to and explore the music of various styles, composers, periods and cultures");
    mStandards["K"].append("4CE Explore and identify a wide variety of sounds, including the human voice.");
    mStandards["K"].append("5CE Explore a variety of classroom instruments. (e.g., metals, skins and woods.).");
    mStandards["K"].append("6CE Attend live music performances");
    mStandards["K"].append("8CE Explore connections between sound and its visual representation.");

    mStandards["K"].append("1PR Demonstrate same and different (e.g., fast/slow, loud/soft, high/low and long/short).");
    mStandards["K"].append("2PR Demonstrate a steady beat and maintain it while performing.");
    mStandards["K"].append("3PR Sing (using head voice and appropriate posture) and move to music of various and contrasting styles, composers and cultures.");
    mStandards["K"].append("4PR Create a wide variety of vocal and instrumental sounds.");
    mStandards["K"].append("5PR Play a variety of classroom instruments, alone and with others, and demonstrate proper technique.");
    mStandards["K"].append("6PR Demonstrate audience behavior appropriate for the context and style of music performed.");
    mStandards["K"].append("7PR Create a visual representation of sound.");

    mStandards["K"].append("1RE Share ideas about musical selections of various and contrasting styles, composers and musical periods.");
    mStandards["K"].append("2RE Describe how sounds and music are used in our daily lives.");
    mStandards["K"].append("3RE Describe the difference between steady beat and rhythm.");
    mStandards["K"].append("4RE Identify and connect a concept shared between music and another curricular subject.");
    mStandards["K"].append("5RE Identify and discuss various uses of music in the United States and the various meanings of the term “musician.");
    mStandards["K"].append("6RE Respond to sound with a drawing of how the sound makes them feel.");
    mStandards["K"].append("7RE Offer opinions about their own musical experiences and responses to music.");

    mStandards.insert("First", {});
    mStandards["First"].append("1CE Identify echo and call/response.");
    mStandards["First"].append("2CE Explore steady beat, rhythm and meter.");
    mStandards["First"].append("3CE Listen to and identify music of various and contrasting styles, composers, periods and cultures.");
    mStandards["First"].append("4CE Identify elements of music using developmentally appropriate vocabulary (e.g., rhythm, syllables and solfege).");
    mStandards["First"].append("5CE Explore selected musical instruments aurally and visually.");
    mStandards["First"].append("6CE Attend live music performances with emphasis on concert etiquette.");

    mStandards["First"].append("1PR Demonstrate echo and call/response.");
    mStandards["First"].append("2PR Sing (using head voice and appropriate posture) and move to music of various styles, composers and cultures with accurate pitch and rhythm.");
    mStandards["First"].append("3PR Read, write and perform using eighth notes, quarter notes and quarter rests.");
    mStandards["First"].append("4PR Improvise new lyrics to known songs and experiment with digital technology.");
    mStandards["First"].append("5PR Read, write and perform (e.g., la-sol-mi) melodies on the treble staff in G-do, F-do and C-do using a system (e.g., solfege, numbers or letters).");
    mStandards["First"].append("6PR Play a variety of classroom instruments, alone and with others, and demonstrate proper technique.");
    mStandards["First"].append("7PR Demonstrate audience behavior appropriate for the context and style of music performed.");

    mStandards.insert("Second", {});
    mStandards["Second"].append("1CE Identify patterns of same and different phrases in simple poems and songs.");
    mStandards["Second"].append("2CE Identify rounds and canons.");
    mStandards["Second"].append("3CE Listen to and identify music of various styles, composers, periods andcultures.");
    mStandards["Second"].append("4CE Identify elements of music using developmentally appropriate vocabulary (e.g., rhythm, syllables and solfege).");
    mStandards["Second"].append("5CE Explore selected musical instruments visually and aurally.");
    mStandards["Second"].append("6CE Attend live music performances with emphasis on instrument and voice identification.");

    mStandards["Second"].append("1PR Demonstrate rounds and canons.");
    mStandards["Second"].append("2PR Sing (using head voice and appropriate posture) and move to music of various styles, composers and cultures with accurate pitch and rhythm.");
    mStandards["Second"].append("3PR Read, write and perform using eighth notes, quarter notes, half notes and quarter rests in 2/4 and 4/4 meter.");
    mStandards["Second"].append("4PR Improvise and compose simple rhythmic and melodic phrases.");
    mStandards["Second"].append("5PR Read, write and perform using pentatonic (la-sol-mi-re-do) melodies on the treble staff in G-do, F-do, and C-do using a system (e.g., solfege, numbers or letters).");
    mStandards["Second"].append("6PR Play a variety of classroom instruments, alone and with others, and demonstrate proper technique.");

    mStandards["Second"].append("1RE Explain how music is used for a variety of purposes and occasions.");
    mStandards["Second"].append("2RE Discuss music of various composers, periods, cultures and contrasting styles.");
    mStandards["Second"].append("3RE Discuss how music communicates feelings, moods, images and meaning.");
    mStandards["Second"].append("4RE Interpret music through dance, drama and visual art.");
    mStandards["Second"].append("5RE Respond to patterns of same and different phrases in simple poems and songs.");
    mStandards["Second"].append("6RE Discuss similarities and differences among the arts including connections between music and other curricular subjects.");
    mStandards["Second"].append("7RE Discuss and write about their observations of types of voices and instruments heard in performances");

//    ui->standardDropdown->addItems(mStandards);
//    mCurrentStandard = mStandards[0];
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
    QFile studentsFile("students.txt");
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

    if (ui->studentDropdown->count() <= 1)
    {
        ui->prevStudentBtn->setEnabled(false);
        ui->nextStudentBtn->setEnabled(false);
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
    QString fileName = QFileDialog::getSaveFileName(this, "Export File", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)) + ".txt";

    QFile outFile(fileName);

    outFile.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream outStream(&outFile);

    for (QString student : mStandardsMap.keys())
    {
        outStream << student;
        for (QString standard : mStandardsMap[student].keys())
        {
            outStream << "\n\t" << standard << "\n\t\t" << mStandardsMap[student][standard] << "\n";
        }
    }

    outFile.close();
}

