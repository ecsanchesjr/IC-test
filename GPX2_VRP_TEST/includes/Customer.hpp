#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <iomanip>

using std::ostream;
using std::setfill;
using std::setw;

class Customer{

	friend ostream& operator<<(ostream&, const Customer&);

public:
	Customer();
	Customer(int id, double x, double y, double demand, bool depot = 0);

	void setId(int);
	void setX(double);
	void setY(double);
	void setDemand(double);
	void setDepot(bool);

	int getId() const;
	double getX() const;
	double getY() const;
	double getDemand() const; 
	bool getDepot() const;

	bool operator==(const Customer&) const;

private:
	int id;
	double x;
	double y;
	double demand;
	bool depot;
};

#endif
