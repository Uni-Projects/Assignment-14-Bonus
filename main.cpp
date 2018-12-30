//Assignment 14_Bonus *FINAL BATTLE*
//Paolo Scattolin s1023775
//Johan Urban s1024726

#define NDEBUG
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <string.h>

using namespace std;


/*********************************************************************
*   type definitions and global array songs:
**********************************************************************/
struct Length
{
	int minutes;							// #minutes (0..)
	int seconds;							// #seconds (0..59)
};
struct Track
{
	string artist;                          // artist name
	string cd;                              // cd title
	int    year;                            // year of appearance
	int    track_no;						// track number
	string title;                           // track title
	string tags;                            // track tags (separated by ,)
	Length time;							// track length
	string country;                         // countr(y/ies) of artist (separated by ,)
};

const int MAX_NO_OF_SONGS = 6000;
vector<Track> songs ;
int iterations = 0 ;

/************************************************************************
*   Ordering relations op Track:
*      define < and == for Length and Track yourself, the other
*      ordering relations (>, <=, >=, >) follow from these automatically.
************************************************************************/
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    else return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    return (a.minutes == b.minutes && a.seconds == b.seconds) ;   /* implement a correct == ordering on Track values */
}

bool operator>(const Length& a, const Length& b)
{
	return b < a ;
}

bool operator<=(const Length& a, const Length& b)
{
	return !(b < a) ;
}

bool operator>=(const Length& a, const Length& b)
{
	return b <= a ;
}

bool operator<(const Track& a, const Track& b)
{
    iterations++;

    if(a.artist == b.artist)
    {
         if(a.cd == b.cd)
         {
             if(a.year == b.year)
             {
                return a.track_no < b.track_no;
             }else return a.year < b.year;

         }else return a.cd < b.cd;

   }else return a.artist < b.artist ;

   //return a.time < b.time ;
}

bool operator==(const Track& a, const Track& b)
{
    iterations++;
    return (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no) ;
    //return a.time == b.time;
}

bool operator>(const Track& a, const Track& b)
{
	return b < a ;
}

bool operator<=(const Track& a, const Track& b)
{
	return !(b < a) ;
}

bool operator>=(const Track& a, const Track& b)
{
	return b <= a ;
}

