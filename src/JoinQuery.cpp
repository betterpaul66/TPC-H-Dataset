#include "JoinQuery.hpp"
#include <assert.h>
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <unordered_set>

//---------------------------------------------------------------------------
JoinQuery::JoinQuery(std::string lineitem, std::string order,
                     std::string customer)
{
   this->tableStr[0] = lineitem;
   this->tableStr[1] = customer;
   this->tableStr[2] = order;
}

size_t JoinQuery::avg(std::string segmentParam)
{
   int j = 0;
   double sumq = 0;
   double result;

   std::string lineitem = this->tableStr[0];
   std::string customer = this->tableStr[1];
   std::string order = this->tableStr[2];


   std::string oline;
   std::string cline;
   std::string lline;


  std::ifstream c(customer);
  std::unordered_set<std::string> Custkey; // !!!use unordered_set for customer key to achieve O(1) complexity join!!!
   
  while (std::getline(c, cline, '\n')) {
		
	  if (cline.find(segmentParam) != std::string::npos) //look up the input customer segment
	  {
        	std::size_t c_cize1 = cline.find("|", 0);
        	Custkey.insert(cline.substr(0, c_cize1)); //return the customer key
	  }

   }


 


   std::ifstream o(order);
   std::unordered_set<std::string> Orderkey;
  while (std::getline(o, oline, '\n')) {
      
	  	std::size_t o_oize1 = oline.find("|", 0);
    
      	  	std::string keyo = oline.substr(0, o_oize1);
         
      	   	std::size_t o_oize2 = oline.find("|", o_oize1+1); // lookup the customer key
      		std::string keyc = oline.substr(o_oize1 + 1, o_oize2-o_oize1-1);
       
      		if (Custkey.find(keyc) != Custkey.end())
	  	{ 
		  Orderkey.insert(keyo); // return order key
          
         
	  	}
   }

 
    std::ifstream l(lineitem);
    while (std::getline(l, lline, '\n')) {

		
		std::size_t l_lize1 = lline.find("|", 0); // lookup the order key
        	std::string keyo = lline.substr(0, l_lize1); 
		
		std::size_t l_lize2 = lline.find("|", l_lize1+1);
        	std::size_t l_lize3 = lline.find("|", l_lize2+1);
        	std::size_t l_lize4 = lline.find("|", l_lize3+1);
        	std::size_t l_lize5 = lline.find("|", l_lize4 + 1);
        	std::string valuel = lline.substr(l_lize4 + 1, l_lize5 - l_lize4 - 1);
        
       		 if (Orderkey.find(keyo) != Orderkey.end()) 
		 	{ 
			sumq += std::stod(valuel); //return the sum 
           		++j; //return the count
			}
		}

      
   result = sumq / j * 100; //calculate average
   return result;
}
//---------------------------------------------------------------------------
size_t JoinQuery::lineCount(std::string rel)
{
   std::ifstream relation(rel);
   assert(relation);  // make sure the provided string references a file
   size_t n = 0;
   for (std::string line; std::getline(relation, line);) n++;
   return n;
}
//---------------------------------------------------------------------------
