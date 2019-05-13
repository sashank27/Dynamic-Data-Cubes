#include <bits/stdc++.h>
using namespace std;

//////////////////// DIMENSIONS ///////////////////////

double dim_type_3 = 4096;
double dim_type_2 = 1024;
double dim_type_1 = 256;

double matrix_size = 65536;

string star_details = "star";
string neighbour_details = "neighbour";

///////////////////// DEFINE A POINT ///////////////////

struct Point{

	double x;
	double y;
	double z;

};

//////////////////// DEFINE A STAR /////////////////////

struct Star{

	Point pos;
	string name;

};

//////////////////// DEFINE A CUBE //////////////////////

struct cube_core{

	int num_stars;
	vector < Point > neighbours_type1;
	vector < Point > neighbours_type2;
	vector < Point > neighbours_type3;

};

struct cube_data{

	vector < Star > stars;

};

/////////////////// COMPARATORS ////////////////////////////////

struct cube_id_cmp{

	bool operator()(const Point& a, const Point& b) const{
        if(a.x != b.x){
        	return (a.x < b.x);
        }
        else if(a.y != b.y){
        	return (a.y < b.y);
        }
        else{
        	return (a.z < b.z);
        }
    }

};

/////////////////// HELPER Data Structures ///////////////////////

vector < Star > input_data;

map < Point, int, cube_id_cmp > m3;
cube_core core_3[4100];
cube_data data_3[4100];

map < Point, int, cube_id_cmp > m2;
cube_core core_2[4100];
cube_data data_2[4100];

map < Point, int, cube_id_cmp > m1;
cube_core core_1[4100];
cube_data data_1[4100];

int total_stars = 0;

/////////////////// HELPER Functions ////////////////////////////

Point get_cube_id(double x, double y, double z, double dimension){

	double x1 = x / dimension;
	double y1 = y / dimension;
	double z1 = z / dimension;
	x1 = floor(x1);
	y1 = floor(y1);
	z1 = floor(z1);
	Point ret;
	ret.x = x1 * dimension;
	ret.y = y1 * dimension;
	ret.z = z1 * dimension;
	return ret;
	
}

int get_cube_type(double x, double y, double z, double dim1, double dim2, double dim3){

	int type = -1;

	if(dim3 != -1){

		Point ID = get_cube_id(x, y, z, dim3);
		if(m3.find(ID) != m3.end()){
			type = 3;
		}

	}

	if(dim2 != -1){

		Point ID = get_cube_id(x, y, z, dim2);
		if(m2.find(ID) != m2.end()){
			type = 2;
		}

	}

	if(dim1 != -1){

		Point ID = get_cube_id(x, y, z, dim1);
		if(m1.find(ID) != m1.end()){
			type = 1;
		}

	}

	return type;

}

////////////////// INITIALIZE CUBES - ASSIGN ID'S /////////////////

void initialize_cubes_type_3(int dimension){

	int id = 0;

	for(double i = -32768; i < 32768; i += 4096){
		for(double j = -32768; j < 32768; j += 4096){
			for(double k = -32768; k < 32768; k += 4096){
				Point ID = get_cube_id(i, j, k, dim_type_3);
				m3[ID] = ++id;
			}
		}
	}

}

void initialize_cubes_type_2(int dimension){

	int id = 0;

	for(double i = -8192; i < 8192; i += 1024){
		for(double j = -8192; j < 8192; j += 1024){
			for(double k = -8192; k < 8192; k += 1024){
				Point ID = get_cube_id(i, j, k, dim_type_2);
				m2[ID] = ++id;
			}
		}
	}

}

void initialize_cubes_type_1(int dimension){

	int id = 0;

	for(double i = -2048; i < 2048; i += 256){
		for(double j = -2048; j < 2048; j += 256){
			for(double k = -2048; k < 2048; k += 256){
				Point ID = get_cube_id(i, j, k, dim_type_1);
				m1[ID] = ++id;
			}
		}
	}

}

//////////////// GET DIRECTIONS ///////////////////////////////

