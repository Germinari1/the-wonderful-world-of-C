//Tideman election algorithm
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j -> graph
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct //data items = index of winner/looser on candidate (2D) array
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2]; //array size = all possible pairs (no redundancy); only non-tie comporisons included

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //validate user input and add rank
    for(int i=0; i<candidate_count; i++)
    {
        if(strcmp(name, candidates[i])==0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //nested loop to access both ith preferred candidate and the one after it (update array in pair comparisons)
    for(int i=0; i<candidate_count; i++)
    {
        for(int j=i+1; j<candidate_count; j++){
            int preference_1 = ranks[i];
            int preference_2 = ranks[j];
            //update preferences array
            preferences[preference_1][preference_2]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // iterate over candidates
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }

    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {

        for (int j = 0; j < pair_count - i - 1; j++) // implement bubble sort
        {
            int first_i = pairs[j].winner;
            int first_j = pairs[j].loser;
            int force_p1 = preferences[first_i][first_j] - preferences[first_j][first_i]; //force of 1° pair

            int second_i = pairs[j + 1].winner;
            int second_j = pairs[j + 1].loser;
            int force_p2 = preferences[second_i][second_j] - preferences[second_j][second_i]; // force of 2° pair
            if (force_p1 < force_p2) //compare forces and swap pairs when necessary
            {
                pair tmp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = tmp;
            }
        }
    }
    return;
}

//helper recursive function to determine if a loop in the graph will be formed by adding another edge -> returns true if a cycle is detected
bool cycle_checker(int cand_winner, int cand_loser)
{
    if (locked[cand_loser][cand_winner] == true)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[cand_loser][i] == true && cycle_checker(cand_winner,i))
        {
            return true;
        }
    }
    return false;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int cand_winner = pairs[i].winner;
        int cand_loser = pairs[i].loser;
        if(!cycle_checker(cand_winner, cand_loser)) //if considered edge does not cause a cycle, establish edge
        {
            locked[cand_winner][cand_loser] = true; //edge
        }
    }
    return;
}

// Print the winner of the election -> candidate who is not pointed by any other candidate
void print_winner(void)
{
    for(int i=0; i<candidate_count; i++)
    {
        bool source = true;
        for(int j=0; j<candidate_count; j++)
        {
            if(locked[j][i])
            {
                source = false;
                break;
            }
        }
        if(source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}