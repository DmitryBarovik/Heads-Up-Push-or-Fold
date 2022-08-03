/* 
 * C++20
 *
 * This program computes the Nash Euilibrium Strategy for a two player all
 * in or fold Texas Holdem game given the blinds and stack sizes.
 *
 * To determine the winner of the hand we use the so-called Two-Plus-Two
 * Evaluator. See reference [2]. 
 *
 * The Nash Equilibrium strategy is found through a Regret Minimization
 * algorithm. Also sometimes called Monte Carlo Tree Search. See
 * reference [1].
 *
 * Notes:
 * The Nash Equilibrium is a single strategy but both strategies
 * taken together. It is like a dance.
 *
 * The strategies don't necessarily converge to a Nash Equilibrium.
 * It is the average strategy (averaged over the number of times the
 * decision node was reached which in our case is the number of times
 * the 2 card starter hand was randomly dealt).
 * 
 * Playing a Nash Equilibrium strategy isn't the one that could make you
 * the most money. There could be a better strategy that wins you more
 * money but it could have holes in it that could be exploited; it's a
 * double edged sword. Like in boxing, if you go for the attack, you expose
 * yourself to getting hit.
 *
 * There could be many Nash Equilibriums.
 *
 * The 2 player zero sum game is a special case. In that you could play
 * from any Nash Equilibrum. However, it doesn't generalize to games
 * with more than 2 players. For example, in a 3 player game,
 * 2 players could play from one Nash Equilibrium profile,
 * and if you play a strategy from another Nash Equilibrium profile, you
 * will probably lose. You would need to somehow all be playing from the
 * same Nash Equilibrium. However, this algorithm could work for 3 or more
 * players if you can somehow guess your opponent's strategy.
 * You could then set your opponents' strategies fixed and run
 * this regret matching algorithm to determine the best strategy.
 *
 * 'Index' Representation and 'Specific' Representation
 * We don't care about all (52 choose 2) hands, we can just care if they're
 * unsuited or suited or a pair. i.e. the strategy for the button when
 * dealt say Ac2d is the same for Ah2s. The particular suits don't matter.
 * The strategy for a particular player can be represented on a 13 x 13 grid
 * where one half (split diagonally) represents suited cards and the other
 * half are unsuited cards and the diagonal represents pairs. The row and
 * column number on this chart is what i will call 'the index' representation
 * of a starter hand. A starter hand can be represented as 2 numbers taken
 * from 1 to 52 inclusive where 1 = 2c, 2 = 2d, 3 = 2h, 4 = 2s, 5 = 3c, ...,
 * 48 = Ks, 49 = Ac, 50 = Ad, 51 = Ah, 52 = As. I will call this the
 * 'specific representation' of the starter hand. So a Ace of spades and
 * a 3 of hearts is (7, 52) in the specific representation and (12, 1). Where
 * I will use the convention that if the first number > second number, it
 * represents an unsuited hand and if the first number < second number,
 * it represents a suited hand in the index representation.
 *
 * Reference:
 * [1] Neller, T., Lanctot, M. An Introduction to Counterfactual Regret
 * Minimization[Computer Science Faculty Publications]. (2013). Retrieved
 * from https://cupola.gettysburg.edu/csfac/19/
 *
 * [2] https://web.archive.org/web/20111103160502/http://www.codingthewheel.com/archives/poker-hand-evaluator-roundup#2p2
 */
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cstring>
#include <array>
#include <sstream>
#include <fstream>
#include <span>

// To determine the winner of a hand you need to do
// 7 look ups (using th 5 community cards AKA 'the board'
// and your 2 cards AKA 'your hand' or 'your hole cards'
// This is a large array of integers produced by the
// Two-Plus-Two evaluator.
constexpr size_t HR_SIZE = 32487834;
const std::string HR_FILE = "handranks.dat";
std::array<int, HR_SIZE> handranks;
const int NUM_DEFAULT_ITERATIONS = 1000000;

// button outcome
enum class Outcome {WIN, LOSE, TIE};
enum class Action {PUSH, FOLD};

void load_handranks();
std::pair<int,int> get_index(std::array<int,2> hand);
int get_handvalue(std::span<int const> cards, int initial=53);


