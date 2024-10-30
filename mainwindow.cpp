#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "komandassacensibas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  for (int i = 0; i < 10; ++i) {
    sportaSacensiba[i] = nullptr;
  }
  counter = 0;
  // Initialize the typing timer for delaying validation
  m_dalibniekuTypingTimer = new QTimer(this);

  m_dalibniekuTypingTimer->setSingleShot(true);

  m_komandasTypingTimer = new QTimer(this);

  m_komandasTypingTimer->setSingleShot(true);

  m_dateTypingTimer = new QTimer(this);

  m_dateTypingTimer->setSingleShot(
      true); // Ensure the timer fires only once after being started

  // Connect the timer's timeout signal to the validation slot
  connect(m_dateTypingTimer, &QTimer::timeout, this,
          &MainWindow::validateDateAfterDelay);

  connect(m_dalibniekuTypingTimer, &QTimer::timeout, this,
          &MainWindow::validateDalibniekuSkaituAfterDelay);

  connect(m_komandasTypingTimer, &QTimer::timeout, this,
          &MainWindow::validateKomandasDalibniekuSkaituAfterDelay);

  setTabOrder(ui->nosaukumsEdit, ui->vietaEdit);
  setTabOrder(ui->vietaEdit, ui->datumsEdit);
  setTabOrder(ui->datumsEdit, ui->dalibniekuSkaitsEdit);

  QRegularExpression regex(
      "^([0-2][0-9]|(3)[0-1])\\.(0[1-9]|1[0-2])\\.([0-9]{4})$");

  QRegularExpressionValidator *dateValidator = new QRegularExpressionValidator(regex, this);

  QIntValidator *intValidator = new QIntValidator(1, 2147483647, this);
  ui->dalibniekuSkaitsEdit->setValidator(intValidator);
  ui->komandasDalibniekuEdit->setValidator(intValidator);
  ui->datumsEdit->setValidator(dateValidator);
}

