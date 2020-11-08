/*******************************************************************************
 Title          : tree_species.cpp
 Author         : Kasey Harvey
 Created on     : March  6, 2019
 Description    : The implementation file for the TreeSpecies class
 Purpose        : To provide lsit of tree species
 Usage          :
 Build with     : g++ -Wall -Wpedantic -Werror -g tree_species.cpp -o treespecies
 Modifications  :
 
 *******************************************************************************/
#include <iostream>
#include <string>
#include <list>
#include <set>
#include "tree_species.h"
#include "__tree_species.h"

using namespace std;

// Helper Functions

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

/** SplitOnAlpha splits (line,before,after) a string based on letters.
 *  ignores all characters in between numbers
 *   @param string line  [in]
 *   @param string before [in]
 *   @param string after  [in]
 *   example : apple, pen
 *   line == apple, pen ; before_comma == apple, after_comma == pen
 */

void SplitOnAlpha(string line, string & before, string &  after){
    before   = "";
    after    = "";
    
    int i = 0; //Begin at first char of word
    while ((isalpha(line[i])) && (i < line.size())) //While i < line length & is not a comma
    {
        before += line[i];
        //        line[i]; //Add char to "before" variable
        i++; //Move to next char, continue while loop
    }
    i++; //Skip the comma, move onto next feild
    while (i < line.size()) //while i < line length
    {
        after += line[i]; //Add each char to "after" variable
        i++; //Move to next char
    }
}

/** IsThereSpace
 *  converts string to lowercase
 *  @param string str [in]
 *  @return true if there is space in str , false if not
 */
bool IsThereSpace (string str){
    for (int count = 0; count < str.size(); count++) {
        if (isspace(str[count])) {
            return true;
        }
    }
    return false;
}
//  use find func since it's now seperated
//  add species & partial to a word string, minus '-' & replace them with a
//space. then use find to located if in species. when true,  return species

/** PartialWnWOSpace (species, partial, space_check) - Partial With and without
 *  Space
 *  takes two string and check if they are sub strings of each other
 *  int tells if it is with or without space.
 *  1 = nospace ; 2 = space.
 *** if partial_name contains no spaces
 *  @post split species to get the next naming
 *  if species when split once == partial_name
 *  matched found
 *  else keep slippting the species name
 *  until partial name is found or until species name is empty
 *  i.e. partial name is not a partial name of any species
 *  @return species
 *** if partial_name contains spaces
 *  splits both species and partical and compare
 ** if the 'before' of both species and partial are ==
 *  split and loop thru the rest of both partial and species until not matched
 *  or until species is empty or there is no space, meaning no other words to be
 *  matched
 *  on the first instance of not matched
 *  Matched: if there is another word in species and not in partial
 *  or species == partial
 *  @return matched species or nothing
 ** if the 'before' of both species and partial are !=
 *  split and loop thru the rest of both species until matched
 *  or until species is empty or there is no space, meaning no other words to be
 *  matched
 *  on the first instance of matched
 *  loop thru the rest of both partial ans species until not matched
 *  or until species is empty or there is no space, meaning no other words to be
 *  matched
 *  NOTMatched: if partial does not match species and partial have more
 *  space(words)
 *  or there is no space(words) on both it doessnt match
 *  Matched: if there is another word in species and not in partial
 *  or species == partial
 *  @return matched species or nothing
 *  @param string species   [in]
 *  @param string partial   [in]
 *  @param int space_check  [in]
 *  @return string empty if not matched , or with species if matched
 */
