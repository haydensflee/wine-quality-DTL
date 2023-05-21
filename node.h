#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>
using namespace std;

class node
{
private:
	string myLabel;
	
	float mySplitVal;
	int mySplitValAttr;
	
	vector<float> myData;
	bool myLeafNode;

	// int N;

public:

	node * myLeftNode;
	node * myRightNode;
	//default constructor
	node();

	void setLabel(string label);
	string getLabel();

	void setSplitVal(float splitval);
	float getSplitVal();

	void setData(vector<float> data, int N);
	// float ** getData();
	void printData();

	void setLeftNode(node * leftNode);
	void setRightNode(node * rightNode);
	node * getLeftNode();
	node * getRightNode();

	void setLeafNode(bool leafNode);
	bool getLeafNode();

	void setSplitValAttr(int splitValAttr);
	int getSplitValAttr();




	//deconstructor
	~node();
};
#endif