MainWindow::~MainWindow() {
  for (int i = 0; i < 10; i++) {
    delete sportaSacensiba[i];
  }
  delete ui;
}
void MainWindow::on_submitValuesButton_clicked() {
  try {
    // Get input from user
    QString datums = ui->datumsEdit->text();
    QString nosaukums = ui->nosaukumsEdit->toPlainText();
    QString vieta = ui->vietaEdit->toPlainText();
    int dalibniekuSkaits = ui->dalibniekuSkaitsEdit->text().toInt();
    double komandasDalibniekuSkaits =
        ui->komandasDalibniekuEdit->text().toInt();

    // Checks for inputs
    if (ui->datumsEdit->text().isEmpty()) {
      notify_warning("Datums nevar but tukss!");
      return;
    }
    if (!check_date_format(datums)) {
      notify_warning(
          "Datuma formats nepareizs. Ludzu ievadiet datumu formata:  "
          "dd.mm.yyyy "
          "0 < Diena <= 31 0 < Menesis <= 12");
    }

    if (ui->komandasSacensibasCheckBox->isChecked()) {
      if (ui->komandasDalibniekuEdit) {
        notify_warning("Komandas dalibniekus vajag pievienot!");
        return;
      }
      if (komandasDalibniekuSkaits <= 0) {
        notify_warning("Komandu skaits vajazetu but vairak par 0");
        return;
      }
    }

    if (ui->nosaukumsEdit->toPlainText().isEmpty()) {
      notify_warning("Nosaukums nevar but tukss!");
      return;
    }
    if (!check_dalibnieku_skaits(dalibniekuSkaits)) {
      notify_warning("Dalibnieku skaits vajag but vairak par 0");
      return;
    }
    if (ui->vietaEdit->toPlainText().isEmpty()) {
      notify_warning("Vieta nevar but tuksa!");
      return;
    }
    if (ui->dalibniekuSkaitsEdit->text().isEmpty()) {
      notify_warning("Dalibniekus vajag pievienot!");
      return;
    }
    // Check for array out of bounds
    if (counter >= 10) {
      notify_warning("Nevaru pievienot vairak par 10 sacensibam!");
      return;
    }
    // Create object on current pointer and show a success window
    if (ui->komandasSacensibasCheckBox->isChecked()) {
      sportaSacensiba[counter] = new komandasSacensibas(
          komandasDalibniekuSkaits, nosaukums.toStdString(),
          vieta.toStdString(), datums.toStdString(), dalibniekuSkaits);
    } else {
      sportaSacensiba[counter] =
          new sportaSacensibas(nosaukums.toStdString(), vieta.toStdString(),
                               datums.toStdString(), dalibniekuSkaits);
    }

    notify_info("Dati ir veiksmigi ierakstiti!");
    // Set data from object to a table
    ui->sacensibuWidget->setItem(
        counter, 0,
        new QTableWidgetItem(
            QString::fromStdString(sportaSacensiba[counter]->getNosaukums())));

    ui->sacensibuWidget->setItem(counter, 1,
                                 new QTableWidgetItem(QString::fromStdString(
                                     sportaSacensiba[counter]->getDatums())));

    ui->sacensibuWidget->setItem(counter, 2,
                                 new QTableWidgetItem(QString::fromStdString(
                                     sportaSacensiba[counter]->getVieta())));

    ui->sacensibuWidget->setItem(
        counter, 3,
        new QTableWidgetItem(
            QString::number(sportaSacensiba[counter]->getDalibiekuSkaits())));

    if (ui->komandasSacensibasCheckBox->isChecked()) {
      komandasSacensibas *komanda =
          static_cast<komandasSacensibas *>(sportaSacensiba[counter]);
      ui->sacensibuWidget->setItem(
          counter, 4,
          new QTableWidgetItem(
              QString::number(komanda->getKomandasDalibniekuSkaits())));
    }

    // After succesful inserting clear input fields
    ui->datumsEdit->clear();
    ui->nosaukumsEdit->clear();
    ui->dalibniekuSkaitsEdit->clear();
    ui->vietaEdit->clear();
    ui->komandasDalibniekuEdit->clear();
    // Increase counter of objects
    counter++;

  } catch (const std::exception &e) {
    QMessageBox::critical(this, "Critical error",
                          QString("An error occurred: %1").arg(e.what()),
                          QMessageBox::Ok);
  }
}
// On table item doubleclick create a dialog with methods
void MainWindow::on_sacensibuWidget_itemDoubleClicked(QTableWidgetItem *item) {
  QDialog dialog(this);
  dialog.setWindowTitle("Izmaksas");
  QDoubleValidator *totalCostValidator = new QDoubleValidator(0.1, INT_MAX, 2, this);
  QIntValidator *taxValidator = new QIntValidator(1, 100, this);

  // Pass a pointer to QVBoxLayout and initialize it
  QVBoxLayout *layout = new QVBoxLayout(&dialog);
  QLabel *welcomeLabel = new QLabel(&dialog);
  welcomeLabel->setText("Aprekinat izmaksas uz vienu dalibnieku");
  layout->addWidget(welcomeLabel);
  // Initialize a checkbox to use an overrided method
  QCheckBox *taxCheck = new QCheckBox(&dialog);
  taxCheck->setText("Aprekinat ar nodokliem");
  layout->addWidget(taxCheck);

  QLabel *totalCostLabel = new QLabel(&dialog);
  totalCostLabel->setText("Ievadiet kopejas izmaksas:");
  layout->addWidget(totalCostLabel);
  QLineEdit *totalCostInput = new QLineEdit(&dialog);
  totalCostInput->setPlaceholderText("Kopejas izmaksas");
  totalCostInput->setValidator(totalCostValidator);
  layout->addWidget(totalCostInput);

  // Initialize a readonly field for tax
  QLabel *taxLabel = new QLabel(&dialog);
  taxLabel->setText("Ievadiet nodoklu likmi:");
  layout->addWidget(taxLabel);
  QLineEdit *taxInput = new QLineEdit(&dialog);
  taxInput->setPlaceholderText("Nodokļu vērtība");
  taxInput->setValidator(taxValidator);
  taxInput->setReadOnly(true);
  layout->addWidget(taxInput);

  QPushButton *calculateButton = new QPushButton("Aprekinat", &dialog);
  layout->addWidget(calculateButton);

  QPushButton *cancelButton = new QPushButton("Aizvert", &dialog);
  layout->addWidget(cancelButton);

  // Check for taxCheck state and enable taxInput field when checked
  connect(taxCheck, &QCheckBox::checkStateChanged, &dialog, [=](int state) {
    if (state == Qt::Checked) {
      taxInput->setReadOnly(false);
    } else {
      taxInput->setReadOnly(true);
      taxInput->setText("");
    }
  });

  // Handle cancel button
  connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::accept);

  // Handle button press and calculate value using lambda function
  connect(calculateButton, &QPushButton::clicked, this, [=]() {
    double taxValue = taxInput->text().toDouble();
    double totalCostValue = totalCostInput->text().toDouble();
    double result = 0;
    if (totalCostValue > 0) {
      if (taxCheck->isChecked()) {
        if (taxValue < 100 && taxValue >= 1) {
          result = sportaSacensiba[item->row()]->calcCostPerParticipant(
              totalCostValue, taxValue);
        } else {
          notify_warning("Nodokļu vērtība jābūt diapazonā no 1 līdz 100");
          return;
        }
      } else {
        result = sportaSacensiba[item->row()]->calcCostPerParticipant(
            totalCostValue);
      }
    } else {
      notify_warning("Kopejas izmaksas vajadzetu but vairak par 0");
      return;
    }

    notify_info("Izmaksas uz vienu dalībnieku: " + QString::number(result));
  });
  // Show dialog window to user
  dialog.exec();
}

