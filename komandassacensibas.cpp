#include "komandassacensibas.h"

#include <QDebug>
#include <QMessageBox>


komandasSacensibas::komandasSacensibas() {
  this->setDalibiekuSkaits(0);
  this->setDatums("Nav zinams");
  this->setNosaukums("Sports");
  this->setVieta("Nav zinams");
}
komandasSacensibas::komandasSacensibas(string nosaukums, string vieta,
                                       string datums, int dalibniekuSkaits) {
  this->setDalibiekuSkaits(dalibniekuSkaits);
  this->setDatums(datums);
  this->setVieta(vieta);
  this->setNosaukums(nosaukums);
};

komandasSacensibas::komandasSacensibas(int komandasDalibniekuSkaits,
                                       string nosaukums, string vieta,
                                       string datums, int dalibniekuSkaits) {
  this->komandasDalibniekuSkaits = komandasDalibniekuSkaits;
  this->setDalibiekuSkaits(dalibniekuSkaits);
  this->setNosaukums(nosaukums);
  this->setDatums(datums);
  this->setVieta(vieta);
}

void komandasSacensibas::setKomandasDalibniekuSkaits(
    int komandasDalibniekuSkaits) {
  this->komandasDalibniekuSkaits = komandasDalibniekuSkaits;
}

double komandasSacensibas::getKomandasDalibniekuSkaits() const {
  return this->komandasDalibniekuSkaits;
}

double komandasSacensibas::calcCostPerParticipant(double totalCost) const {
  int totalDalibnieki = getDalibiekuSkaits() * komandasDalibniekuSkaits;
  return totalCost / totalDalibnieki;
}

double komandasSacensibas::calcCostPerParticipant(double totalCost,
                                                  double taxRate) const {
  taxRate = taxRate / 100;
  double totalWithTax = totalCost + (totalCost * taxRate);
  int totalDalibnieki = getDalibiekuSkaits() * komandasDalibniekuSkaits;
  if (totalDalibnieki == 0) return 0.0;
  return totalWithTax / totalDalibnieki;
}