void assign_directions_type_3(){

	for(auto it = m3.begin(); it != m3.end(); it++){

		int idx = it -> second;
		Point ID = it -> first;
		Point P = ID;
		double dim = dim_type_3;

		cube_core C;
		int counter = 0;

		for(double i = P.x - dim; i <= P.x + dim; i += dim){
			for(double j = P.y - dim; j <= P.y + dim; j += dim){
				for(double k = P.z - dim; k <= P.z + dim; k += dim){

					if(i == P.x && j == P.y && k == P.z){
						continue;
					}

					Point new_id;
					new_id.x = i;
					new_id.y = j;
					new_id.z = k;

					if(m3.find(new_id) != m3.end()){
						core_3[idx].neighbours_type3.push_back(new_id);
					}

				}
			}
		}

	}

}

void assign_directions_type_2(){

	for(auto it = m2.begin(); it != m2.end(); it++){

		int idx = it -> second;
		Point ID = it -> first;
		Point P = ID;
		double dim = dim_type_2;

		cube_core C;
		int counter = 0;

		for(double i = P.x - dim; i <= P.x + dim; i += dim){
			for(double j = P.y - dim; j <= P.y + dim; j += dim){
				for(double k = P.z - dim; k <= P.z + dim; k += dim){

					if(i == P.x && j == P.y && k == P.z){
						continue;
					}

					Point new_id;
					new_id.x = i;
					new_id.y = j;
					new_id.z = k;

					if(m2.find(new_id) != m2.end()){
						core_2[idx].neighbours_type2.push_back(new_id);
					}

				}
			}
		}

	}

}

void assign_directions_type_1(){

	for(auto it = m1.begin(); it != m1.end(); it++){

		int idx = it -> second;
		Point ID = it -> first;
		Point P = ID;
		double dim = dim_type_1;

		cube_core C;
		int counter = 0;

		for(double i = P.x - dim; i <= P.x + dim; i += dim){
			for(double j = P.y - dim; j <= P.y + dim; j += dim){
				for(double k = P.z - dim; k <= P.z + dim; k += dim){

					if(i == P.x && j == P.y && k == P.z){
						continue;
					}

					Point new_id;
					new_id.x = i;
					new_id.y = j;
					new_id.z = k;

					if(m1.find(new_id) != m1.end()){
						core_1[idx].neighbours_type1.push_back(new_id);
					}

				}
			}
		}

	}

}

/////////////////////// HETEROGENOUS EDGE LINKAGE /////////////////////

void link_type_2_type_3(double dim2, double dim3){

	for(auto it = m2.begin(); it != m2.end(); it++){

		Point ID = it -> first;
		int idx = it -> second;


		if(core_2[idx].neighbours_type2.size() < 26){
			for(int i = ID.x - dim2; i <= ID.x + dim2; i += dim2){
				for(int j = ID.y - dim2; j <= ID.y + dim2; j += dim2){
					for(int k = ID.z - dim2; k <= ID.z + dim2; k += dim2){

						

						if(i == ID.x && j == ID.y && k == ID.z){
							continue;
						}

						if(get_cube_type(i, j, k, -1, dim_type_2, dim_type_3) == 3){
							
							Point N;
							N.x = i;
							N.y = j;
							N.z = k;
							core_2[idx].neighbours_type3.push_back(N);

							Point ID_3 = get_cube_id(i, j, k, dim_type_3);
							auto it_3 = m3.find(ID_3);
							int idx_3 = it_3 -> second;
							core_3[idx_3].neighbours_type2.push_back(ID);

						}

					}
				}
			}

		}

	}

}