void MainWindow::on_komandasSacensibasCheckBox_stateChanged(int arg1) {
  if (arg1 == 2) {
    ui->dalibniekuLabel->setText("Komandu skaits");
    ui->komandasDalibniekuEdit->setReadOnly(false);
    setTabOrder(ui->dalibniekuSkaitsEdit, ui->komandasDalibniekuEdit);
    return;
  } else {
    ui->dalibniekuLabel->setText("Dalibnieku skaits");
    ui->komandasDalibniekuEdit->setReadOnly(true);
    return;
  }
}
// Private Methods
void MainWindow::validateDateAfterDelay() {
  QString text = ui->datumsEdit->text();

  if (!check_date_format(text)) {
    notify_warning(
        "Datuma formats nepareizs. Ludzu ievadiet datumu formata:  dd.mm.yyyy "
        "0 < Diena <= 31 0 < Menesis <= 12");
  }
}

void MainWindow::validateDalibniekuSkaituAfterDelay() {
  if (!check_dalibnieku_skaits(ui->dalibniekuSkaitsEdit->text().toInt()) &&
      !ui->dalibniekuSkaitsEdit->text().isEmpty()) {
    notify_warning("Dalibnieku skaits vajag but lielaks par 0");
    return;
  }
}

void MainWindow::validateKomandasDalibniekuSkaituAfterDelay() {
  if (!check_dalibnieku_skaits(ui->komandasDalibniekuEdit->text().toInt()) &&
      !ui->komandasDalibniekuEdit->text().isEmpty()) {
    notify_warning("Komandas Dalibnieku skaits vajag but lielaks par 0");
    return;
  }
}
bool MainWindow::check_dalibnieku_skaits(int skaits) {
  if (skaits <= 0) {
    return false;
  } else {
    return true;
  }
}
bool MainWindow::check_date_format(QString date) {
  // Regular expression to validate the dd.mm.yyyy format
  QRegularExpression regex(
      "^([0-2][0-9]|(3)[0-1])\\.(0[1-9]|1[0-2])\\.([0-9]{4})$");

  if (!regex.match(date).hasMatch() && !date.isEmpty()) {
    return false;
  } else {
    return true;
  }
}
void MainWindow::notify_info(QString message) {
  QMessageBox::information(this, "Info", message);
}

void MainWindow::notify_warning(QString message) {
  QMessageBox::warning(this, "Warning", message);
}
// Timers on edit

// Dalibnieku edit timer
void MainWindow::on_dalibniekuSkaitsEdit_textChanged() {
  // Each time the text is changed, restart the timer
  m_dalibniekuTypingTimer->start(1000); // Start the timer with a 1000ms delay
}

void MainWindow::on_dalibniekuSkaitsEdit_selectionChanged() {
  if (ui->dalibniekuSkaitsEdit->isEnabled()) {
    return;
  } else {
    validateDalibniekuSkaituAfterDelay();
  }
}

// Datums edit timer
void MainWindow::on_datumsEdit_textChanged() {
  // Each time the text is changed, restart the timer
  m_dateTypingTimer->start(1000); // Start the timer with a 1000ms delay
}

void MainWindow::on_datumsEdit_selectionChanged() {
  if (ui->datumsEdit->isEnabled()) {
    return;
  } else {
    validateDateAfterDelay();
  }
}

// Komandas dalibnieku edit timer
void MainWindow::on_komandasDalibniekuEdit_textChanged() {
  m_komandasTypingTimer->start(1000);
}

void MainWindow::on_komandasDalibniekuEdit_selectionChanged() {
  if (ui->komandasDalibniekuEdit->isEnabled()) {
    return;
  } else {
    validateKomandasDalibniekuSkaituAfterDelay();
  }
}
