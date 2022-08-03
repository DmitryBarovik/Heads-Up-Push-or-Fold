#include "strategy.h"
#include <utility>

Strategy::Strategy(double value)
{
  for (int i = 0; i < 13; i++)
  {
    for (int j = 0; j < 13; j++)
    {
      strategy[i][j] = value;
    }
  }
}


double Strategy::get_strategy(int card1, int card2, bool is_index_rep)
{
  if (is_index_rep)
  {
    return strategy[card1][card2];
  }
  else
  {
    std::pair<int,int> index = get_index(card1, card2);
    return strategy[index.first][index.second];
  }
}


std::pair<int, int> Strategy::get_index(int card1, int card2)
{
    int v1 = (card1 - 1) / 4;
    int v2 = (card2 - 1) / 4;
    if (v1 == v2) //check if pocket pair first
        return std::make_pair(v1, v2);
    else
    {
        int s1 = (card1 - 1) % 4;
        int s2 = (card2 - 1) % 4;
        if (s1 == s2)
            return std::make_pair(std::max(v1, v2), std::min(v1,v2));
        else
            return std::make_pair(std::min(v1,v2), std::max(v1,v2));
    }
}


void Strategy::set_strategy(int card1, int card2, double value,
    bool is_index_rep)
{
  if (is_index_rep)
  {
    strategy[card1][card2] = value;
  }
  else
  {
    std::pair<int,int> index = get_index(card1, card2);
    strategy[index.first][index.second] = value;
  }
}