void link_type_1_type_2(double dim1, double dim2){

	for(auto it = m1.begin(); it != m1.end(); it++){

		Point ID = it -> first;
		int idx = it -> second;


		if(core_1[idx].neighbours_type1.size() < 26){

			for(int i = ID.x - dim1; i <= ID.x + dim1; i += dim1){
				for(int j = ID.y - dim1; j <= ID.y + dim1; j += dim1){
					for(int k = ID.z - dim1; k <= ID.z + dim1; k += dim1){

						if(i == ID.x && j == ID.y && k == ID.z){
							continue;
						}

						if(get_cube_type(i, j, k, dim_type_1, dim_type_2, dim_type_3) == 2){

							Point N;
							N.x = i;
							N.y = j;
							N.z = k;
							core_1[idx].neighbours_type2.push_back(N);

							Point ID_2 = get_cube_id(i, j, k, dim_type_2);
							auto it_2 = m2.find(ID_2);
							int idx_2 = it_2 -> second;
							core_2[idx_2].neighbours_type1.push_back(ID);

						}

					}
				}
			}

		}

	}

}

//////////////////////// DATASET INPUT //////////////////////////

string number_to_string(int num){
	string s = "";
	int temp = num / 10;
	if(temp == 1){
		s.push_back('1');
	}
	else if(temp == 2){
		s.push_back('2');
	}
	temp = num % 10;
	char c = temp + '0';
	s.push_back(c);
	return s;
}

void ParseLine(string line){

	vector <string> v;
	string s = "";
	for(int i = 0; i < line.size(); i++){

		if(line[i] == ','){
			v.push_back(s);
			s = "";
		}
		else{
			s.push_back(line[i]);
		}

	}

	v.push_back(s);

	Star temp;
	temp.pos.x = stod(v[2]);
	temp.pos.y = stod(v[3]);
	temp.pos.z = stod(v[4]);

	int type = get_cube_type(temp.pos.x, temp.pos.y, temp.pos.z, dim_type_1, dim_type_2, dim_type_3);

	if(type != -1){
		input_data.push_back(temp);
	}

}

void scan_file(string filepath){

	ifstream fin;
	fin.open(filepath);
	string line;

	while(getline(fin, line)){

		ParseLine(line);
		total_stars++;

	}

	fin.close();
}

void get_input(){

	string filepath = "../dataset/processed/outputly";

	for(int i = 0; i <= 15; i++){

		string filename = filepath + number_to_string(i) + ".csv";
		scan_file(filename);

	}

}

void fit_data(){

	for(int i = 0; i < input_data.size(); i++){

		int type = get_cube_type(input_data[i].pos.x, input_data[i].pos.y, input_data[i].pos.z, dim_type_1, dim_type_2, dim_type_3);
		int idx = -1;
		if(type == 1){
			Point ID = get_cube_id(input_data[i].pos.x, input_data[i].pos.y, input_data[i].pos.z, dim_type_1);
			auto it = m1.find(ID);
			idx = it -> second;
			data_1[idx].stars.push_back(input_data[i]);
		}
		else if(type == 2){
			Point ID = get_cube_id(input_data[i].pos.x, input_data[i].pos.y, input_data[i].pos.z, dim_type_2);
			auto it = m2.find(ID);
			idx = it -> second;
			data_2[idx].stars.push_back(input_data[i]);
		}
		else if(type == 3){
			Point ID = get_cube_id(input_data[i].pos.x, input_data[i].pos.y, input_data[i].pos.z, dim_type_3);
			auto it = m3.find(ID);
			idx = it -> second;
			data_3[idx].stars.push_back(input_data[i]);
		}

	}

}

//////////////////////// WRITE TO FILES /////////////////////////

