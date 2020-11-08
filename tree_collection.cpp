/*******************************************************************************
 Title          : tree_collection.cpp
 Author         : Stewart Weiss
 Created on     : February  16, 2019
 Description    : The interface file for the TreeCollection class
 Purpose        : To provide a collection of trees.
 Usage          :
 Build with     : g++ -Wall -Wpedantic -Werror -g tree_collection.cpp -o treecol
 treecollection
 Modifications  :
 
 *******************************************************************************/

#include "tree_collection.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

//Helper Functions


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
/** UpdateBorough(string & boro_
 *  takes in a boro and update count by one
 *  @param str [in]
 */
void TreeCollection::UpdateBorough(string boro, string species){
    if (boro =="Manhattan" ){
        list_of_boroughs[0].count++;
        for (vector<everySpecies>::iterator a_species = list_of_boroughs[0].boro_name_cnt.begin();
             a_species != species_with_count.end(); a_species++ ) {
            if (species != a_species->species_name) {
                everySpecies new_specs = {species,1};
                boro_name_cnt.push_back(new_specs);
            }
            if (species == a_species->species_name) {
                a_species->num_of_this_species++;
            }
        }
    }
    if (boro =="Bronx"){
        list_of_boroughs[1].count++;
        for (vector<everySpecies>::iterator a_species = list_of_boroughs[1].boro_name_cnt.begin();
             a_species != species_with_count.end(); a_species++ ) {
            if (species != a_species->species_name) {
                everySpecies new_specs = {species,1};
                boro_name_cnt.push_back(new_specs);
            }
            if (species == a_species->species_name) {
                a_species->num_of_this_species++;
            }
        }
    }
    if (boro =="Brooklyn"){
        list_of_boroughs[2].count++;
        for (vector<everySpecies>::iterator a_species = list_of_boroughs[2].boro_name_cnt.begin();
             a_species != species_with_count.end(); a_species++ ) {
            if (species != a_species->species_name) {
                everySpecies new_specs = {species,1};
                boro_name_cnt.push_back(new_specs);
            }
            if (species == a_species->species_name) {
                a_species->num_of_this_species++;
            }
        }
    }
    if (boro =="Queens"){
        list_of_boroughs[3].count++;
        for (vector<everySpecies>::iterator a_species = list_of_boroughs[3].boro_name_cnt.begin();
             a_species != species_with_count.end(); a_species++ ) {
            if (species != a_species->species_name) {
                everySpecies new_specs = {species,1};
                boro_name_cnt.push_back(new_specs);
            }
            if (species == a_species->species_name) {
                a_species->num_of_this_species++;
            }
        }
    }
    if (boro =="Staten Island"){
        list_of_boroughs[4].count++;
        for (vector<everySpecies>::iterator a_species = list_of_boroughs[4].boro_name_cnt.begin();
             a_species != species_with_count.end(); a_species++ ) {
            if (species != a_species->species_name) {
                everySpecies new_specs = {species,1};
                boro_name_cnt.push_back(new_specs);
            }
            if (species == a_species->species_name) {
                a_species->num_of_this_species++;
            }
        }
    }
}
double haversine ( double lat1 , double lon1 , double lat2 , double lon2 ) {
    const double R = 6372.8 ;// radius of earth in km
    const double TO_RAD = M_PI / 180.0; // conversion of degrees to rads
    lat1 =TO_RAD * lat1;
    lat2 =TO_RAD * lat2;
    lon1 =TO_RAD * lon1;
    lon2 =TO_RAD * lon2;
    double dLat = (lat2 - lat1)/2;
    double dLon = (lon2 - lon1)/2;
    double a = sin(dLat);
    double b = sin(dLon);
    return 2 * R * asin(sqrt(a * a + cos(lat1) * cos(lat2) * b * b));
}
//Public Function

TreeCollection::TreeCollection () : root(nullptr) , AvlTree() {

}

TreeCollection::TreeCollection (Tree & all_trees): AvlTree<Tree>(all_trees) {
    add_tree(all_trees);
}

TreeCollection::~TreeCollection (){
    all_trees.makeEmpty();
    all_species.clear();
    boro_name_cnt.clear();
    species_with_count.clear();
    tree_counter = 0;
    for (int i = 0; i < 5; i++) list_of_boroughs[i].count = 0;
}

