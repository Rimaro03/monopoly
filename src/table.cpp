#include <iostream>
#include <algorithm>
#include <random>
#include "table.h"
#include "sideBox.h"
#include "lateralBox.h"

Table::Table(Player* players): players_{players}
{
    int ecoCount = 8;
    int standardCount = 10;
    int luxCount = 6;
    
    //generazione indici
    int indici[24];
    int i = 0;
    while (i < 28)
    {
        if(i % 7 != 0){
            indici[i] = i;
        }
        i++;
    }
    
    //randomizzazione indici con shuffle()
    std::shuffle(indici, indici + 24, std::default_random_engine(time(NULL)));
    int count = 0;
    for (unsigned int i = 0; i < 28; i++)
    {
        Box casella;
        if(i % 7 == 0){
            casella = SideBox(i, (i == 0));
        }
        else{
            if(count < 8){
                casella = LateralBox(i, BoxType::economic, 6, 3, 3, 2, 4);
            }
            else{
                if(count < 10){
                    casella = LateralBox(i, BoxType::standard, 10, 5, 5, 4, 8);
                }
                else{
                    casella = LateralBox(i, BoxType::luxury, 20, 10, 10, 7, 14);
                }
            }
        }
        map_[indici[i]] = casella;
    }
    
}