/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

int zero_i;
int zero_j;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();
    zero_i = zero_j = d - 1;
    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        // `man usleep` for more
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */

 // i -->  lignes
 // j --> colonnes
void init(void)
{
    // Initialize valeur initiale
    board[0][0] = d * d - 1 ;

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
           // assigne value of board[i][j] ;
           board[i][j] = board[0][0] - (i * d + j);
        }
    }
    //swap 1 et 2 si d pair
    if (d % 2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 0)
            {
                printf("_");
            }
            else
            {
                printf("%2i", board[i][j]);
            }

            if (j < d - 1)
            {
                printf("\t");
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // 1. FIND THE NUMBER
    int a, b ;
    // if (board[zero_i][zero_j] != 0)
    // {
    //     return false;
    // }
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                a = i;
                b = j;
                goto exist;
            }
        }
    }
    return false;

    // 2. VERIFY IF THE TILE IS ADJACENT TO THE BLANK SPACE
    exist:
    if ((board[a][abs(b - 1)] == 0) //left
    || ((board[a][b % d + 1] == 0) && (b < d - 1))  //right
    || (board[abs(a - 1)][b] == 0)  //top
    || ((board[a % d + 1][b] == 0) && (a < d - 1))) //bottom
    //a + b == zero_i + zero_j +ou-1
    {
        // 3. SWAP NUMBER <--> BLANK SPACE (0 or '_')
        board[zero_i][zero_j] = tile ;
        board[a][b] = 0;
        zero_i = a;
        zero_j = b;
        return true;
    }
    else
    {
        return false;
    }

}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if ((j == d - 1 && i == d - 1)
            && (board[i][j-1] == d * d - 1))
            {
                return true;
            }
            if ((board[0][0] == 1) && (i == 0 && j == 0))
            {
                continue;
            }
            if ((j == 0 && i > 0)
            && (board [i][j] == board[i-1][d-1] + 1))
            {
                continue;
            }
            else
            {
                if (board[i][j] == board[i][j-1] +1)
                {
                    continue;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}