void TreeCollection::CountEverySpecies(const string & species){
    set<string>::iterator a_species;
    for ( a_species = all_species.begin();
         a_species != all_species.end(); ++a_species) {
        for (int i = 0; i < species_with_count.size(); i++) {
            if (species == *a_species) {
                species_with_count[i].num_of_this_species +=1;
            }
            if ((species == *a_species) && (species_with_count.empty())){
                everySpecies new_species = {species, 1};
                species_with_count.push_back(new_species);
            }
        }
    }
}

int TreeCollection::total_tree_count(){
    return tree_counter;
}

int TreeCollection::count_of_tree_species ( const string & species_name ) {
    for (vector<everySpecies>::iterator a_species = species_with_count.begin();
         a_species != species_with_count.end(); a_species++ ) {
        if (species_name == a_species->species_name)
            return a_species->num_of_this_species;
    }
    return 0 ;;
}

int TreeCollection::count_of_tree_species_in_boro ( const string & species_name,
                                                   const string & boro_name ){
    if (boro_name == "Manhattan"){
        list_of_boroughs[0].count++;
        for (vector<everySpecies>::iterator a_species = list_of_boroughs[0].boro_name_cnt.begin();
             a_species != species_with_count.end(); a_species++ ) {
            if (species_name == a_species->species_name) {
                return a_species->num_of_this_species;
            }
        }
    }
    
    
    if (boro_name =="Bronx"){
        list_of_boroughs[1].count++;
        for (vector<everySpecies>::iterator a_species = list_of_boroughs[1].boro_name_cnt.begin();
             a_species != species_with_count.end(); a_species++ ) {
            if (species_name == a_species->species_name) {
                return a_species->num_of_this_species;
            }
        }
    }
    if (boro_name =="Brooklyn"){
        list_of_boroughs[2].count++;
        for (vector<everySpecies>::iterator a_species = list_of_boroughs[2].boro_name_cnt.begin();
             a_species != species_with_count.end(); a_species++ ) {
            if (species_name == a_species->species_name) {
                return a_species->num_of_this_species;
            }
        }
    }
    if (boro_name =="Queens"){
        list_of_boroughs[3].count++;
        for (vector<everySpecies>::iterator a_species = list_of_boroughs[3].boro_name_cnt.begin();
             a_species != species_with_count.end(); a_species++ ) {
            if (species_name == a_species->species_name) {
                return a_species->num_of_this_species;
            }
        }
    }
    if (boro_name =="Staten Island") {
        list_of_boroughs[4].count++;
        for (vector<everySpecies>::iterator a_species = list_of_boroughs[4].boro_name_cnt.begin();
             a_species != species_with_count.end(); a_species++ ) {
            if (species_name == a_species->species_name) {
                return a_species->num_of_this_species;
            }
        }
    }
//    if (boro_name == "Manhattan"){
//        set<string>::iterator a_species;
//        for ( a_species = all_species.begin(); a_species !=
//             all_species.end();  ++a_species) {
//            if(all_trees.find(boro_name) == boro_name){
//                counter++;
//            }
//        }
//        return counter;
//    }
//    if (boro_name == "Bronx"){
//        set<string>::iterator a_species;
//        for ( a_species = all_species.begin(); a_species !=
//             all_species.end();  ++a_species) {
//            if(all_trees.find(boro_name) == boro_name){
//                counter++;
//            }
//        }
//        return counter;
//    }
//
//    if (boro_name =="Brooklyn"){
//        set<string>::iterator a_species;
//        for ( a_species = all_species.begin(); a_species !=
//             all_species.end();  ++a_species) {
//            if(all_trees.find(boro_name) == boro_name){
//                counter++;
//            }
//        }
//        return counter;
//
//    }
//    if (boro_name =="Queens"){
//        set<string>::iterator a_species;
//        for ( a_species = all_species.begin(); a_species !=
//             all_species.end();  ++a_species) {
//            if(all_trees.find(boro_name) == boro_name){
//                counter++;
//            }
//        }
//        return counter;
//    }
//    if (boro_name =="Staten Island") {
//        set<string>::iterator a_species;
//        for ( a_species = all_species.begin(); a_species !=
//             all_species.end();  ++a_species) {
//            if(all_trees.find(boro_name) == boro_name){
//                counter++;
//            }
//        }
//        return counter;
//    }
    return 0;
}


