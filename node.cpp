#include "node.h"
#include <iostream>
#include <string>
using namespace std;

node::node()
{
	myLabel="unknown";
	mySplitVal=0;
	myLeafNode=false;
	mySplitValAttr=-1;
}

void node::setLabel(string label)
{
	myLabel=label;
}
string node::getLabel()
{
	return myLabel;
}

void node::setSplitVal(float splitVal)
{
	mySplitVal=splitVal;
}
float node::getSplitVal()
{
	return mySplitVal;
}

void node::setData(vector<float> data, int N)
{
	// this function might need something like myData=new int[900][12] or something...
	// cout<<data[0][0];
	
	// cout<<N<<"bBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
	for(int i=0; i<N; i++)
	{
		myData.push_back(data.at(i));
	}

}

void node::printData()
{
	for(int i=0; i<myData.size(); i++)
	{
		cout<<myData.at(i)<<" ";
		
	}
	cout<<endl;
}

node * node::getLeftNode()
{
	return myLeftNode;
}
node * node::getRightNode()
{
	return myRightNode;
}

void node::setLeafNode(bool leafNode)
{
	myLeafNode=leafNode;
}
bool node::getLeafNode()
{
	return myLeafNode;
}
void node::setSplitValAttr(int splitValAttr)
{
	mySplitValAttr=splitValAttr;
}
int node::getSplitValAttr()
{
	return mySplitValAttr;
}
// float ** node::getData()
// {
// 	return myData;
// }

node::~node()
{
}