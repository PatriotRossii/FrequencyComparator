#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableWidget>
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

    QVector<QChar> getSortedKeys(const QMap<QChar, int>& map) const;
    QVector<QChar> getKeysIntersection(const QMap<QChar, int>& first, const QMap<QChar, int>& second) const;

    void calculateFrequency(const QString& text, QMap<QChar, int>& map) const;

    void displayTable(const QMap<QChar, int>& frequency, QTableWidget* table, std::initializer_list<QString> tables) const;
    void displayResult() const;
private slots:
    void recalculateFrequency();
};
#endif // MAINWINDOW_H