string PartialWnWOSpace (string species, string partial, int space_check){
    string species_saved = ConvertLower(species);
    string species_before, species_after, partial_before, partial_after,
    nothing = "";
    if (partial.length() > species_saved.length()) return nothing;
    if (partial == nothing) return nothing;
    if (species_saved == partial) return species_saved;
    
    if (space_check == 1) {
        SplitOnAlpha(species_saved,species_before,species_after);
        if ((species_before == partial) || (species_after == partial)) {
            return species_saved;
        }
        else {
            while (!species_after.empty()) {
                SplitOnAlpha(species_after,species_before,species_after);
                if (species_before == partial) {
                    return species_saved;
                }
            }
        }
        
    }
    if (space_check == 2) {
        SplitOnAlpha(species_saved,species_before,species_after);
        SplitOnAlpha(partial,partial_before,partial_after);
        
        if (species_before == partial_before) {
            while ((!species_after.empty() )&& (!partial_after.empty())) {
                if ((IsThereSpace(species_after)) &&
                    (IsThereSpace(partial_after))){
                    SplitOnAlpha(species_after,species_before,species_after);
                    SplitOnAlpha(partial_after,partial_before,partial_after);
                    if (species_before != partial_before) return nothing;
                }
                if ((!IsThereSpace(partial_after)) &&
                    (!IsThereSpace(species_after))){
                    if (species_after != partial_after) return nothing;
                    return species_saved;
                }
                if ((!IsThereSpace(partial_after)) &&
                    (IsThereSpace(species_after))) {
                    SplitOnAlpha(species_after,species_before,species_after);
                    if (species_before != partial_after) return nothing;
                    return species_saved;
                }
            }
            return nothing;
            
        }
        if (species_before != partial_before) {
            while ((!species_after.empty()) && (!partial_after.empty()) &&
                   (species_before != partial_before)) {
                if (IsThereSpace(species_after)){
                    SplitOnAlpha(species_after,species_before,species_after);
                }
                else
                    return nothing;
            }
            while ((!species_after.empty()) && (!partial_after.empty()) &&
                   (species_before == partial_before)) {
                if ((IsThereSpace(species_after)) &&
                    (IsThereSpace(partial_after))){
                    
                    SplitOnAlpha(species_after,species_before,species_after);
                    SplitOnAlpha(partial_after,partial_before,partial_after);
                    if (species_before != partial_before) return nothing;
                }
                if ((IsThereSpace(species_after)) &&
                    (!IsThereSpace(partial_after))){
                    SplitOnAlpha(species_after,species_before,species_after);
                    if (species_before != partial_after) return nothing;
                    
                }
                if ((!IsThereSpace(species_after)) &&
                    (IsThereSpace(partial_after))){
                    return nothing;
                }
                if ((!IsThereSpace(species_after)) &&
                    (!IsThereSpace(partial_after)) &&
                    (species_before == partial_before)) return species_saved;
            }
            
            return species_saved;
        }
    }
    return nothing;
}

// Public functions
TreeSpecies::TreeSpecies(){
    add_species("");
}

TreeSpecies::TreeSpecies (const string & species){
   add_species(species);
}

TreeSpecies(const TreeSpecies & copy_species){
    set<string> copy_species = list_of_species;
    
}

TreeSpecies::~TreeSpecies (){
    list_of_species.clear();
}

void TreeSpecies::print_all_species(ostream & out) const {
    set<string>::iterator all_species;
    for ( all_species = list_of_species.begin();
         all_species != list_of_species.end(); ++all_species) {
        out << *all_species << endl;
    }
}

int TreeSpecies::number_of_species() const {
    return list_of_species.size();
    
}

int TreeSpecies::add_species( const string & species) {
    if (list_of_species.insert(new_species).second){
        return 0;
    }
    return 1;
}

list<string> TreeSpecies::get_matching_species(const string & partial_name) const {
    
    string prtl_name = ConvertLower(partial_name);
    list<string> matching_species;
    set<string>::iterator species = list_of_species.begin();

    // if there is space, iterate thru list and match via 1,PartialWnWOSpace
    if ( !IsThereSpace(prtl_name)){
        while (species != list_of_species.end()) {
            matching_species.push_back(PartialWnWOSpace(*species,prtl_name,1));
            species++;
        }
    }
    // if there is no space, iterate thru list and match and match via 2,PartialWnWOSpace
    if (IsThereSpace(prtl_name)){
         while (species != list_of_species.end()) {
             matching_species.push_back(PartialWnWOSpace(*species,prtl_name,2));
             species++;
        }
    }
   return matching_species;
}

