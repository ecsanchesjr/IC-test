#include "Customer.hpp"

Customer::Customer() {}

Customer::Customer(int id, double x, double y, double demand, bool depot) : id(id), x(x), y(y), demand(demand), depot(depot) {}

void Customer::setId(int id) { this->id = id; }
void Customer::setX(double x) { this->x = x; }
void Customer::setY(double y) { this->y = y; }
void Customer::setDemand(double demand) { this->demand = demand; }
void Customer::setDepot(bool depot) { this->depot = depot; }

int Customer::getId() const { return (id); }
double Customer::getX() const { return (x); }
double Customer::getY() const { return (y); }
double Customer::getDemand() const { return (demand); }
bool Customer::getDepot() const { return (depot); }

ostream &operator<<(ostream &out, const Customer &c)
{
    if (!c.getDepot())
    {
        out << setfill(' ') << "ID: " << setw(2) << c.getId() << " Demand: " << setw(3) << c.getDemand() << " | "
            << "X: " << setw(5) << c.getX() << " Y: " << setw(5) << c.getY();
    }else{
        out << setfill(' ') << "ID: " << setw(2) << c.getId() << " Demand: " << setw(3) << c.getDemand() << " | "
            << "X: " << setw(5) << c.getX() << " Y: " << setw(5) << c.getY() <<" DEPOT";
    }
    return (out);
}

bool Customer::operator==(const Customer &c) const { return (this->getId() == c.getId()); }
