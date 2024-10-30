#ifndef SPORTASACENSIBAS_H
#define SPORTASACENSIBAS_H
#pragma once
#include <string>

using namespace std;

class sportaSacensibas {
private:
    string nosaukums;
    string vieta;
    string datums;
    int dalibniekuSkaits;
    static int sacensibuSkaits;

public:
    // Constructors
    // Initialize sportaSacensibas object with default attributes
    sportaSacensibas();
    // Initialize sportaSacensibas object with user defined attributes
    sportaSacensibas(string nosaukums, string vieta, string datums, int dalibniekuSkaits);
    // Unloads object from memory, decreasing the amount of sportaSacensibas
    // objects initialized
    ~sportaSacensibas();

    // Setters
    // Gets event name and sets private nosaukums attribute
    void setNosaukums(string nosaukums);
    // Gets place string and sets it to private attribute vieta
    void setVieta(string vieta);
    // Gets date as string and sets it to private attribute datums
    void setDatums(string datums);
    // Gets participant number as int and sets it to dalibnieku skaits attribute
    void setDalibiekuSkaits(int skaits);

    // Getters
    // Returns nosaukums attribute
    string getNosaukums() const;
    // Returns vieta attribute
    string getVieta() const;
    // Returns datums attribute
    string getDatums() const;
    // Returns dalibnieku skaits attribute
    int getDalibiekuSkaits() const;

    // Returns number of class instances
    static int getSacensibuSkaits();

    // Methods
    // Calculates cost per every competition participant by total cost
    virtual double calcCostPerParticipant(double totalCost) const;
    // Calculates cost per every competition participant by total cost and tax
    // rate
    virtual double calcCostPerParticipant(double totalCost, double taxRate) const;
};

#endif // SPORTASACENSIBAS_H
