/*******************************************************************************
 Title          : tree.cpp
 Author         : Kasey Harvey
 Created on     : March  6, 2019
 Description    : The implementation file for the Tree class
 Purpose        : To provide a minimal interface to be used to interact with
 the Tree objects.
 Usage          :
 Build with     : g++ -Wall -Wpedantic -Werror -g tree.cpp -o tree
 Modifications  :
 
 *******************************************************************************/

#include "tree.h"
#include <string>
#include <sstream>


// Helper Functions

/** SplitOnComma splits (line,before_comma,after_comma) a string based on commas
 *   @param line         [in]
 *   @param before_comma [in]
 *   @param after_comma  [in]
 *   example : apple, pen
 *   str == apple, pen ; str2 == apple, str3 == pen
 */
void SplitOnComma(string line, string & before_comma, string &  after_comma){
    before_comma   = "";
    after_comma    = "";
    char comma = ',';
    
    int i = 0; //Begin at first char of word
    while ((i < line.size()) && (line[i] != comma)) //While i < line length & is not a comma
    {
        before_comma += line[i]; //Add char to "before" variable
        i++; //Move to next char, continue while loop
    }
    i++; //Skip the comma, move onto next feild
    while (i < line.size()) //while i < line length
    {
        after_comma += line[i]; //Add each char to "after" variable
        i++; //Move to next char
    }
}

/** ConvertLower
 *  converts string to lowercase
 *  @param string str [in]
 *  @return string new_str
 */
string ConvertLower(string str){
    string new_str;
    for (int count = 0; count < str.length(); count++) {
        new_str+=tolower(str[count]);
    }
    return new_str;
}

/** IsNumber (str)
 *  checks if string is a number
 *  @param string str [in]
 *  @return true if str is a number , false is not
 */
bool IsNumber(string & str) {
    for (int count = 0; count < str.length(); count++){
        if (isdigit(str[count]) == false)
            return false;
    }
    return true;
}

/** IsPositiveNumber (str)
 *  converts string to lowercase
 *  @param string str [in]
 *  @return true if str is a positive number , false is not
 */
bool IsPositiveNumber(string & str) {
    for (int i = 0; i < str.length(); i++){
        if (isdigit(str[i]) == true && stoi(str) > 0)
            return true;
        }
    return false;
}

/** IsBorough (str)
 *  checks if string is a borough
 *  @param string str [in]
 *  @return true if str is a Borough , false is not
 */
bool IsBorough(string & str) {
    if ( str == "Bronx" || str == "Brooklyn" || str == "Manhattan" ||
        str == "Queens" || str == "Staten Island") return true;
    return false;
}

/** TreeStatus (str)
  *  checks if status is a valid
  *  @param string str [in]
  *  @return true if str is a valid status , false is not
  */
bool TreeStatus(string str){
    if (str == "Alive" || str == "Dead" || str == "Stump" || str == "") return true;
    return false;
}
/** TreeHeath (str)
 *  checks if health is valid
 *  @param string str [in]
 *  @return true if str is a valid health , false is not
 */
bool TreeHealth(string str){
    if (str == "Good" || str == "Fair" || str == "Poor" || str == "")
        return true;
    return false;
}

//Public Functions

Tree::Tree():tree_id(0),tree_dbh(0),status(""),health(""),spc_common(""),
zipcode(0),address(""),boroname(""),latitude(0),longitude(0){
    
}

Tree::Tree(const string & str){
    int column_counter = 1;
    string feild[50];

    string line; // string from param
    string before_cma; // before comma
    string after_cma; // after comma

    SplitOnComma(str, before_cma,after_cma);
    feild[column_counter] = before_cma;
    column_counter++;

    while(!after_cma.empty()){
        feild[column_counter] = before_cma;
        SplitOnComma(after_cma, before_cma,after_cma);
        
        column_counter++;

    }
    if((IsPositiveNumber(feild[1])) && (IsPositiveNumber(feild[5])) &&
        (TreeStatus(feild[8])) && (TreeHealth(feild[9])) &&
        (!IsNumber(feild[11]) && (!feild[11].empty())) && (!feild[26].empty())
        && ((feild[27].length() <= 5) && (IsNumber(feild[27]))) &&
        (IsBorough(feild[31])) && (IsPositiveNumber(feild[39])) &&
        (!IsPositiveNumber(feild[40]))){
                                                                                                                                                                                              
        tree_id    = stoi(feild[1]);
        tree_dbh   = stoi(feild[5]);
        status     = feild[8];
        health     = feild[9];
        spc_common = feild[11];
        address    = feild[26];
        zipcode    = stoi (feild[27]);
        boroname   = feild[31];
        latitude   = stold (feild[39]);
        longitude  = stold (feild[40]);
        }
    else{
        tree_id    = 0;
        tree_dbh   = 0;
        status     = "";
        health     = "";
        spc_common = "";
        address    = "";
        zipcode    = 0;
        boroname   = "";
        latitude   = 0;
        longitude  = 0;
    }
                                                                                    
}

Tree::Tree(int id, int diam,  string stat, string hlth, string name,
     int zip, string addr, string boro, double lat, double longtd):
     tree_id(id),tree_dbh(diam),status(stat),health(hlth),spc_common(name),
    zipcode(zip),address(addr),boroname(boro),latitude(lat),longitude(longtd){
    
}

ostream& operator<< (ostream & os, const Tree & t){
    char comma = ',';
    os << t.spc_common << comma << t.tree_id << comma << t.tree_dbh << comma <<
    t.status << comma << t.health << comma << t.address << comma << t.zipcode <<
    comma << t.boroname << comma << t.latitude << comma << t.longitude;
    return os;
}

bool operator==(const Tree & t1, const Tree & t2){
    if ((samename(t1,t2)) && (t2.tree_id == t1.tree_id)) return true;
    return false;
}

bool operator<(const Tree & t1, const Tree & t2){
    if ((islessname(t1,t2)) ||
        ((samename(t1,t2))&&(t2.tree_id>t1.tree_id))) return true;
    return false;
}

bool samename(const Tree & t1, const Tree & t2){
    if (t2.spc_common.length() == t1.spc_common.length()){
        if ((ConvertLower(t2.spc_common)) != (ConvertLower(t1.spc_common)))
                return false;
        else return true;
    }
    return false;
}

bool islessname(const Tree & t1, const Tree & t2){
    if (t2.spc_common.length() == t1.spc_common.length()){
        if (ConvertLower(t2.spc_common) < ConvertLower(t1.spc_common))
            return false;
        else return true;
    }
    return false;
}

string Tree::common_name() const{
    return spc_common;
}

string Tree::borough_name() const{
    return boroname;
}
/** Returns address
 */
string Tree::nearest_address() const{
    return address;
}

/** Returns tree's status
 */
string Tree::life_status() const{
    return status;
}

/** Returns tree's health status
 */
string Tree::tree_health() const{
    return health;
}

/** Returns tree's id number
 */
int Tree::id()       const{
    return tree_id;
}

/** Returns tree's zipcde
 */
int Tree::zip_code() const{
    return zipcode;
}

/** Returns tree's dbh
 */
int Tree::diameter() const{
    return tree_dbh;
}

/** Returns tree's position
 */
void Tree::get_position(double & latitude,double & longitude) const{
//    double x = latitude;
//    double y = longitude;
}

