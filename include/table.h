#ifndef TABLE_H
#define TABLE_H
#include "bot.h"
#include "human.h"
#include "box.h"

class Table
{
public:
    Table(); //e aggiungere set per i players
    void turn();

    struct Iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Player;
        using pointer = Player **;
        using reference = Player &;

        Iterator(pointer ptr) : player_ptr{ptr} {};
        ~Iterator() {}
        reference operator*() const { return **player_ptr; };
        pointer operator->() { return player_ptr; };
        Iterator &operator++()
        {
            player_ptr++;
            return *this;
        };
        Iterator &operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        };
        friend bool operator==(const Iterator &a, const Iterator &b) { return a.player_ptr == b.player_ptr; };
        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.player_ptr != b.player_ptr; };
    private:
        pointer player_ptr;
    };

    Iterator begin() { return Iterator(&players_[0]); };
    Iterator end() { return Iterator(&players_[4]); };

    //aggiungere iteratore per le box

private:
    //array di puntatori non di oggetti
    Box map_[28];
    
    Player *players_[4];
};

#endif