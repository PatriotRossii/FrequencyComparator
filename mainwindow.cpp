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


void MainWindow::recalculateFrequency() {
    this->calculateFrequency(this->ui->first_edit->toPlainText(), this->first_frequency);
    this->calculateFrequency(this->ui->second_edit->toPlainText(), this->second_frequency);
    this->displayResult();
}

void MainWindow::displayResult() const {
    const QVector<QChar> sortedKeys = [this]() -> QVector<QChar> {
        QSet<QChar> keys(this->first_frequency.keyBegin(), this->first_frequency.keyEnd());
        keys.unite(QSet(this->second_frequency.keyBegin(), this->second_frequency.keyEnd()));

        QVector<QChar> result(keys.begin(), keys.end());
        std::sort(result.begin(), result.end());

        return result;
    }();

    this->ui->result_tbl->clear();

    this->ui->result_tbl->setRowCount(2);
    this->ui->result_tbl->setColumnCount(sortedKeys.size());

    this->ui->result_tbl->setHorizontalHeaderLabels(
        QStringList(sortedKeys.begin(), sortedKeys.end())
    );

    int idx = 0;
    for(auto key: sortedKeys) {
        QTableWidgetItem* first_item =
            new QTableWidgetItem(QString::number(this->first_frequency.value(key, 0)));
        QTableWidgetItem* second_item =
                new QTableWidgetItem(QString::number(this->second_frequency.value(key, 0)));

        this->ui->result_tbl->setItem(0, idx, first_item);
        this->ui->result_tbl->setItem(1, idx, second_item);

        idx += 1;
    }
}