/** get_counts_of_trees_by_boro(s,t) puts number of trees matching name s
 *                                     in all boros into param t
 * @note This puts the number of Tree objects in the collection whose
 *       spc_common name matches the species_name specified by
 *       parameter s into the boro_name array.
 *       This method is case insensitive.
 *       If the method is called with a non-existent species s,
 *       the return value should be 0.
 * @param  string species_name [in] species name to search for
 * @param  boro boro_name[5] [in,out] array of boro structures
 * @pre    boro_name[k].count ==0 for k = 0,...,4 and
 *         boro_name[k].name is initialized with boro name[k]
 * @post   boro_name[k].count has count of trees of given species in boro[k]
 * @return int the total number of trees of given species in all boros
 */
int TreeCollection::get_counts_of_trees_by_boro ( const string & species_name,
                                                 boro tree_count[5] ){
    for (vector<everySpecies>::iterator a_species =
         list_of_boroughs[0].boro_name_cnt.begin();
        a_species != species_with_count.end(); a_species++ ) {
        if (species_name == a_species->species_name) {
            tree_count[0].count += a_species->num_of_this_species;
            }
        }
    
    
    for (vector<everySpecies>::iterator a_species =
         list_of_boroughs[1].boro_name_cnt.begin();
         a_species != species_with_count.end(); a_species++ ) {
        if (species_name == a_species->species_name) {
            tree_count[1].count += a_species->num_of_this_species;
        }
    }
    for (vector<everySpecies>::iterator a_species =
         list_of_boroughs[2].boro_name_cnt.begin();
         a_species != species_with_count.end(); a_species++ ) {
        if (species_name == a_species->species_name) {
            tree_count[2].count += a_species->num_of_this_species;
        }
    }
    for (vector<everySpecies>::iterator a_species =
         list_of_boroughs[3].boro_name_cnt.begin();
         a_species != species_with_count.end(); a_species++ ) {
        if (species_name == a_species->species_name) {
            tree_count[3].count += a_species->num_of_this_species;
        }
    }
    for (vector<everySpecies>::iterator a_species =
         list_of_boroughs[4].boro_name_cnt.begin();
         a_species != species_with_count.end(); a_species++ ) {
        if (species_name == a_species->species_name) {
            tree_count[4].count += a_species->num_of_this_species;
        }
    }
    return tree_count[5].count;
}

int TreeCollection::count_of_trees_in_boro( const string & boro_name ){
    if (boro_name =="Manhattan" )    return list_of_boroughs[0].count;
    if (boro_name =="Bronx")         return list_of_boroughs[1].count;
    if (boro_name =="Brooklyn")      return list_of_boroughs[2].count;
    if (boro_name =="Queens")        return list_of_boroughs[3].count;
    if (boro_name =="Staten Island") return list_of_boroughs[4].count;
    return 0;
}

int TreeCollection::add_tree( Tree & new_tree) {
    if (all_trees.isEmpty()){
        all_trees.insert(new_tree);
        UpdateBorough(new_tree.borough_name(),new_tree.common_name());
        if((list_of_species.add_species(new_tree.common_name())) == 1){
            tree_counter +=1;
            return 1;
        }
    }
    if((((all_trees.find(new_tree.common_name(), *root))) == new_tree.common_name()) && ((list_of_species.add_species(new_tree.common_name())) == 1)){
            all_trees.insert(new_tree);
            tree_counter +=1;
            UpdateBorough(new_tree.borough_name(),new_tree.common_name());
            return 1;
    }
    return 0;
}
                
void TreeCollection::print_all_species(ostream & out) const {
    list_of_species.print_all_species(out);
}
                
void TreeCollection::print(ostream & out ) const {
    all_trees.printTree();
}
                
list<string> TreeCollection::get_matching_species(const string & species_name)
const{
    string species = ConvertLower(species_name);
    return list_of_species.get_matching_species(species);
}
list<string> TreeCollection::get_all_in_zipcode(int zipcode) const{
    list<string> matches;
//    if (all_trees.find(&zipcode)==zipcode){
// if there is a match , add to list then search again
//        }
        return matches;

}

list<string> TreeCollection::get_all_near(double latitude, double longitude,
                                                    double  distance) const {
    
    list<string> matches;
    return matches;
                    
}
