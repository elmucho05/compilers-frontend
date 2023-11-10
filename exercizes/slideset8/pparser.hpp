#define EPS 0
#define BASE_VARIABLES 256

const int F = 256;
const int E = 257;
const int Y = 258;
const int T = 259;
const int B = 260;
const int AXIOM = 257;

std::vector<int> prod1{-2};	// F : 'number'
std::vector<int> prod2{40,257,41};	// F : '(' E ')'
std::vector<int> prod3{42,256,258};	// Y : '*' F Y 
std::vector<int> prod4{0};	// Y : EPS
std::vector<int> prod5{256,258};	// T : F Y
std::vector<int> prod6{43,259,260};	// B : '+' T B
std::vector<int> prod7{0};	// B : EPS
std::vector<int> prod8{259,260};	// E : T B

std::map<int,std::vector<int>> prods = {
	{1,{prod1}},
	{2,{prod2}},
	{3,{prod3}},
	{4,{prod4}},
	{5,{prod5}},
	{6,{prod6}},
	{7,{prod7}},
	{8,{prod8}}
};
std::map<int,std::map<int,int>> parsing_table;
void set_parsing_table() {
	parsing_table[256]={{-2,1}, {40,2}};
	parsing_table[258]={{42,3}, {41,4}, {43,4}, {-1,4}};
	parsing_table[259]={{40,5}, {-2,5}};
	parsing_table[260]={{43,6}, {41,7}, {-1,7}};
	parsing_table[257]={{40,8}, {-2,8}};
};

std::map<int,std::string> display = {
	{1,"F : 'number'"},
	{2,"F : '(' E ')'"},
	{3,"Y : '*' F Y"},
	{4,"Y : EPS"},
	{5,"T : F Y"},
	{6,"B : '+' T B"},
	{7,"B : EPS"},
	{8,"E : T B"}
};
