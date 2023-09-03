#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

//computes the Coleman-Liau index of text.

int count_letter(string txt);
int count_words(string txtw);
int count_sent(string txts);


int main(void)
{
    //get user`s text
    string text = get_string("Add your text, please: ");
    //count letters, words ans sentences > plug to formula [index = 0.0588 * L - 0.296 * S - 15.8] -> round to nearest int.
    float l =(float)count_letter(text)/(float)count_words(text)*100;
    float s =(float)count_sent(text)/(float)count_words(text)*100;
    float index = (0.0588 * l) - (0.296 * s) - 15.8;
    //print grade
    int final_index = round(index);
    if (final_index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (final_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n",final_index );
    }
}

// function to count letters
int count_letter(string txt)
{
    int count = 0;
    for (int  i= 0; i < strlen(txt); i++)
    {
        char c = txt[i];;
        if (isalpha(c) !=0)
        {
            count++;
        }
    }
    return count;
}

//function to count words
int count_words(string txtw)
{
    int countw = 1;
    for(int j=0; j < strlen(txtw); j++)
    {
        char e = txtw[j];
        if ( e == ' ')
        {
            countw++;
        }
    }
    return countw;
}

//function to count sentences
int count_sent(string txts)
{
    int counts = 0;
    for (int z=0; z < strlen(txts); z++)
    {
        char d = txts[z];
        if ( d == '.' ||d == '!'||d == '?')
        {
            counts++;
        }
    }
    return counts;
}