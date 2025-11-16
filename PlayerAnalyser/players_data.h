#ifndef PLAYERS_DATA_H
#define PLAYERS_DATA_H

typedef struct {
    char name[50];
    char role[20];
    char teamName[20];
    int performanceIndex; 
} Player;

Player players[50] = {

    { "Virat Kohli",        "Batter",       "IND",  94 },
    { "Rohit Sharma",       "Batter",       "IND",  90 },
    { "KL Rahul",           "WK-Batter",    "IND",  87 },
    { "Ravindra Jadeja",    "All-Rounder",  "IND",  85 },
    { "Jasprit Bumrah",     "Bowler",       "IND",  96 },

    { "David Warner",       "Batter",       "AUS",  88 },
    { "Steve Smith",        "Batter",       "AUS",  92 },
    { "Alex Carey",         "WK-Batter",    "AUS",  78 },
    { "Glenn Maxwell",      "All-Rounder",  "AUS",  84 },
    { "Mitchell Starc",     "Bowler",       "AUS",  93 },

    { "Joe Root",           "Batter",       "ENG",  91 },
    { "Jos Buttler",        "WK-Batter",    "ENG",  90 },
    { "Ben Stokes",         "All-Rounder",  "ENG",  88 },
    { "Moeen Ali",          "All-Rounder",  "ENG",  78 },
    { "Jofra Archer",       "Bowler",       "ENG",  85 },

    { "Kane Williamson",    "Batter",       "NZ",   95 },
    { "Devon Conway",       "WK-Batter",    "NZ",   86 },
    { "Daryl Mitchell",     "All-Rounder",  "NZ",   82 },
    { "Trent Boult",        "Bowler",       "NZ",   88 },
    { "Tim Southee",        "Bowler",       "NZ",   83 },

    { "Quinton de Kock",    "WK-Batter",    "SA",   89 },
    { "Aiden Markram",      "Batter",       "SA",   85 },
    { "Heinrich Klaasen",   "WK-Batter",    "SA",   90 },
    { "Marco Jansen",       "All-Rounder",  "SA",   80 },
    { "Kagiso Rabada",      "Bowler",       "SA",   92 },

    { "Babar Azam",         "Batter",       "PAK",  94 },
    { "Mohammad Rizwan",    "WK-Batter",    "PAK",  88 },
    { "Shadab Khan",        "All-Rounder",  "PAK",  81 },
    { "Shaheen Afridi",     "Bowler",       "PAK",  91 },
    { "Haris Rauf",         "Bowler",       "PAK",  84 },

    { "Nicholas Pooran",    "WK-Batter",    "WI",   87 },
    { "Shai Hope",          "Batter",       "WI",   82 },
    { "Jason Holder",       "All-Rounder",  "WI",   83 },
    { "Andre Russell",      "All-Rounder",  "WI",   89 },
    { "Alzarri Joseph",     "Bowler",       "WI",   80 },

    { "Shakib Al Hasan",    "All-Rounder",  "BAN",  88 },
    { "Litton Das",         "WK-Batter",    "BAN",  79 },
    { "Mushfiqur Rahim",    "WK-Batter",    "BAN",  82 },
    { "Taskin Ahmed",       "Bowler",       "BAN",  78 },
    { "Mahmudullah",        "All-Rounder",  "BAN",  76 }

};
#endif
