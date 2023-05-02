#include "Bar.h"

// Name: Bar (Default Constructor) (not used)
// Desc: Dynamically allocates m_data for strings (always). m_fileName defaults to test.txt
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
Bar::Bar() {
	m_fileName = "test.txt";
	m_data = new LL<string>;
}
// Name: Bar (Overloaded Constructor)
// Desc: Used to pass an input file
//       Dynamically allocates m_data for strings (always)
//       Sets m_fileName and nothing done with m_dataSorted until SortData
// Preconditions: Input file
// Postconditions: m_data is allocated, m_fileName populated
Bar::Bar(string filename){
	m_fileName = filename;
	m_data = new LL<string>;
}
// Name: ~Bar (Destructor)
// Desc: Deallocates m_data
// Preconditions: m_data has been dynamically allocated
// Postconditions: m_data is empty
Bar::~Bar() {
	delete m_data;
}
// Name: Start
// Desc: Calls LoadFile, RemoveCommon, RemoveSingles, Sort, DisplayBars, and Export
//       During testing, may want to call Display
// Preconditions: None (filename is available)
// Postconditions: None
void Bar::Start() {
	LoadFile();
	RemoveCommon();
	RemoveSingles();
	SortData();
	DisplayBars();
	//Export();
}
// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything stringlike)
//       Calls RemovePunct as each item is loaded
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_data is populated
void Bar::LoadFile() {
	string word = "";
	string newString = "";
	ifstream myFile;
	myFile.open(m_fileName);
	int numWords = 0;

	if (myFile.is_open()) {
		cout << "File opened" << endl;
		while (getline(myFile, word, ' ')) {
			newString += (word + " ");
		}
		word = "";
	}
	else {
		cout << "File not opened" << endl;
	}

	for (unsigned int i = 0; i < newString.size() - 1; i++) {

		if (newString.at(i) == '\n') {
			RemovePunct(word);
			m_data->Insert(word);
			word = "";
			numWords++;
		}
		else if (newString.at(i) == ' ') {
			RemovePunct(word);
			m_data->Insert(word);
			word = "";
			numWords++;
		}
		else {
			word += newString.at(i);
		}
	}
/*
	while (word != "") {
		if (myFile.peek() == EOF) {
			word.erase(word.size() - 1);
		}
		RemovePunct(word);
		m_data->Insert(word);
		if (myFile.peek() == EOF) {
			word = "";
		}
		numWords++;
	}
	*/
	//m_data->Display();
	cout << numWords << " words loaded" << endl;
}
// Name: RemovePunct (passed a string)
// Desc: Converts all input into lowercase using tolower
//       When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
//       You can use ispunct - https://www.geeksforgeeks.org/ispunct-function-c/
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void Bar::RemovePunct(string& word) {
	unsigned int size = word.size() - 1;

	if (ispunct(word[0]) != 0) {
		word.erase(0 , 1);
		size--;
	}
	if (ispunct(word[size]) != 0) {
		word.erase(size);
	}
	//makes all characters lowercase
	for (unsigned int i = 0; i < word.size(); i++) {
		word[i] = tolower(word[i]);
	}
}
// Name: RemoveCommon
// Desc: Asks user if they want to remove common words
//       If yes, iterates through m_data and removes all common words after they are read
// Preconditions: m_data is populated and EXCLUDE_LIST is populated
// Postconditions: m_data will have no words from EXCLUDE_LIST
void Bar::RemoveCommon() {
	string choice = "";
	pair<string, int> set;
	string excludeList = "";
	string tempExList = "";
	cout << "Would you like to remove all common words (Only use with essays)?" << endl;
	cin >> choice;
	for (unsigned int i = 0; i < choice.size(); i++) {
		choice[i] = tolower(choice[i]);
	}
	if ((choice == "y") || (choice == "yes")) {
		for (int i = 0; i < m_data->GetSize(); i++) {
			set = (*m_data)[i];
			for (unsigned int j = 0; j < EXCLUDE_LIST.size(); j++) {
				excludeList = EXCLUDE_LIST.at(j);
				for (string::iterator it = excludeList.begin(); it != excludeList.end(); it++) {
					if (*it != ' ') {
						tempExList += *it;
					}
				}
				excludeList = tempExList;
				tempExList = "";
				if (excludeList == set.first) {
					m_data->RemoveAt(set.first);
					//makes sure iterator doesnt skip an index
					i--;
				}

			}

		}
		cout << "All common words removed." << endl;
	}
	//m_data->Display();
}
// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_data is a pointer!
// Preconditions: m_data is populated
// Postconditions: m_data will have no words with a frequency of 1
void Bar::RemoveSingles() {
	string choice;
	pair<string, int> set;
	int numRemoved = 0;

	cout << " Would you like to remove all words with a frequency of 1?" << endl;
	cin >> choice;

	for (unsigned int i = 0; i < choice.size(); i++) {
		choice[i] = tolower(choice[i]);
	}
	
	if ((choice == "y") || (choice == "yes")) {
		for (int i = 0; i < m_data->GetSize(); i++) {
			set = (*m_data)[i];
			if (set.second == 1) {
				m_data->RemoveAt(set.first);
				i--;
				numRemoved++;
			}
		}
		cout << numRemoved << " removed." << endl;
		//m_data->Display();

	}

}
// Name: SortData
// Desc: Iterates through each items in m_data and inserts into
//       m_dataSorted using the frequency as the key (can use make_pair)
// Preconditions: m_data is populated
// Postconditions: m_dataSorted is populated and sorted based on frequency
void Bar::SortData() {
	int freq = 0;
	string name = "";

	for (int i = 0; i < m_data->GetSize(); i++) {
		name = (*m_data)[i].first;
		freq = (*m_data)[i].second;
		m_dataSorted.insert(make_pair(freq, name));
	}

}
// Name: DisplayBars
// Desc: Displays a bar chart for each item in m_dataSorted from highest
//       frequency (at the top) to lowest frequency (at the bottom) (iterate backwards)
// Preconditions:  m_dataSorted is populated
// Postconditions: Bar charts are displayed
void Bar::DisplayBars() {
	int i = 0;
	for (multimap<int, string>::reverse_iterator rp = m_dataSorted.rbegin(); rp != m_dataSorted.rend(); rp++) {
		cout << setw(16) << rp->second << ": ";
		for (int i = 0; i < rp->first; i++) {
			cout << barChar;
		}
		cout << endl;
	}
}
// Name: Export
// Desc: Asks the user what name the export file should be called
//       Iterates through m_dataSorted and exports to file
// Preconditions: m_dataSorted is populated
// Postconditions: New export file is created and populated with a formatted bar chart
void Bar::Export() {
	string name = "";

	cout << "What would you like to call your export file?" << endl;
	cin >> name;

	ofstream outfile(name);
	for (multimap<int, string>::reverse_iterator rp = m_dataSorted.rbegin(); rp != m_dataSorted.rend(); rp++) {
		outfile << setw(16) << rp->second << ": ";
		for (int i = 0; i < rp->first; i++) {

			outfile << barChar;
		}
		outfile << endl;
	}
	outfile.close();
}