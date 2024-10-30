#ifndef KOMANDASSACENSIBAS_H
#define KOMANDASSACENSIBAS_H

#include "sportasacensibas.h"

class komandasSacensibas : public sportaSacensibas {
 private:
  int komandasDalibniekuSkaits;

 public:
  komandasSacensibas();
  komandasSacensibas(string nosaukums, string vieta, string datums,
                     int dalibniekuSkaits);
  komandasSacensibas(int komandasDalibniekuSkaits, string nosaukums,
                     string vieta, string datums, int dalibniekuSkaits);

  ~komandasSacensibas();

          // Setters
  // Sets if team won or not
  void setKomandasDalibniekuSkaits(int komandasDalibniekuSkaits);

  // Getters
  double getKomandasDalibniekuSkaits() const;

  // Methods

  // Calculates cost per every competition participant by total cost
  double calcCostPerParticipant(double totalCost) const;

  // Calculates cost per every competition participant by total cost and tax
  // rate
  double calcCostPerParticipant(double totalCost, double taxRate) const;
};

#endif  // KOMANDASSACENSIBAS_H
