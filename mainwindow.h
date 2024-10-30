#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCheckBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTimer>
#include <QVBoxLayout>

#include "sportasacensibas.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  bool check_date_format(QString date);
  bool check_dalibnieku_skaits(int skaits);
  void notify_warning(QString message);
  void notify_info(QString message);

 private slots:
  // Slots
  void on_submitValuesButton_clicked();

  void on_sacensibuWidget_itemDoubleClicked(QTableWidgetItem *item);

  void on_datumsEdit_textChanged();

  void validateKomandasDalibniekuSkaituAfterDelay();

  void validateDateAfterDelay();

  void validateDalibniekuSkaituAfterDelay();

  void on_dalibniekuSkaitsEdit_selectionChanged();

  void on_datumsEdit_selectionChanged();

  void on_komandasSacensibasCheckBox_stateChanged(int arg1);

  void on_komandasDalibniekuEdit_textChanged();

  void on_komandasDalibniekuEdit_selectionChanged();

  void on_dalibniekuSkaitsEdit_textChanged();

 private:
  Ui::MainWindow *ui;
  QTimer *m_dalibniekuTypingTimer;
  QTimer *m_dateTypingTimer;
  QTimer *m_komandasTypingTimer;

  sportaSacensibas *sportaSacensiba[10];

  int counter;
};
#endif  // MAINWINDOW_H