void write_star_details(){

	cout<<"BEGIN WRITING"<<endl<<endl;

	ofstream fout;
	string line;

	int counter = 0;
	int curr = 0;

	string file_name = star_details + "_" + number_to_string(curr) + ".csv";
	fout.open(file_name, ios::app);

	cout<<"WRITING "<<file_name<<endl; 

	for(int i = 0; i < input_data.size(); i++){

	 	int type = get_cube_type(input_data[i].pos.x, input_data[i].pos.y, input_data[i].pos.z, dim_type_1, dim_type_2, dim_type_3);
		Point ID;
		if(type == 1){
			ID = get_cube_id(input_data[i].pos.x, input_data[i].pos.y, input_data[i].pos.z, dim_type_1);
		}
		else if(type == 2){
			Point ID = get_cube_id(input_data[i].pos.x, input_data[i].pos.y, input_data[i].pos.z, dim_type_2);
		}
		else if(type == 3){
			Point ID = get_cube_id(input_data[i].pos.x, input_data[i].pos.y, input_data[i].pos.z, dim_type_3);
		}

		counter++;

		fout<<input_data[i].pos.x<<','<<input_data[i].pos.y<<','<<input_data[i].pos.z<<','<<type<<","<<ID.x<<','<<ID.y<<','<<ID.z<<endl;

		if(counter % (int)1e5 == 0){
			curr++;
			fout.close();
			file_name = star_details + "_" + number_to_string(curr) + ".csv";
			cout<<"WRITING "<<file_name<<endl; 
			fout.open(file_name, ios::app);
		}

	}

}

void write_neighbours(){

	ofstream fout;
	string file_name = neighbour_details + "_" + number_to_string(1) + ".csv";
	fout.open(file_name, ios::app);

	cout<<"WRITING "<<file_name<<endl; 

	for(auto it = m1.begin(); it != m1.end(); it++){

		map < Point, int, cube_id_cmp > m;

		Point ID = it -> first;
		int type = get_cube_type(ID.x, ID.y, ID.z, dim_type_1, dim_type_2, dim_type_3);
		assert(type == 1);

		int idx = it -> second;

		for(int i = 0; i < core_1[idx].neighbours_type1.size(); i++){
			auto temp_it = m.find(core_1[idx].neighbours_type1[i]);
			if(temp_it == m.end()){
				Point ID1 = core_1[idx].neighbours_type1[i];
				m[ID1] = 1;
				fout<<ID.x<<','<<ID.y<<','<<ID.z<<','<<1<<','<<ID1.x<<','<<ID1.y<<','<<ID1.z<<','<<1<<endl;
			}
		}

		for(int i = 0; i < core_1[idx].neighbours_type2.size(); i++){
			auto temp_it = m.find(core_1[idx].neighbours_type2[i]);
			if(temp_it == m.end()){
				Point ID1 = core_1[idx].neighbours_type1[i];
				m[ID1] = 1;
				fout<<ID.x<<','<<ID.y<<','<<ID.z<<','<<1<<','<<ID1.x<<','<<ID1.y<<','<<ID1.z<<','<<2<<endl;

			}
		}

		assert(core_1[idx].neighbours_type3.size() == 0);

	}

	fout.close();

	file_name = neighbour_details + "_" + number_to_string(2) + ".csv";
	fout.open(file_name, ios::app);

	cout<<"WRITING "<<file_name<<endl; 

	for(auto it = m2.begin(); it != m2.end(); it++){

		map < Point, int, cube_id_cmp > m;

		Point ID = it -> first;
		int type = get_cube_type(ID.x, ID.y, ID.z, dim_type_1, dim_type_2, dim_type_3);
	
		if(type == 2){

			int idx = it -> second;

			for(int i = 0; i < core_2[idx].neighbours_type2.size(); i++){
				auto temp_it = m.find(core_2[idx].neighbours_type2[i]);
				if(temp_it == m.end()){
					Point ID1 = core_2[idx].neighbours_type2[i];
					m[ID1] = 1;
					fout<<ID.x<<','<<ID.y<<','<<ID.z<<','<<2<<','<<ID1.x<<','<<ID1.y<<','<<ID1.z<<','<<2<<endl;
				}
			}

			for(int i = 0; i < core_2[idx].neighbours_type1.size(); i++){
				auto temp_it = m.find(core_2[idx].neighbours_type1[i]);
				if(temp_it == m.end()){
					Point ID1 = core_2[idx].neighbours_type1[i];
					m[ID1] = 1;
					fout<<ID.x<<','<<ID.y<<','<<ID.z<<','<<2<<','<<ID1.x<<','<<ID1.y<<','<<ID1.z<<','<<1<<endl;

				}
			}

			for(int i = 0; i < core_2[idx].neighbours_type3.size(); i++){
				auto temp_it = m.find(core_2[idx].neighbours_type3[i]);
				if(temp_it == m.end()){
					Point ID1 = core_2[idx].neighbours_type3[i];
					m[ID1] = 1;
					fout<<ID.x<<','<<ID.y<<','<<ID.z<<','<<2<<','<<ID1.x<<','<<ID1.y<<','<<ID1.z<<','<<3<<endl;

				}
			}

		}

	}

	fout.close();

	file_name = neighbour_details + "_" + number_to_string(3) + ".csv";
	fout.open(file_name, ios::app);

	cout<<"WRITING "<<file_name<<endl; 

	for(auto it = m3.begin(); it != m3.end(); it++){

		map < Point, int, cube_id_cmp > m;

		Point ID = it -> first;
		int type = get_cube_type(ID.x, ID.y, ID.z, dim_type_1, dim_type_2, dim_type_3);
	
		if(type == 3){

			int idx = it -> second;

			for(int i = 0; i < core_3[idx].neighbours_type3.size(); i++){
				auto temp_it = m.find(core_3[idx].neighbours_type3[i]);
				if(temp_it == m.end()){
					Point ID1 = core_3[idx].neighbours_type3[i];
					m[ID1] = 1;
					fout<<ID.x<<','<<ID.y<<','<<ID.z<<','<<3<<','<<ID1.x<<','<<ID1.y<<','<<ID1.z<<','<<3<<endl;
				}
			}

			for(int i = 0; i < core_3[idx].neighbours_type2.size(); i++){
				auto temp_it = m.find(core_3[idx].neighbours_type2[i]);
				if(temp_it == m.end()){
					Point ID1 = core_3[idx].neighbours_type2[i];
					m[ID1] = 1;
					fout<<ID.x<<','<<ID.y<<','<<ID.z<<','<<3<<','<<ID1.x<<','<<ID1.y<<','<<ID1.z<<','<<2<<endl;

				}
			}

			assert(core_3[idx].neighbours_type1.size() == 0);

		}

	}

	fout.close();

}

