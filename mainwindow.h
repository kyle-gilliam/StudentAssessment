#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QMap>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringList mStandards;
    QMap<QString, QMap<QString, QString>> mStandardsMap;
    QString mCurrentStudent;
    QString mCurrentStandard;

    void addStandards();
    void setupConnections();
    void loadStudents();

public slots:
    void incrementStandard();
    void decrementStandard();
    void incrementStudent();
    void decrementStudent();
    void setRating(int);
    void setComment();
    void loadData();
    void setNewStandard(QString standard) { mCurrentStandard = standard; loadData(); }
    void setNewStudent(QString student) { mCurrentStudent = student; loadData(); }
    void exportData();
};
#endif // MAINWINDOW_H