/************************************************************************
*   Reading Tracks.txt file:
************************************************************************/
istream& operator>> (istream& in, Length& length)
{// Pre-condition:
    assert (true) ;
/*  Post-condition:
    a value for length has been obtained from in: first minutes, followed by ':', followed by seconds.
*/
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{// Pre-condition:
    assert (true) ;
/*  Post-condition:
    length is sent to out as: minutes, ':', seconds (at least 2 digits)
*/
    out << length.minutes << ':';
	if (length.seconds < 10)
		out << '0';
	out << length.seconds;
	return out ;
}

void skip_to_next_newline (istream& infile)
{// pre-condition:
    assert (true) ;
/*  post-condition:
    infile has been read up to and including the next newline character.
*/
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{// pre-condition:
    assert (true) ;
/*  post-condition:
    infile has been read up to and including all members of one Track entry, including the last separating newline.
    These members are stored in track.
*/
    getline(infile,track.artist);       // artist
    getline(infile,track.cd);           // cd
    infile >> track.year ;              // year
    skip_to_next_newline(infile) ;
    infile >> track.track_no ;          // track number
    skip_to_next_newline(infile) ;
    getline(infile,track.title);        // track title
    getline(infile,track.tags);         // track tags
    infile >> track.time ;              // track time
    skip_to_next_newline(infile) ;
    getline(infile,track.country);      // country
    skip_to_next_newline(infile) ;
    return infile ;
}

// not necessary for assignment (because of show_track function), but included anyway because of symmetry:
ostream& operator<< (ostream& out, const Track track)
{// pre-condition:
    assert (true) ;
/*  post-condition:
    out has emitted all members of track, including the last separating newline.
*/
    out << track.artist   << endl ;
    out << track.cd       << endl ;
    out << track.year     << endl ;
    out << track.track_no << endl ;
    out << track.title    << endl ;
    out << track.tags     << endl ;
    out << track.time     << endl ;
    out << track.country  << endl ;
    out << endl ;
    return out ;
}

// NOTE: this version uses *array* implementation, convert to vector yourself
int read_songs (ifstream& infile, vector <Track>& songs)
{// pre-condition:
    assert (infile.is_open ()) ;
/*  post-condition:
    All tracks in infile have been read and stored in the same order in songs.
    The result is the number of tracks that have been read.
*/
    int i = 0 ;
    do {
        Track song ;
        infile >> song ;

        songs.push_back(song);
        i++;
    }
    while (!infile.eof() && i < MAX_NO_OF_SONGS);

    return i ;
}

int read_file (string filename)
{// pre-condition:
    assert (songs.size() == 0) ;
/*  post-condition:
    If the result is -1, then no file could be opened, and songs is unchanged.
    Otherwise, the result is zero or positive, and songs contains all the found tracks in the
    file that corresponds with filename.
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_SONGS = read_songs (songsDBS, songs);
	songsDBS.close();
	cout << "Read " << NO_OF_SONGS << " tracks." << endl;
	return NO_OF_SONGS;
}

// NOTE: this version uses *array* implementation, convert to vector yourself
void show_all_tracks (vector <Track> songs, int no_of_songs)
{// pre-condition:
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*  post-condition:
    songs[0] ... songs[no_of_songs-1] have been displayed to cout.
*/
    for (int i = 0 ; i < no_of_songs ; i++)
    {
        cout << i+1 <<". "<< songs[i] << endl ;
    }
}

/************************************************************************
*   sorting functions:
************************************************************************/

void swap (vector <Track>& songs, int  pos1, int pos2)
{
    Track temp;
    temp = songs[pos1];
    songs[pos1] = songs [pos2];
    songs[pos2] = temp;
}

void dnf (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    red = first-1;         // index last red
    blue = last+1;         // index first blue
    int white = last+1;    // index first white
    const Track PIVOT = songs [first+(last-first)/2];
    while (red < white - 1) // orange not empty
    {
         const int NEXT = white - 1; // last orange
         if (songs[NEXT] < PIVOT) // belongs in red
         {
              red++; // swap with first orange
              swap (songs, red, NEXT) ;
         }
         else if (songs[NEXT] == PIVOT) // belongs in white
               white-- ; // white area one larger
         else // belongs in blue
         {
              white--;
              blue--; // swap with last white
              swap (songs, NEXT, blue);
         }
     }
}

void special_dnf (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    red = first - 1;                     // index last red
    blue = last + 1;                     // index first blue
    int white = first - 1;               // index last white
    const Track PIVOT = songs [first+(last-first)/2];
    while (white < blue - 1)             // orange not empty
    {
         const int NEXT = blue - 1;      // last orange
         if (songs[NEXT] < PIVOT)        // belongs in red
         {
              red++;                     //adjust last red
              white++;                   //adjust last white
              swap(songs, red, NEXT);    // swap with first orange
         }
         else if (songs[NEXT] == PIVOT)  // belongs in white
         {
             white++;                    // adjust last white
             swap(songs, NEXT, white);   // swap last orange with first orange
         }

         else                            // belongs in blue
         {
              blue--;                    // adjust first blue
              swap (songs, NEXT, blue);  // swap first blue with last orange
         }
     }
}

void quicksort (vector<Track>& songs, int first, int last)
{
   // PRE:
   assert (0 <= first && last < size (songs)) ;
   // POST: songs[first] ... songs[last] is sorted
   if (first >= last)
      return;
   else
    {
      int red, blue ;
      dnf(songs, first, last, red, blue) ;
      quicksort (songs, first, red) ;
      quicksort (songs, blue, last) ;
    }
}

void special_quicksort (vector<Track>& songs, int first, int last)
{
   // PRE:
   assert (0 <= first && last < size (songs)) ;
   // POST: songs[first] ... songs[last] is sorted
   if (first >= last)
      return;
   else
    {
      int red, blue ;
      special_dnf(songs, first, last, red, blue) ;
      quicksort (songs, first, red) ;
      quicksort (songs, blue, last) ;
    }
}

struct Slice
{
	int from ; 	// 0    <= from
	int to ; 	// from <= to
} ;

Slice mkSlice (int from, int to)
{//	pre-condition:
	assert (0 <= from && from <= to);
/*  post-condition:
    result is the slice formed by from and to.
*/	Slice s = { from, to } ;
	return s ;
}

bool valid_slice (Slice s)
{// pre-condition:
    assert (true) ;
/*  post-condition:
    result is true only if s.from is not negative, and s.from is not larger than s.to.
*/
	return 0 <= s.from && s.from <= s.to ;
}

bool is_sorted ( vector <Track>&  songs, Slice s)
{//	pre-condition:
	assert (valid_slice(s)) ;	// ...and s.to < size of songs
//	post-condition:
//	result is true if	songs[s.from]   <= songs[s.from+1]
//						songs[s.from+1] <= songs[s.from+2]
//						...
//						songs[s.to-1]   <= songs[s.to]
	bool sorted = true ;
	for (int i = s.from; i < s.to && sorted; i++)
		if (songs[i] > songs[i+1])
			sorted = false ;
	return sorted ;
}

int find_position ( vector <Track>&  songs, Slice s, Track y )
{//	pre-condition:
	assert (valid_slice(s) && is_sorted(songs,s)) ;    // ...and s.to < size of songs
//	post-condition: s.from <= result <= s.to+1
	for ( int i = s.from ; i <= s.to ; i++ )
		if ( y <= songs [i] )
			return i ;
	return s.to+1;
}

void shift_right ( vector <Track>&  songs, Slice s )
{//	pre-condition:
	assert (valid_slice (s)) ;	// ... and s.to < size (songs) - 1
//	post-condition:  songs[s.from+1]	= 	old songs[s.from]
//			    	 songs[s.from+2]	= 	old songs[s.from+1]
//						...
//			    	 songs[s.to+1]		= 	old songs[s.to]
	for ( int i = s.to+1 ; i > s.from ; i-- )
		songs [i]  = songs [i-1] ;
}

void insert ( vector <Track>&  songs, int& length, Track y )
{// pre-condition:
    Slice s = mkSlice(0,length-1) ;
    assert (length >= 0 && is_sorted (songs, s)) ;
/*  post-condition:
    value y is inserted in songs[0] ... songs[length-1] at the right ordering position,
    and length is increased by one.
*/
	const int POS = find_position (songs, mkSlice (0, length-1), y) ;
	if (POS < length)
		shift_right ( songs, mkSlice (POS, length-1) ) ;
	songs [POS] = y ;
	length++;
}

void insertion_sort ( vector <Track>&  songs, int length )
{
	int sorted = 1 ;
    while ( sorted < length )
    {
        insert ( songs, sorted, songs[sorted] ) ;
    }
}

//	array based selection sort:
int smallest_value_at ( vector <Track>&  songs, Slice s )
{//	pre-condition:
	assert (valid_slice (s)) ;	// ... and s.to < size (s)
//	Post-condition: s.from <= result <= s.to and songs[result] is
//	the minimum value of songs[s.from] .. songs[s.to]
	int smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( songs [index] < songs [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort ( vector <Track>&  songs, int length )
{
    for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{
        const int k = smallest_value_at (songs, mkSlice (unsorted, length-1));
	    swap ( songs, unsorted, k ) ;
	}
}

//	array based bubble sort:
bool bubble ( vector <Track>&  songs , Slice s )
{//	pre-condition:
	assert (valid_slice(s));	// ... and s.to < size(songs)
//	Post-condition:
//	maximum of songs[s.from]..songs[s.to] is at songs[s.to]
//	if result is true then sorted( songs, s )
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if ( songs [i] > songs [i+1])
		{	swap ( songs, i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort ( vector <Track>&  songs, int length )
{
    while ( !bubble ( songs, mkSlice (0, length-1 ) ) )
        length-- ;
}

//heap sort:

void push_up(vector <Track>& songs, int i)
{
    //preconditions:
    assert(i >= 0 && i < MAX);
    //postcondition: the elements is pushed to its highest position.

    while (songs[i] > songs[(i-1)/2])
    {
        swap (songs, i , (i-1)/2);
        i = (i-1)/2;
    }
}

void build_heap(vector <Track>& songs,int MAX)
{
    //preconditions:
    assert(true);
    //postconditions: the function calls push_up for each el. of the array.

    for (int i = 1 ; i < MAX ; i++)
    {
        push_up(songs,i);
    }
}

void push_down(vector <Track>& songs, int MAX_EL)
{
    // precondition:
    assert(MAX_EL >= 0);
    // postcondition:
    // A value is placed more and more toward the end of the vector being sorted,
    // until it is no longer larger than one of its children.
    while (MAX_EL > 0)
    {
        int i = 0;
        while (2*i+1 < MAX_EL)
        {
            if(2*i+2 < MAX_EL && (songs[2*i+1] >= songs[2*i+2]))
            {
                if (songs[i] <= songs[2*i+1])
                {
                    swap (songs, i , 2*i + 1);
                    i = 2*i + 1;
                }
            }
            else if (2*i+2 < MAX_EL && (songs[2*i+1] < songs[2*i+2]))
            {
                if (songs[i] <= songs[2*i+2])
                {
                    swap (songs, i , 2*i + 2);
                    i = 2*i + 2;
                }
            }
            else if (songs[i] <= songs[2*i+1])
            {
                swap (songs, i , 2*i + 1);
                i = 2*i + 1;
            }
            i++;
        }
        MAX_EL--;
    }
}

void pick_heap(vector <Track>& songs, int MAX)
{
    // precondition:
    assert(true);
    //postcondition:
    //the vector is being sorted by a cooperation of two implemented functions:
    // swap() and push_down().
    int MAX_EL = MAX;

    for (int i = 0; i < MAX ; i++)
    {
        swap (songs ,0, MAX_EL-1);
        MAX_EL--;
        push_down(songs ,MAX_EL);
    }
}

void algorithm_selection (vector <Track>&  songs)
{
    char c;

    cout << "Which sorting agorithm?" << endl ;
    cout << "Insertion Sort --> i" << endl ;
    cout << "Selection Sort --> s" << endl ;
    cout << "Bubble Sort --> b" << endl ;
    cout << "Heap Sort --> h" << endl ;
    cout << "Quicksort --> q" << endl ;
    cin >> c ;

    switch (c)
    {
        case 'i':
            insertion_sort(songs,songs.size());
            break;
        case 's':
            selection_sort(songs,songs.size());
            break;
        case 'b':
            bubble_sort(songs,songs.size());
            break;
        case 'h':
             build_heap(songs,songs.size());
             pick_heap(songs,songs.size());
            break;
        case 'q':
            quicksort(songs,0, songs.size()-1);
            break;
        default:
            cout << "Please insert a valid option!" << endl ;
            break;
    }
}
/************************************************************************
*   the main structure of the program:
*       - read file
*       - sort songs with insertion_sort / selection_sort / bubble_sort /
*         heap sort / quick sort.
*              and "normal" order of Tracks
*              and increasing track length
************************************************************************/

int main()
{
    int first = 0;

	const int NO_OF_SONGS = read_file ("Tracks.txt");

	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }

    algorithm_selection(songs);

    show_all_tracks(songs,NO_OF_SONGS);
    cout << "# of iterations: " << iterations << endl ;
    iterations = 0 ;
    /*
     Now the algorithm are going to sort the track songs by time.
     If you want to sort by track number in the album, just comment the .time part
     in these 2 functions and de-comment the rest.

     bool operator<(const Track& a, const Track& b)

     bool operator==(const Track& a, const Track& b)
    */

	return 0;
}

