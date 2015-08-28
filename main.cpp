// ===================================================================
//
// IMPORTANT: Do not make any changes to this file, except to
//            uncomment the test cases in BasicTests and
//            ExtraCreditTests as you work, and to write your own test
//            cases in StudentTests.
//
// ===================================================================

#include <iostream>
#include <cassert>
#include <string>
#include <vector> 
#include <utility>
#include <algorithm>
#include <cstdlib>

#include "bidirectional_map.h"


// prototypes of helper functions
void BasicTests();
void StudentTests();
void ExtraCreditTests();


int main() {

  BasicTests();
  StudentTests();
  ExtraCreditTests();

}


void BasicTests() {

  std::cout << "Beginning BasicTests()..." << std::endl;

  // some simple data to put in the map
  std::vector<std::string> keys;
  keys.push_back("carrot");
  keys.push_back("banana");
  keys.push_back("date");
  keys.push_back("fig");
  keys.push_back("eggplant");
  keys.push_back("apple");
  std::vector<int> values;
  values.push_back(4);
  values.push_back(5);
  values.push_back(6);
  values.push_back(2);
  values.push_back(1);
  values.push_back(3);

  // sorted versions of the input data for testing the iterators
  std::vector<std::string> sorted_keys = keys;
  std::sort(sorted_keys.begin(),sorted_keys.end());
  std::vector<int> sorted_values = values;
  std::sort(sorted_values.begin(),sorted_values.end());


  // ------------------------------------------------
  // CREATE A BIDIRECTIONAL MAP
  bidirectional_map<std::string,int> bdmap;
  assert (bdmap.size() == 0);


  // INSERT 6 SIMPLE ONE-TO-ONE ASSOCIATIONS
  // (a later test case will verify the return value of insert)
  for (int i = 0; i < 6; i++) {
    bdmap.insert(std::make_pair(keys[i],values[i])); 
  }
  assert (bdmap.size() == 6);


  // PRINT THE STRUCTURE 
  // note the formatting of this output is not strictly specified, 
  // but the data should be clearly presented
  std::cout << "created bidirectional map with 6 associations" << std::endl;
  bdmap.print(std::cout);


  // ------------------------------------------------
  
  // TEST THE SUBSCRIPT [] OPERATOR
  // verify that the associations are bidirectional
  for (int i = 0; i < 6; i++) {
    assert (bdmap[keys[i]] == values[i]);
    assert (bdmap[values[i]] == keys[i]);
  }
  std::cout << "bidirectional links verified" << std::endl;
  


  // ------------------------------------------------
  
  // TEST FIND ON KEYS
  bidirectional_map<std::string,int>::key_iterator ki; 
  for (int i = 0; i < 6; i++) {
    ki = bdmap.find(keys[i]);
    assert (ki != bdmap.key_end());
    assert ((*ki).first == keys[i]);
    assert ((*ki).second == values[i]);
  }
  ki = bdmap.find("grape");
  assert (ki == bdmap.key_end());
  // TEST FIND ON VALUES
  bidirectional_map<std::string,int>::value_iterator vi;
  for (int i = 0; i < 6; i++) {
    vi = bdmap.find(values[i]);
    assert (vi != bdmap.value_end());
    assert ((*vi).first == values[i]);
    assert ((*vi).second == keys[i]);
  }
  vi = bdmap.find(7);
  assert (vi == bdmap.value_end());
  std::cout << "find on keys and find on values successful" << std::endl;
  


  // ------------------------------------------------
    
  // FORWARD ITERATOR ON KEYS
  int counter = 0;
  for (bidirectional_map<std::string,int>::key_iterator ki = bdmap.key_begin();
       ki != bdmap.key_end(); ki++) {
    assert (sorted_keys[counter] == (*ki).first);
    std::cout << "key:" << (*ki).first << " associated with value:" << (*ki).second << std::endl;
    counter++;
  }
  // FORWARD ITERATOR ON VALUES
  counter = 0;
  for (bidirectional_map<std::string,int>::value_iterator vi = bdmap.value_begin();
       vi != bdmap.value_end(); vi++) {
    assert (sorted_values[counter] == (*vi).first);
    std::cout << "value:" << (*vi).first << " associated with key:" << (*vi).second << std::endl;
    counter++;
  }
  // BACKWARD ITERATOR ON KEYS
  counter = 5;
  ki = bdmap.find(sorted_keys[counter]);
  while (1) {
    assert ((*ki).first == sorted_keys[counter]);
    if (counter == 0) break;
    counter--;
    ki--;
  }
  // BACKWARD ITERATOR ON VALUES
  counter = 5;
  vi = bdmap.find(sorted_values[counter]);
  while (1) {
    assert ((*vi).first == sorted_values[counter]);
    if (counter == 0) break;
    counter--;
    vi--;
  }
  std::cout << "forward and backward iterators on keys and values successful" << std::endl;
  


  // ------------------------------------------------
  // TESTING THE RETURN VALUE OF INSERT
  // like the STL map, insert returns a pair with an iterator pointing
  // to the key in the map, and a bool indicating whether the element
  // was newly added, or was already there
  
  std::pair<bidirectional_map<std::string,int>::key_iterator,bool> insert_return;
  insert_return = bdmap.insert(std::make_pair("zebra",26));
  assert (insert_return.first == bdmap.find("zebra"));
  assert (insert_return.second == true);
  insert_return = bdmap.insert(std::make_pair("apple",3));
  assert (insert_return.first == bdmap.find("apple"));
  assert (insert_return.second == false);
  assert (bdmap.size() == 7);
  bdmap.print(std::cout);
  std::cout << "return value of insert correct" << std::endl;
  


  // ------------------------------------------------
  // ERASE KEY-VALUE ASSOCIATIONS FROM THE STRUCTURE
  // erase returns an integer, indicating whether the specified key
  // exists in the structure and was successfully erased
  
  assert (bdmap.size() == 7);
  int num_erased = bdmap.erase("zebra");
  assert (num_erased == 1);
  assert (bdmap.size() == 6);
  bdmap.print(std::cout);
  std::cout << "erased key:'zebra' and value:26" << std::endl;
  num_erased = bdmap.erase("carrot");
  assert (num_erased == 1);
  assert (bdmap.size() == 5);
  bdmap.print(std::cout);
  std::cout << "erased key:'carrot' and value:4" << std::endl;
  num_erased = bdmap.erase("date");
  assert (num_erased == 1);
  assert (bdmap.size() == 4);
  bdmap.print(std::cout);
  std::cout << "erased key:'date' and value:6" << std::endl;
  num_erased = bdmap.erase("grape");
  assert (num_erased == 0);
  std::cout << "erase tests valid" << std::endl;
  


  // ------------------------------------------------
  // MORE TESTING OF THE RETURN VALUE OF INSERT
  
  insert_return = bdmap.insert(std::make_pair("carrot",6));
  assert (insert_return.first == bdmap.find("carrot"));
  assert (insert_return.second == true);
  insert_return = bdmap.insert(std::make_pair("apple",3));
  assert (insert_return.first == bdmap.find("apple"));
  assert (insert_return.second == false);
  assert (bdmap.size() == 5);
  bdmap.print(std::cout);
  std::cout << "return value of insert correct" << std::endl;
  

  
  // ------------------------------------------------
  // TESTING THE FOLLOW_LINK FUNCTION
  // the follow link function can be used to "jump" from an iterator
  // on keys tree, to an iterator in the values tree (and vice versa)
  
  ki = bdmap.find("fig");
  assert (ki != bdmap.key_end());
  assert ((*ki).first == "fig");
  assert ((*ki).second == 2);
  vi = ki.follow_link();
  assert (vi != bdmap.value_end());
  assert ((*vi).first == 2);
  assert ((*vi).second == "fig");
  bidirectional_map<std::string,int>::key_iterator ki2 = vi.follow_link();
  assert (ki == ki2);
  std::cout << "follow link function successful" << std::endl;
  

  
  std::cout << "BasicTests() completed" << std::endl;
}