void write_data(){

	cout<<endl<<".......... WRITING DATA .........."<<endl<<endl;

	write_star_details();
	write_neighbours();

	cout<<endl<<".......... OPERATION COMPLETE .........."<<endl;

}

/////////////////////// DRIVER CODE /////////////////////////////

int main(){

	cout<<".......... CUBE GENERATION .........."<<endl;

	cout<<endl<<"GENERATING CUBES OF TYPE 3"<<endl;

	initialize_cubes_type_3(dim_type_3);
	assign_directions_type_3();

	cout<<"GENERATING CUBES OF TYPE 2"<<endl;

	initialize_cubes_type_2(dim_type_2);
	assign_directions_type_2();

	cout<<"LINKING TYPES 2 and 3"<<endl;

	link_type_2_type_3(dim_type_2, dim_type_3);

	cout<<"GENERATING CUBES OF TYPE 1"<<endl;

	initialize_cubes_type_1(dim_type_1);
	assign_directions_type_1();

	cout<<"LINKING TYPES 1 and 2"<<endl;

	link_type_1_type_2(dim_type_1, dim_type_2);

	cout<<endl<<".......... CUBES GENERATED .........."<<endl;

	cout<<endl<<".......... LOADING RAW DATA .........."<<endl;

	get_input();

	cout<<endl<<".......... DATA LOADED .........."<<endl;

	cout<<endl<<".......... MAPPING STARS TO CUBES .........."<<endl;

	fit_data();

	cout<<endl<<".......... DATA MAPPED .........."<<endl;

	write_data();

	cout<<endl<<"TOTAL STARS: "<<total_stars<<endl;
	cout<<"STARS PROCESSED: "<<input_data.size()<<endl;
	cout<<"STARS LEFT: "<<total_stars - input_data.size()<<endl;

}