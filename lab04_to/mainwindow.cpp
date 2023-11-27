#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    populateCountries();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto layout = new QVBoxLayout(centralWidget);

    listWidget = new QListWidget(this);
    label = new QLabel("Seleccione un país", this);

    layout->addWidget(listWidget);
    layout->addWidget(label);

    connect(listWidget, &QListWidget::itemClicked, this, &MainWindow::onCountrySelected);
}

void MainWindow::populateCountries() {
    // Aquí puedes agregar los países
    listWidget->addItem("España");
    listWidget->addItem("Francia");
    // ... y así sucesivamente
}

void MainWindow::onCountrySelected() {
    auto item = listWidget->currentItem();

    if (item) {
        QString country = item->text();
        QString info;

        // Aquí defines la información por país
        if (country == "España") {
            info = "Idioma: Español, Capital: Madrid";
        } else if (country == "Francia") {
            info = "Idioma: Francés, Capital: París";
        } // ... más condiciones para otros países

        label->setText(info);
    }
}
