// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>  
#include <fstream>  
using namespace std;
#include "heroskin.pb.h"



int main(int args, char* argv[]) {
	fstream input("heroskin_c_new.dat", ios::in | ios::binary);
	fstream input_old("heroskin_c_old.dat", ios::in | ios::binary);
	fstream output("heroskin_c.dat", ios::out | ios::trunc | ios::binary);
	heroskin_c skins, skins_old;
	skins.ParseFromIstream(&input);
	skins_old.ParseFromIstream(&input_old);


	for (int i = skins_old.skins_size(); i < skins.skins_size(); i++) {
		heroskin* skin = skins_old.add_skins();

		char temp[256];
		strcpy_s(temp, skins.skins(i).resource().c_str());
		char* pos = strstr(temp, "_.png");
		if (pos) {
			strcpy_s(pos, sizeof(temp) - (pos - (char *)&temp), ".dds");
		}

		skins.mutable_skins(i)->set_resource(temp);

		skin->CopyFrom(skins.skins(i));

		
		cout << skin->DebugString() << endl;

		if (skin->hero_index() == 191 && skin->skin_index() == 1)
		{
			skin->set_head_img_pos("221;0");
			skin->set_head_img_wh("357;640");

			skin->set_box_pos("295;23");
			skin->set_box_wh("161;161");
			skin->set_card_pos("221;14");
			skin->set_card_wh("357;625");
		}

		//cout << skin->hero_index() << endl;

		//cout << skin->resource() << endl;
	}

	if (!skins_old.SerializeToOstream(&output)) {
		cerr << "Failed to write msg." << endl;
		return -1;
	}

	cout << "Write to file: " << "heroskin_c.dat" << " successfully" << endl; 

	output.flush();

	/*heroskin_c skins;
	fstream input("heroskin_c.dat", ios::in | ios::binary);
	skins.ParseFromIstream(&input);
	printf("%d\n", skins.skins_size());
	for (int i = 0; i < skins.skins_size(); i++)
	{
		char temp[256];
		strcpy_s(temp, skins.skins(i).resource().c_str());
		char* pos = strstr(temp, "_.png");
		if (pos) {
			strcpy_s(pos, sizeof(temp)-(pos - (char *)&temp) , ".dds");
		}

		skins.mutable_skins(i)->set_resource(temp);

		cout << skins.skins(i).resource() << endl;
	}

	fstream output("test.dat", ios::out | ios::trunc | ios::binary);

	if (!skins.SerializeToOstream(&output)) {
		cerr << "Failed to write msg." << endl;
		return -1;
	}

	cout << "Write to file: " << "test.dat" << " successfully" << endl;*/
}