#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <chrono>
#include "Napoje.hpp"
#include "Monety.hpp"
#include <OpenXLSX.hpp>
using namespace OpenXLSX;

class Automat
{
    public:
    Automat()
    {
        std::string initNazwa;
        double initCena;
        int initIlosc;
        //Przypisywanie napojów do slotu, ilość + cena + nazwa
        for(int i=0;i<nSlots;i++)
        {
            std::cout<<"Podaj nazwe napoju\n";
            std::cin>>initNazwa;
            
            std::cout<<"Podaj cene napoju\n";
            std::cin>>initCena;
            
            std::cout<<"Podaj ilosc napoju\n";
            std::cin>>initIlosc;

            maszyna_.emplace_back(Napoje{initIlosc,initCena,initNazwa});
        }

        auto srtFnc = [](Napoje a, Napoje b){return a.getCena()<b.getCena();};
        std::sort(maszyna_.begin(), maszyna_.end(), srtFnc);   

        doc_.create("Transakcje.xlsx");
        wks_ = doc_.workbook().worksheet("Sheet1");

        wks_.cell(1,1).value() = "Data";
        wks_.cell(1,2).value() = "Godzina";
        wks_.cell(1,3).value() = "Produkt";
        wks_.cell(1,4).value() = "Cena";
        wks_.cell(1,5).value() = "Kredyt";
        doc_.save();     
    }

    void printAutomat()
    {   
        //wypisywanie zawartosci automatu
        std::cout<<"#############################################\n";

        for(int i=0;i<nSlots;i++)
        {
            std::cout<<"Slot "<<i<<".\t";
            //Dodać if czy slot nie jest pusty!!!
            std::cout<<maszyna_[i].getNazwa();
            if(maszyna_[i].getIlosc()==0)
                std::cout<<"\tBRAK PRODUKTU\n";
            else
                std::cout<<"\tIlosc = "<<maszyna_[i].getIlosc()<<"\tCena: "<<maszyna_[i].getCena()<<" PLN\n";
        }

        std::cout<<"#############################################\n";
    }

    void getDrink(int slotNumber)
    {
        //akcja wydawania napojów
        if (slotNumber>nSlots || maszyna_[slotNumber].getIlosc() == 0)
        {
            std::cout<<"Podaj wlasciwy numer napoju\n";
        }
        else
        {
            double kredyt=0.0;
            double reszta = 0.0;
            std::string wrzuconaMoneta;
            std::cout<<"Wybrano napoj "<<maszyna_[slotNumber].getNazwa()<<"\n";
            while(kredyt<maszyna_[slotNumber].getCena())
            {
                std::cout<<"Wrzuc monete\n";
                std::cin>>wrzuconaMoneta;

                if(m.monety_.contains(wrzuconaMoneta))
                {
                    kredyt+=m.monety_[wrzuconaMoneta];
                }
                else
                {
                    std::cout<<"Wrzuc poprawna monete\n";
                }
            }

            maszyna_[slotNumber].wydajNapoj();
            reszta = kredyt-maszyna_[slotNumber].getCena();
            std::cout<<"Produkt wydany, reszta = "<<reszta<<"\n";

            wydajReszte(reszta);

            //Funkcja zapisujaca transakcje do arkusza xlsx!!!
            //std::asctime(&tm_);
            t_ = std::time(0);
            tm_ = std::localtime(&t_);
            XLDateTime dt(*tm_);
            

            wks_.cell(nCellRow,1).value() = dt;
            wks_.cell(nCellRow,1).setCellFormat(1);
            wks_.cell(nCellRow,2).value() = dt;
            wks_.cell(nCellRow,2).setCellFormat(1);

            wks_.cell(nCellRow,3).value() = maszyna_[slotNumber].getNazwa();
            wks_.cell(nCellRow,4).value() = maszyna_[slotNumber].getCena();
            wks_.cell(nCellRow,5).value() = kredyt;
            doc_.save();
            nCellRow++;
        }
    }

    void wydajReszte(double reszta)
    {
        std::cout<<"Mam do wydania "<<reszta<<" PLN\n";
        int iReszta = static_cast<int>(reszta*100);
        int k = 8;
        while(iReszta>0)
        {   
            int n = static_cast<int>(m.getVal(k)*100);
            if(n<=iReszta)
            {   
                std::cout<<"Wydaje reszte, "<<m.getVal(k)<<" PLN\n";
                iReszta-=n;
            }
            else
            {
                k--;
            }
        }
        std::cout<<"Cala reszta wydana\n";
    }

    private:
    static const int nSlots = 2;
    std::vector<Napoje> maszyna_;
    int nCellRow = 2;
    std::time_t t_;
    std::tm* tm_;
    XLDocument doc_;
    XLWorksheet wks_;
    
    Monety m{};
};