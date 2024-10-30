#include "sportasacensibas.h"
#include <qnamespace.h>

int sportaSacensibas::sacensibuSkaits = 0;

//Constructors
sportaSacensibas::sportaSacensibas() {
    this->nosaukums = "Nezinams";
    this->datums = "Nezinams";
    this->dalibniekuSkaits = 0;
    this->vieta = "Nezinams";
    sacensibuSkaits++;
}

sportaSacensibas::sportaSacensibas(string nosaukums, string vieta, string datums, int dalibniekuSkaits){
    this->nosaukums = nosaukums;
    this->vieta = vieta;
    this->datums = datums;
    this->dalibniekuSkaits = dalibniekuSkaits;
    sacensibuSkaits++;
}

//Destructor
sportaSacensibas::~sportaSacensibas(){
    sacensibuSkaits--;
}

//Setters
void sportaSacensibas::setNosaukums(string nosaukums){
    this->nosaukums = nosaukums;
}

void sportaSacensibas::setDatums(string datums){
    this->datums = datums;
}

void sportaSacensibas::setVieta(string vieta){
    this->vieta = vieta;
}

void sportaSacensibas::setDalibiekuSkaits(int dalibniekuSkaits){
    this->dalibniekuSkaits = dalibniekuSkaits;
}

//Getters
string sportaSacensibas::getNosaukums() const {
    return this->nosaukums;
}

string sportaSacensibas::getDatums() const {
    return this->datums;
}

string sportaSacensibas::getVieta() const {
    return this->vieta;
}

int sportaSacensibas::getDalibiekuSkaits() const {
    return this->dalibniekuSkaits;
}

int sportaSacensibas::getSacensibuSkaits() {
    return sacensibuSkaits;
}

//Methods
double sportaSacensibas::calcCostPerParticipant(double totalCost) const {
    if (dalibniekuSkaits == 0) return 0.0;
    return totalCost / dalibniekuSkaits;
}

double sportaSacensibas::calcCostPerParticipant(double totalCost, double taxRate) const {
    taxRate = taxRate/100;
    double totalWithTax = totalCost + (totalCost * taxRate);
    if (dalibniekuSkaits == 0) return 0.0;
    return totalWithTax / dalibniekuSkaits;
}
