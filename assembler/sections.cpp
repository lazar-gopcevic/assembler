//
//  sectons.cpp
//  assembler
//
//  Created by Lazar Gopcevic on 20/5/17.
//  Copyright © 2017 Lazar Gopcevic. All rights reserved.
//

#include <iomanip>
#include <iostream>
#include "section.hpp"
#include "sections.hpp"
#include "relocationtableentry.hpp"
#include "keywordsutil.h"

using namespace std;

vector<Section> Sections::entries = vector<Section>();

void Sections::outputSections() {
   for (int i=0; i < Sections::entries.size(); i++) {
      if (Sections::entries[i].name.find(".bss") != string::npos) {
         continue;
      }
      cout << "#rel" << Sections::entries[i].name << endl;
      cout << setw(10) << "numID"
         << setw(10) << "address"
         << setw(10) << "type"
         << endl;
      for (int j=0; j < Sections::entries[i].relTable.entries.size(); j++) {
         RelocationTableEntry rte = Sections::entries[i].relTable.entries[j];
         cout << setw(10) << rte.numID
               << setw(10) << rte.address
               << setw(10) << rte.type
         << endl;
      }
      
      cout << Sections::entries[i].name << endl;
      
      
      for (int j=0; j < Sections::entries[i].content.size(); j++) {
         if (j%16 == 0 && j != 0) {
            cout << endl;
         }
         if (Sections::entries[i].content[j] == '?') {
            cout << "??";
         } else {
            printHexaFromChar(Sections::entries[i].content[j]);
         }
         cout << " ";
      }
      
      cout << endl;
   }
}

void Sections::outputSections(ofstream &out) {
   
   for (int i=0; i < Sections::entries.size(); i++) {
      if (Sections::entries[i].name.find(".bss") != string::npos) {
         continue;
      }
      out << "#rel" << Sections::entries[i].name << endl;
      
      for (int j=0; j < Sections::entries[i].relTable.entries.size(); j++) {
         RelocationTableEntry rte = Sections::entries[i].relTable.entries[j];
         out << "0x" << getHexStringFromInt(rte.address)
         << " " << rte.type
         << " " << rte.numID
         << endl;
      }
      
      out << Sections::entries[i].name << endl;
      
      
      for (int j=0; j < Sections::entries[i].content.size(); j++) {
         if (j%16 == 0 && j != 0) {
            out << endl;
         }
         if (Sections::entries[i].content[j] == '?') {
            out << "??";
         } else {
            out << getHexFromChar(Sections::entries[i].content[j]);
         }
         out << " ";
      }
      
      out << endl;
   }
}