void StudentTests() {

  std::cout << "Beginning StudentTests()..." << std::endl;   

  //
  // Add your own test cases here
  //
  // Be sure to test:
  //   * copy constructor
  //   * assignment operator
  //   * bidirectional_maps with other data types
  //   * all corner cases of insert, find, and erase
  //

 std::cout << "StudentTests() completed" << std::endl;

}



void ExtraCreditTests() {


  // uncomment if you implement non one-to-one associations
  /*

  std::cout << "Beginning ExtraCreditTests()..." << std::endl;   


  // these tests illustrate how non one-on-one associations are
  // stored, queried, and removed from the structure


  // some simple data to put in the map
  std::vector<std::string> keys;
  keys.push_back("cat");
  keys.push_back("dog");
  keys.push_back("cat");
  keys.push_back("bird");
  keys.push_back("cat");
  keys.push_back("dog");
  keys.push_back("bird");
  std::vector<int> values;
  values.push_back(4);
  values.push_back(6);
  values.push_back(1);
  values.push_back(6);
  values.push_back(2);
  values.push_back(1);
  values.push_back(1);

  // sorted versions of the input data for testing the iterators
  std::vector<std::string> sorted_keys = keys;
  std::sort(sorted_keys.begin(),sorted_keys.end());
  std::vector<int> sorted_values = values;
  std::sort(sorted_values.begin(),sorted_values.end());


  // ------------------------------------------------  
  // INSERT NON ONE-TO-ONE ASSOCIATIONS
  // insert a number of associations, note that in this example we
  // have duplicates in both keys and values
  bidirectional_map<std::string,int> bdmap;
  for (int i = 0; i < 6; i++) {
    bdmap.insert(std::make_pair(keys[i],values[i]));
  }
  assert (bdmap.size() == 6);
  bdmap.print(std::cout);


  // FAILED INSERT
  // however, when we try to insert an association that is already in
  // the structure the insert returns false
  std::pair<bidirectional_map<std::string,int>::key_iterator,bool> insert_result;
  insert_result = bdmap.insert(std::make_pair("cat", 2));
  assert (insert_result.first == bdmap.find("cat"));
  assert (insert_result.second == false);
  assert (bdmap.size() == 6);


  // ANOTHER SUCCESSFUL INSERT 
  insert_result = bdmap.insert(std::make_pair(keys[6],values[6]));
  assert (insert_result.first == bdmap.find("bird"));
  assert (insert_result.second == true);
  assert (bdmap.size() == 7);
  bdmap.print(std::cout);
  


  // ------------------------------------------------
  // FORWARD ITERATOR ON KEYS
  std::cout << "forward iteration over keys:" << std::endl;
  unsigned int counter = 0;
  for (bidirectional_map<std::string,int>::key_iterator ki = bdmap.key_begin();
       ki != bdmap.key_end(); ki++) {
    std::cout << "  key:" << (*ki).first << " associated with value:" << (*ki).second << std::endl;
    assert ((*ki).first == sorted_keys[counter]);
    counter++;
  }
  assert (counter == bdmap.size());
  // FORWARD ITERATOR ON VALUES
  std::cout << "forward iteration over values:" << std::endl;
  counter = 0;
  for (bidirectional_map<std::string,int>::value_iterator vi = bdmap.value_begin();
       vi != bdmap.value_end(); vi++) {
    std::cout << "  value:" << (*vi).first << " associated with key:" << (*vi).second << std::endl;
    assert ((*vi).first == sorted_values[counter]);
    counter++;
  }
  assert (counter == bdmap.size());
  bdmap.print(std::cout);



  // ------------------------------------------------
  // ERASE AN ASSOCIATION
  // erase a single association between key:cat and value:4
  int num_erased = bdmap.erase("cat", 4);
  bdmap.print(std::cout);
  assert (num_erased == 1);
  assert (bdmap.size() == 6);
  std::cout << "erased key:cat and value:4" << std::endl;
  sorted_keys.erase(sorted_keys.begin()+4);
  sorted_values.erase(sorted_values.begin()+4);

  // verify iteration over keys and values
  std::cout << "forward iteration over keys:" << std::endl;
  counter = 0;
  for (bidirectional_map<std::string,int>::key_iterator ki = bdmap.key_begin();
       ki != bdmap.key_end(); ki++) {
    std::cout << "  key:" << (*ki).first << " associated with value:" << (*ki).second << std::endl;
    assert ((*ki).first == sorted_keys[counter]);
    counter++;
  }
  assert (counter == bdmap.size());
  std::cout << "forward iteration over values:" << std::endl;
  counter = 0;
  for (bidirectional_map<std::string,int>::value_iterator vi = bdmap.value_begin();
       vi != bdmap.value_end(); vi++) {
    std::cout << "  value:" << (*vi).first << " associated with key:" << (*vi).second << std::endl;
    assert ((*vi).first == sorted_values[counter]);
    counter++;
  }
  assert (counter == bdmap.size());
  bdmap.print(std::cout);


  // ------------------------------------------------
  // FAILED ERASE
  // try to erase an association that does not exist
  num_erased = bdmap.erase("bird", 2);
  assert (num_erased == 0);
  assert (bdmap.size() == 6);


  // ------------------------------------------------
  // ERASE ALL WITH SPECIFIC KEY 
  // erase all associations with "bird" as the key
  num_erased = bdmap.erase("dog");
  assert (num_erased == 2);
  assert (bdmap.size() == 4);
  bdmap.print(std::cout);
  std::cout << "erased all key:bird associations" << std::endl;
  sorted_keys.erase(sorted_keys.begin()+5);
  sorted_keys.erase(sorted_keys.begin()+4);
  sorted_values.erase(sorted_values.begin()+5);
  sorted_values.erase(sorted_values.begin()+2);

  // verify iteration over keys and values
  std::cout << "forward iteration over keys:" << std::endl;
  counter = 0;
  for (bidirectional_map<std::string,int>::key_iterator ki = bdmap.key_begin();
       ki != bdmap.key_end(); ki++) {
    std::cout << "  key:" << (*ki).first << " associated with value:" << (*ki).second << std::endl;
    assert ((*ki).first == sorted_keys[counter]);
    counter++;
  }
  assert (counter == bdmap.size());
  std::cout << "forward iteration over values:" << std::endl;
  counter = 0;
  for (bidirectional_map<std::string,int>::value_iterator vi = bdmap.value_begin();
       vi != bdmap.value_end(); vi++) {
    std::cout << "  value:" << (*vi).first << " associated with key:" << (*vi).second << std::endl;
    assert ((*vi).first == sorted_values[counter]);
    counter++;
  }
  assert (counter == bdmap.size());


  // ------------------------------------------------
  // ERASE ALL WITH SPECIFIC VALUE
  // erase all associations with 1 as the value
  num_erased = bdmap.erase(1);
  assert (num_erased == 2);
  assert (bdmap.size() == 2);
  bdmap.print(std::cout);
  std::cout << "erased all value:1 associations" << std::endl;
  bdmap.print(std::cout);
  sorted_keys.erase(sorted_keys.begin()+2);
  sorted_keys.erase(sorted_keys.begin());
  sorted_values.erase(sorted_values.begin()+1);
  sorted_values.erase(sorted_values.begin());

  // verify iteration over keys and values
  std::cout << "forward iteration over keys:" << std::endl;
  counter = 0;
  for (bidirectional_map<std::string,int>::key_iterator ki = bdmap.key_begin();
       ki != bdmap.key_end(); ki++) {
    std::cout << "  key:" << (*ki).first << " associated with value:" << (*ki).second << std::endl;
    assert ((*ki).first == sorted_keys[counter]);
    counter++;
  }
  assert (counter == bdmap.size());
  std::cout << "forward iteration over values:" << std::endl;
  counter = 0;
  for (bidirectional_map<std::string,int>::value_iterator vi = bdmap.value_begin();
       vi != bdmap.value_end(); vi++) {
    std::cout << "  value:" << (*vi).first << " associated with key:" << (*vi).second << std::endl;
    assert ((*vi).first == sorted_values[counter]);
    counter++;
  }
  assert (counter == bdmap.size());
  

  std::cout << "ExtraCreditTests() completed" << std::endl;
  */

}

