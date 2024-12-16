#include <string>

class Napoje
{
    public:
    Napoje(int ilosc, double price, std::string brand): ilosc_{ilosc}, cena_{price}, nazwa_{brand} {}
    Napoje():ilosc_{0}, cena_{0},nazwa_{"BRAK"} {}

    void wydajNapoj()
    {
        ilosc_--;
    }
    double getCena()
    {
        return cena_;
    }
    std::string getNazwa()
    {
        return nazwa_;
    }
    int getIlosc()
    {
        return ilosc_;
    }

    private:
    int ilosc_;
    double cena_;
    std::string nazwa_;
};
