#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCountrySelected();

private:
    QListWidget *listWidget;
    QLabel *label;
    void setupUI();
    void populateCountries();
};

#endif // MAINWINDOW_H
