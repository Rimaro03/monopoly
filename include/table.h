#ifndef TABLE_H
#define TABLE_H
#include "bot.h"
#include "human.h"
#include "box.h"

class Table
{
public:
    Table();
    ~Table();

    void turn();
    void players(Player *player1, Player *player2, Player *player3, Player *player4);

    Box **box();

    struct PlayerIterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Player;
        using pointer = Player **;
        using reference = Player &;

        PlayerIterator(pointer ptr) : player_ptr{ptr} {};
        ~PlayerIterator() {}
        reference operator*() const { return **player_ptr; };
        pointer operator->() { return player_ptr; };
        PlayerIterator &operator++()
        {
            player_ptr++;
            return *this;
        };
        friend bool operator==(const PlayerIterator &a, const PlayerIterator &b) { return a.player_ptr == b.player_ptr; };
        friend bool operator!=(const PlayerIterator &a, const PlayerIterator &b) { return a.player_ptr != b.player_ptr; };

    private:
        pointer player_ptr;
    };

    PlayerIterator BeginPlayer() { return PlayerIterator(&players_[0]); };
    PlayerIterator EndPlayer() { return PlayerIterator(&players_[4]); };

    struct BoxIterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Box;
        using pointer = Box **;
        using reference = Box &;

        BoxIterator(pointer ptr) : box_ptr{ptr} {};
        ~BoxIterator() {}
        reference operator*() const { return **box_ptr; };
        pointer operator->() { return box_ptr; };
        BoxIterator &operator++()
        {
            box_ptr++;
            return *this;
        };
        friend bool operator==(const BoxIterator &a, const BoxIterator &b) { return a.box_ptr == b.box_ptr; };
        friend bool operator!=(const BoxIterator &a, const BoxIterator &b) { return a.box_ptr != b.box_ptr; };

        private:
            pointer box_ptr;
    };

    BoxIterator BeginBox() { return BoxIterator(&map_[0]); };
    BoxIterator EndBox() { return BoxIterator(&map_[28]); };

private:
    Box *map_[28];
    Player *players_[4];
};

#endif