#include<iostream>

using namespace std;

// HashMap
class HashMap {
    int degree;       // string count to calculate hash value
    int space;        // max array to save same hash value
    string*** map;    // the space to set key and value
    int* map_cnt;     // the number of space for each hash value

    // inner function to get a convert value
    int convertValue(char a);

    // inner function to get a hash value
    int getHash(string str);
public:
    // constructor
    HashMap(int _degree, int _space);

    void setValue(string key, string value);

    string getValue(string key);

    void removeValue(string key);

};

//constructor
HashMap::HashMap(int _degree, int _space){
    // 64 is the maximum convect value in getHash function. and degree is calculating number.
    int all_space;
    int i;

    space = _space;
    degree = _degree;

    all_space = 1 << (6 * degree);

    map = new string**[all_space];
    map_cnt = new int[all_space];

    for(i = 0; i < all_space; i++ ){
        map[i] = NULL;
        map_cnt[i] = 0;
    }
}

// string to int and minimum value is 0 and maximum value is 63
int HashMap::convertValue(char c){
    int ret_val = -1;
    if( c=='.' ){
        ret_val = 0;
    }
    if( c>='0' && c<='9' ){
        ret_val = c - '0' + 1 ; // '.'
    }
    else if( c>='A' && c<='Z' ){
        ret_val = c - 'A' + 11; // '.' + number
    }
    else if( c=='_' ){
        ret_val = 37;           // '.' + number + upper case letter
    }
    else if( c>='a' && c<='z' ){
        ret_val = c - 'a' + 38; // '.' + number + upper case letter + '_'
    }
    return ret_val;
}

// string convert to int use remainder
int HashMap::getHash(string str){
    int ret_val = 0;
    int tmp_val, i, j;
    int len = str.length();
    bool is_valid = false;

    for( i=1; i<=degree; i++){
        if( str.length() > i ){
            // save convert value
            tmp_val = convertValue(str[len-i]);
            // if it is valid value
            if( tmp_val != -1 ){
                is_valid = true;
                
                for( j=1; j<i; j++){
                    tmp_val *= 64; // digit add
                }
                ret_val += tmp_val;
            }
        }
        else{
            break;
        }
    }

    if( is_valid == false ){
        ret_val = -1;
    }

    return ret_val;
}

// set key, if exists match value then update else insert
void HashMap::setValue(string key, string value){
    int hash;
    int idx;
    int i;
    string log_header = "[setValue] ";

    hash = getHash(key);

    if( hash != -1 ){
        // check space
        idx = map_cnt[hash];

        // allocate key space
        if( idx == 0 ){
            map[hash] = new string*[space];
        }

        // check exist key value
        for( i=0; i<idx; i++){
            if( key.compare(map[hash][i][0]) == 0 )
                break;
        }

        // check space for add anothre value
        if( idx == space ){
            cout << log_header << key << " have no space." << endl;
        }
        // set value
        else{
            if( idx == i ){
                map[hash][i] = new string[2];
                map_cnt[hash] = idx+1;
            }
            map[hash][i][0] = key;
            map[hash][i][1] = value;
        }
    }
    // hash is -1
    else{
        cout << log_header << key << " is invalid ( valid text is  '.' / 'a'-'z' / '_' / 'A'-'Z' )" << endl;
    }
}

// remove value if exists key
void HashMap::removeValue(string key){
    int idx, i;
    int hash;
    string log_header = "[removeValue] ";
    
    hash = getHash(key);
    
    if( hash!=-1 ){
        idx = map_cnt[hash];
        // check space and exists key value
        for(i=0; i<idx; i++){
            if( key.compare(map[hash][i][0]) == 0 )
                break;
        }

        // if key is valid
        if( i != idx ){
            // move the right value
            while( i<idx-1 ){
                map[hash][i][0] = map[hash][i+1][0];
                map[hash][i][1] = map[hash][i+1][1];
                i++;
            }

            // set empty string and set null
            map[hash][i][0].clear();
            map[hash][i][1].clear();

            map_cnt[hash] = idx-1;

            // if empty set
            if( i == 0 ){
                delete(map[hash]);
            }
        }
        // no value
        else{
            cout << log_header << key << " have no hash set" << endl;
        }
    }
    // hash is -1
    else{
        cout << log_header << key << " is invalid ( valid text is  '.' / 'a'-'z' / '_' / 'A'-'Z' )" << endl;
    }
}

// get the value if the key is already setting
string HashMap::getValue(string key){
    int idx, i;
    int hash;
    string ret_val = "";
    string log_header = "[getValue] ";

    hash = getHash(key);

    if( hash!=-1 ){
        idx = map_cnt[hash];
        // check space and exists key value
        for(i=0; i<idx; i++){
            if( key.compare(map[hash][i][0]) == 0 )
                break;
        }

        // if find the value
        if( idx!=i ){
            ret_val = map[hash][i][1];
        }
        // no value
        else{
            cout << log_header << key << " have no hash set" << endl;
        }
    }
    // hash is -1
    else{
        cout << log_header << key << " is invalid ( valid text is  '.' / 'a'-'z' / '_' / 'A'-'Z' )" << endl;
    }

    return ret_val;
}

int main(){
    // hash map
    HashMap map(3, 1024);
    string get_value;

    cout << " * set Kyo" << endl;
    map.setValue("Kyo", "170");

    cout << " * set Park" << endl;
    map.setValue("Park", "180");

    cout << " * get Kyo" << endl;
    get_value = map.getValue("Kyo");
    if( get_value.length() > 0 ){
        cout << "The value of 'Kyo' is " << get_value << endl;
    }

    cout << " * remove Kyo" << endl;
    map.removeValue("Kyo");

    cout << " * get Kyo" << endl;
    get_value = map.getValue("Kyo");
    if( get_value.length() > 0 ){
        cout << "The value of 'Kyo' is " << get_value << endl;
    }

    return 0;  
}