#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSignals() const {
    QObject::connect(
        this->ui->first_edit, &QPlainTextEdit::textChanged,
        this, &MainWindow::recalculateFrequency
    );
    QObject::connect(
        this->ui->second_edit, &QPlainTextEdit::textChanged,
        this, &MainWindow::recalculateFrequency
    );
}

void MainWindow::calculateFrequency(const QString& text, QMap<QChar, int>& map) const {
    map.clear();
    for(QChar x: text) {
        map[x] += 1;
    }
}

QVector<QChar> MainWindow::getSortedKeys(const QMap<QChar, int>& map) const {
    QSet<QChar> keys(map.keyBegin(), map.keyEnd());

    QVector<QChar> result(keys.begin(), keys.end());
    std::sort(result.begin(), result.end());

    return result;
}

QVector<QChar> MainWindow::getKeysIntersection(const QMap<QChar, int>& first, const QMap<QChar, int>& second) const {
    QSet<QChar> keys(first.keyBegin(), first.keyEnd());
    keys.unite(QSet(second.keyBegin(), second.keyEnd()));
    return QVector<QChar>(keys.begin(), keys.end());
}

void MainWindow::recalculateFrequency() {
    this->calculateFrequency(this->ui->first_edit->toPlainText(), this->first_frequency);
    this->calculateFrequency(this->ui->second_edit->toPlainText(), this->second_frequency);
    this->displayResult();
}

void MainWindow::displayTable(const QMap<QChar, int>& frequency, QTableWidget* table, std::initializer_list<QString> headers) const {
    const QVector<QChar> sortedKeys = getSortedKeys(frequency);

    table->clear();

    table->setRowCount(sortedKeys.size());
    table->setColumnCount(2);

    table->setHorizontalHeaderLabels(
        headers
    );

    int idx = 0;
    for(auto key: sortedKeys) {
        QTableWidgetItem* key_widget = new QTableWidgetItem(QString(key));
        QTableWidgetItem* value_widget = new QTableWidgetItem(QString::number(frequency[key]));

        table->setItem(idx, 0, key_widget);
        table->setItem(idx, 1, value_widget);

        idx += 1;
    }
}

void MainWindow::displayResult() const {
    const QMap<QChar, int> frequencyUnion = [this]() -> QMap<QChar, int> {
        QMap<QChar, int> result;

        for(auto it = this->first_frequency.begin(), end = this->first_frequency.end(); it != end; ++it) {
            result[it.key()] += it.value();
        }
        for(auto it = this->second_frequency.begin(), end = this->second_frequency.end(); it != end; ++it) {
            result[it.key()] = abs(result[it.key()] - it.value());
        }

        return result;
    }();

    // First table display

    this->displayTable(this->first_frequency, this->ui->first_tbl, {"Символ", "n"});

    // Second table display

    this->displayTable(this->second_frequency, this->ui->second_tbl, {"Символ", "n"});

    // Delta table display

    this->displayTable(frequencyUnion, this->ui->delta_tbl, {"Символ", "Δn"});

}
