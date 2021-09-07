#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QChar>
#include <QMap>

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

    QMap<QChar, int> first_frequency;
    QMap<QChar, int> second_frequency;

    void setupSignals() const;

    void calculateFrequency(const QString& text, QMap<QChar, int>& map) const;
    void displayResult() const;
private slots:
    void recalculateFrequency();
};
#endif // MAINWINDOW_H
