#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

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

void calc_win_probs(const vector<card_type> &deck);

int main()
{
    // categorize the deck based on similarities
    card_type draws(10, 2.3); //cards that let you draw more cards
    draws.avg_draw_amount = 1.2; 
    card_type win_con(5, 4.0); //The cards that the deck is based around
    card_type lands(22); //cards that can give mana
    card_type rest(10, 2.6); //cards that don't really matter for this
    card_type creature(13, 5.07); //creature cards
    const vector<card_type> deck = {draws, win_con, lands, creature, rest};
    calc_win_probs(deck);
    return 0;
}

double simple_prob(double cards, double cards_wanted) //number divided by total
{
    return cards_wanted / cards;
}

int handle_playing(const vector<card_type> &deck, vector<double> &ex_total, vector<double> &ex_in_play) //simulate a turn
{
    double num_draw = 0.0;
    // play a land
    if (ex_total[2] - ex_in_play[2] >= 1)
    {
        ++ex_in_play[2];
    }
    double i = ex_in_play[2];
    while (i > 0)
    {
        if ((ex_total[1] - ex_in_play[1] >= 1) && (deck[1].avg_cost <= i)) //focus playing win conditions
        {
            ++ex_in_play[1];
            i -= deck[1].avg_cost;
        }
        else if ((ex_total[0] - ex_in_play[0] >= 1) && (deck[0].avg_cost <= i)) //then draw more cards
        {
            ++ex_in_play[0];
            i -= deck[0].avg_cost;
            num_draw += deck[0].avg_draw_amount;
        }
        else if ((ex_total[3] - ex_in_play[3] >= 1) && (deck[3].avg_cost <= i)) //then creatures
        {
            ++ex_in_play[3];
            i -= deck[3].avg_cost;
        }
        else if ((ex_total[4] - ex_in_play[4] >= 1) && (deck[4].avg_cost <= i)) //then spells
        {
            ++ex_in_play[4];
            i -= deck[4].avg_cost;
        }
        else
        {
            return (int)num_draw;
        }
    }
    return (int)num_draw;
}

void draw(int draw, double num, const vector<card_type> &deck, vector<double> &ex_total, vector<double> &ex_in_play)
{
    for (int j = 0; j <= draw; ++j)
    {
        for (int i = 0; i <= deck.size(); ++i)
        {
            ex_total[i] += (ex_total[i]+1) * simple_prob(num - j, deck[i].number - ex_total[i]); //calculate the expected value of each card type in the hand and on the field
        }
    }
}

void calc_win_probs(const vector<card_type> &deck)
{
    double deck_size = deck[0].number + deck[1].number + deck[2].number + deck[3].number + deck[4].number;
    vector<double> ex_in_play = {0.0, 0.0, 0.0, 0.0, 0.0};
    vector<double> ex_total = {0.0, 0.0, 0.0, 0.0, 0.0};
    cout << "Enter how many turns you would like to go to:" << endl;
    int counter1 = 7;
    cin >> counter1;
    int draws = 6;

    cout << "\n\n\n\n\n\n\n\n\n\n\n" << endl;
    cout << "Probability of having a win condition in the hand by the end of turn:" << endl;
    for (int keeper = 0; keeper < counter1; ++keeper)
    {
        ++draws;
        draw(draws, deck_size, deck, ex_total, ex_in_play);
        deck_size = deck_size - draws;
        draws = handle_playing(deck, ex_total, ex_in_play);

        cout << "    " << keeper+1 << ": ";
        cout <<  ex_total[1]/5 *100;
        cout << "%" << endl;
    }
}