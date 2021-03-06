#include "helpers.hpp"

void cinclr(){
    while (cin.get() == '\n');
    cin.unget();
}

void clean(string& s){
    if(s[s.size()-1] == '\r' || s[s.size()-1] == '\n') //Thank linux for making this even necessary
        s.pop_back();
    s.erase( std::remove_if( s.begin(), s.end(), []( char c ) { return !std::isalpha(c) ; } ), s.end() ); //Get rid of non-letters
    transform(s.begin(), s.end(), s.begin(), ::tolower); //lowercase
}

vector<string> getWords(string filename){
    ifstream file(filename);
    vector<string> words;
    string word;
    while(!file.eof()){
        file >> word;
        clean(word);
        words.push_back(word);
    }
    file.close();
    return words;
}

pair<string, string> makeSpell(){
    extern vector<string> verbs;
    extern vector<string> nouns;
    pair<string, string> spellPair;
    spellPair.first = verbs[rand() % verbs.size()];
    spellPair.second = nouns[rand() % nouns.size()];
    return spellPair;
}

bool inDict(string verb, string noun){
    extern vector<string> verbs;
    extern vector<string> nouns;
    return (find(verbs.begin(), verbs.end(), verb) != verbs.end()) && (find(nouns.begin(), nouns.end(), noun) != nouns.end());
}

int countDiff(string pre, string post){
    vector<int> charCountPre(26, 0); vector<int> charCountPost(26, 0);
    for(char c : pre){
        char lowc = tolower(c);
        if(lowc >= 'a' && lowc <= 'z')
            charCountPre[lowc - 'a']++;
    }
    for(char c : post){
        char lowc = tolower(c);
        if(lowc >= 'a' && lowc <= 'z')
            charCountPost[lowc - 'a']++;
    }
    int diff = 0;
    for(int i = 0; i < 26; i++){
        diff += abs(charCountPre[i] - charCountPost[i]);
    }
    return diff;
}

string strDiff(string pre, string post){
    vector<int> count(26, 0);
    string diff;
    for(char c : pre)
        count[c-'a']++;
    for(char c : post)
        count[c-'a']--;
    for(int i = 0; i < count.size(); i++){
        if(count[i] > 0) {
            char c = 'a' + i;
            for (int j = 0; j < count[i]; j++)
                diff.push_back(c);
        }
    }
    return diff;
}

int countAdditions(string pre, string post){
    vector<int> count(26, 0);
    int diff = 0;
    for(char c : post)
        count[c-'a']++;
    for(char c : pre)
        count[c-'a']--;
    for(unsigned int i = 0; i < count.size(); i++){
        if(count[i] > 0)
            for (int j = 0; j < count[i]; j++)
                diff++;
    }
    return diff;
}

int compareWords(string a, string b){
    stringstream as(a);
    stringstream bs(b);
    map<string, int> aWords;
    map<string, int> bWords;
    string temp;
    while(as){
        as >> temp;
        temp.erase(remove_if(temp.begin(), temp.end(), [](unsigned char c){return !isalpha(c);}), temp.end());
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        ++aWords[temp];
    }
    while(bs){
        bs >> temp;
        temp.erase(remove_if(temp.begin(), temp.end(), [](unsigned char c){return !isalpha(c);}), temp.end());
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        ++bWords[temp];
    }
    int diff = 0;
    for (pair<std::string, int> element : aWords){ //Initializes non shared words
        bWords[element.first];
    }
    for (pair<std::string, int> element : bWords){
        diff += abs(element.second - aWords[element.first]);
    }
    return diff;
}