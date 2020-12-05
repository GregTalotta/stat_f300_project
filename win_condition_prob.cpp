#include <vector>
using std::vector;

void calc_win_probs(const card_type &draws, const card_type &win_con, const card_type &lands, const card_type &creature, const card_type &rest);

struct card_type
{
    card_type();
    card_type(double num)
    {
        number = num;
        is_land = true;
    }
    card_type(double num, double cost)
    {
        number = num;
        avg_cost = cost;
    }
    double number = 0;
    double avg_cost = 0;
    double avg_draw_amount = 0.0;
    bool is_land = false;
};

struct ex_vals
{
    double draws_gone = 0.0;
    double lands_gone = 0.0;
    double win_con_gone = 0.0;
    double lands_gone = 0.0;
    double creature_gone = 0.0;
    double rest_gone = 0.0;
};

int main()
{
    card_type draws(10, 2.3);
    draws.avg_draw_amount = 1.2;
    card_type win_con(5, 4.0);
    card_type lands(22);
    card_type rest(10, 2.6);
    card_type creature(13, 5.07);
    calc_win_probs(draws, win_con, lands, creature, rest);
    return 0;
}

void calc_win_probs(const card_type &draws, const card_type &win_con, const card_type &lands, const card_type &creature, const card_type &rest)
{
    double deck_size = draws.number + win_con.number + lands.number + creature.number + rest.number;
    double draws_gone = 0.0;
    double lands_gone = 0.0;
    double win_con_gone = 0.0;
    double lands_gone = 0.0;
    double creature_gone = 0.0;
    double rest_gone = 0.0;
}